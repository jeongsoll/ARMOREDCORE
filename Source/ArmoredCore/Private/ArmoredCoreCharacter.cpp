// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArmoredCoreCharacter.h"

#include "Aim.h"
#include "AssertBoostState.h"
#include "AsyncTreeDifferences.h"
#include "Bullet.h"
#include "EasingFunction.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FallState.h"
#include "FlyState.h"
#include "FrameTypes.h"
#include "IdleState.h"
#include "InputActionValue.h"
#include "InteractiveToolManager.h"
#include "JumpState.h"
#include "LandState.h"
#include "MovieSceneTracksComponentTypes.h"
#include "WalkState.h"
#include "Weapon.h"
#include "BaseGizmos/GizmoElementArrow.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"
#include "Rendering/RenderCommandPipes.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AArmoredCoreCharacter

AArmoredCoreCharacter::AArmoredCoreCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.75f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->BrakingDecelerationFlying = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(-60.0f, 0.0f, 120.0f));
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	LArmFirePos = CreateDefaultSubobject<USceneComponent>(TEXT("LArmFirePos"));
	RArmFirePos = CreateDefaultSubobject<USceneComponent>(TEXT("RArmFirePos"));

	LArmFirePos->SetupAttachment(GetMesh());
	RArmFirePos->SetupAttachment(GetMesh());

	GetMesh()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);


	//
	//
	// 변수 초기화 구간
	GetCharacterMovement()->BrakingDecelerationFalling = 3500;

	// 이동
	IsMove = false;
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	WalkRotationRate = GetCharacterMovement()->RotationRate;

	// 카메라
	WalkCameraLagSpeed = CameraBoom->CameraLagSpeed;
	BoostCameraLagSpeed = 8.0f;

	// 마우스 민감도
	MouseSensitivity = 1.0f;

	// 중력
	BaseGravity = 1.75f;
	FlyingGravity = 0.1f;
	FallingGravity = 0.7f;


	// 부스트
	IsBoostOn = false;
	BoostSpeed = 800.0f;
	BoostRotationRate = FRotator(0,150.0f,0);
	
	// 부스트 사용하는 기술(퀵 부스트, 어썰트 부스트) 사용 후
	// 이어서 부스트 사용하는 기술을 사용하지 않은 상태로 3초가 지나면
	// 부스트를 회복한다.
	MaxBoostGauge = 100.0f;
	BoostGauge = MaxBoostGauge;
	IsBoostChargeStart = false;
	BoostUsedTime = 0.0f;
	
	CanQuickBoost = true;
	IsQuickBoostTrigger = false;
	QuickBoostSpeed = 2500.0f;
	QuickBoostCoolTime = 0.65f;
	
	IsAssertBoostOn = false;
	IsAssertBoostLaunch = false;

	
	// 공격
	IsAttacking = false;

}

void AArmoredCoreCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FName SocketName = TEXT("FirePos");
	if (GetMesh()->DoesSocketExist(SocketName))
	{
		RArmFirePos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket %s does not exist on SkeletalMesh"), *SocketName.ToString());
	}

	// state
	CurrentStateEnum = EPlayerState::Idle;
	CurrentState = NewObject<UIdleState>(this);
	CurrentState->EnterState(this);

	// ui 생성
	MainUI = CreateWidget<UPlayerMainUI>(GetWorld(),
		MainUIFactory);
	
	if (MainUI)
	{
		MainUI->AddToViewport();
	}
	
	LArmWeapon = NewObject<UWeapon>(this);
	RArmWeapon = NewObject<UWeapon>(this);
	RShoulderWeapon = NewObject<UWeapon>(this);

	LArmWeapon->SetChoosenWeapon(EPlayerWeapon::BeamSaber);
	RArmWeapon->SetChoosenWeapon(EPlayerWeapon::Rifle);
	RShoulderWeapon->SetChoosenWeapon(EPlayerWeapon::Missile);
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AArmoredCoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping & Fly
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::OnMoveComplete);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::Look);

		// Boost
		EnhancedInputComponent->BindAction(BoostOnAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::BoostOn);
		EnhancedInputComponent->BindAction(QuickBoostAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::QuickBoost);
		EnhancedInputComponent->BindAction(AssertBoostAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::AssertBoost);
		EnhancedInputComponent->BindAction(AssertBoostCancleAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::AssertBoostCancle);
	
		// LArmFire
		EnhancedInputComponent->BindAction(LArmFireAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::LArmFirePressed);
		EnhancedInputComponent->BindAction(LArmFireAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::LArmFireReleased);

		// RArmFire
		EnhancedInputComponent->BindAction(RArmFireAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::RArmFirePressed);
		EnhancedInputComponent->BindAction(RArmFireAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::RArmFireReleased);
	}
	
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AArmoredCoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState->UpdateState(this, DeltaTime);
	}

	// TODO
	// 부스트 관련 함수들 전부 이동시키기

	// 부스트의 카메라 연출 함수
	UpdateCamera();
	// 부스트 함수
	UpdateBoostState();
	UpdateBoostGauge();
	// 공격 함수
	UpdateAttackState();
}

void AArmoredCoreCharacter::UpdatePlayerState(EPlayerState NewState)
{
	if (CurrentStateEnum == NewState)
	{
		UE_LOG(LogTemp, Error, TEXT("Player state already in progress"));
		return;
	}

	if (CurrentStateEnum == EPlayerState::Falling)
	{
		if (NewState == EPlayerState::Flying || NewState == EPlayerState::Jumping)
		{
			if (BoostGauge <= 0.0f)
				return;
		}
	}
	
	if (CurrentState)
	{
		CurrentState->ExitState(this);
		PreviousStateEnum = CurrentStateEnum;
		CurrentState = nullptr;
	}

	CurrentStateEnum = NewState;
	switch (NewState)
	{
	case EPlayerState::Idle:
		CurrentState = NewObject<UIdleState>(this);
		break;
	case EPlayerState::Walking:
		CurrentState = NewObject<UWalkState>(this);
		break;
	case EPlayerState::Jumping:
		CurrentState = NewObject<UJumpState>(this);
		break;
	case EPlayerState::Flying:
		CurrentState = NewObject<UFlyState>(this);
		break;
	case EPlayerState::Falling:
		CurrentState = NewObject<UFallState>(this);
		break;
	case EPlayerState::Landing:
		CurrentState = NewObject<ULandState>(this);
		break;
	case EPlayerState::AssertBoost:
		CurrentState = NewObject<UAssertBoostState>(this);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unhandled player state: %d"), NewState);
		break;
	}

	if (CurrentState)
	{
		CurrentState->EnterState(this);
	}
}

void AArmoredCoreCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
	}
}

void AArmoredCoreCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		if (CurrentStateEnum == EPlayerState::AssertBoost)
			return;
		
		// state를 walk로 바꾸지 않는 이유
		// fly state와 walk state가 동시에 생길 수 있어서
		// ismove 변수만 true로 바꾸는 역할인 walking state는 적용하지 않는다.
		//IsMove = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y, true);
		AddMovementInput(RightDirection, MovementVector.X, true);
		
		QuickBoostDir = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
		QuickBoostDir.Normalize();
		
	}
}

void AArmoredCoreCharacter::OnMoveComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMoveComplete"));
	MovementVector = FVector2D::ZeroVector;
	if (CurrentStateEnum != EPlayerState::AssertBoost && CurrentStateEnum != EPlayerState::Flying && CurrentStateEnum != EPlayerState::Falling)
	{
		UpdatePlayerState(EPlayerState::Idle);
	}
}

// 점프 - 비행 - 추락 순서로 진행하기 위한 코드
// 점프 할 때 발 구르기 후 비행해야 하기 때문에 timer사용
void AArmoredCoreCharacter::Jump()
{
	if (CurrentStateEnum != EPlayerState::Jumping)
	{
		IsBoostOn = true;
		if (CurrentStateEnum == EPlayerState::Falling)
		{
			// 떨어지는 도중에 space를 다시 누를 때의 코드
			if (BoostGauge <= 0.0f)
				return;
			else
			{
				UpdatePlayerState(EPlayerState::Flying);
				return;
			}
		}
		else
		{
			PlayMyMontage(JumpMontage);
			LaunchCharacter(GetActorUpVector() * 750.0f,false,true);
		}

		GetWorld()->GetTimerManager().SetTimer(ChangeJumpStateTimerHandle,this,&AArmoredCoreCharacter::ToggleToJumpState,0.3f,false);
	}
}

void AArmoredCoreCharacter::ToggleToJumpState()
{
	UpdatePlayerState(EPlayerState::Jumping);
}

void AArmoredCoreCharacter::StopJumping()
{
	Super::StopJumping();
	if (GetWorld()->GetTimerManager().IsTimerActive(ChangeJumpStateTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(ChangeJumpStateTimerHandle);
	
	UpdatePlayerState(EPlayerState::Falling);
}

void AArmoredCoreCharacter::UpdateCamera()
{
	FRotator lerpRotator = FRotator(-MovementVector.Y, 0, MovementVector.X);
	FRotator newRotator;

	// 퀵부스트 사용가능 시(퀵부스트 사용안한상태), 부스트 이동상태에 따른 회전값 설정
	if (CanQuickBoost)
	{
		// 퀵 부스트를 사용한 후에 Trigger bool값이 몇초 뒤에 false로 변함
		// 이를 이용해서 퀵부스트로 변경된 회전값을 0 0 0 으로 빠른 회복을 위한 코드
		if (IsQuickBoostTrigger)
		{
			newRotator = UKismetMathLibrary::RInterpTo(FollowCamera->GetRelativeRotation(),FRotator(0,0,0),GetWorld()->GetDeltaSeconds(),3.0f);
		}

		// 부스트 이동을 하는 상태이고 퀵부스트가 끝났으면
		// 카메라를 천천히 회전해라
		if (IsMove && IsBoostOn && !IsQuickBoostTrigger)
		{
			// lerpRotator가 (-1,0,1)의 값을 가지기 때문에 곱해준 값 만큼 카메라의 회전각도가 올라간다.
			newRotator = UKismetMathLibrary::RInterpTo(FollowCamera->GetRelativeRotation(),lerpRotator * 1.2f, GetWorld()->GetDeltaSeconds(), 0.2f);
		}

		// 이동을 멈췄으면
		// 카메라를 원상복구 시켜라
		else
		{
			newRotator = UKismetMathLibrary::RInterpTo(FollowCamera->GetRelativeRotation(),FRotator(0,0,0),GetWorld()->GetDeltaSeconds(),3.0f);
		}
	}
	// 퀵부스트 사용 시, 카메라를 기존보다 3배 더 회전값을 주어서 돌려라
	else
	{
		newRotator = UKismetMathLibrary::RInterpTo(FollowCamera->GetRelativeRotation(),lerpRotator * 2.5f, GetWorld()->GetDeltaSeconds(), 3.0f);
	}	
	FollowCamera->SetRelativeRotation(newRotator);
}


void AArmoredCoreCharacter::BoostOn()
{
	if (IsMove)
		IsBoostOn = true;
}

void AArmoredCoreCharacter::UpdateBoostGauge()
{
	if (BoostGauge <= 0.0f)
	{
		BoostGauge = 0.0f;
	}
	
	if (BoostUsedTime >= 2.0f)
	{
		if (BoostGauge < 100.0f &&
			!GetCharacterMovement()->IsFlying() &&
			!GetCharacterMovement()->IsFalling())
			IsBoostChargeStart = true;
	}
	else
	{
		IsBoostChargeStart = false;
		BoostUsedTime += GetWorld()->GetDeltaSeconds();
	}
	

	if (IsBoostChargeStart)
	{
		if (BoostGauge < 100.0f)
			BoostGauge += GetWorld()->GetDeltaSeconds() * 20.0f;
		else
		{
			BoostGauge = 100.0f;
			IsBoostChargeStart = false;
		}
	}
}

void AArmoredCoreCharacter::UpdateBoostState()
{
	if (IsBoostOn)
	{
		CameraBoom->CameraLagSpeed = BoostCameraLagSpeed;
		GetCharacterMovement()->MaxWalkSpeed = BoostSpeed;
		GetCharacterMovement()->RotationRate = BoostRotationRate;
		GetCharacterMovement()->BrakingFrictionFactor = 0.75f;
	}
	else
	{
		CameraBoom->CameraLagSpeed = WalkCameraLagSpeed;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCharacterMovement()->RotationRate = WalkRotationRate;
		GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	}
}

void AArmoredCoreCharacter::QuickBoost()
{
	if (CanQuickBoost)
	{
		IsQuickBoostTrigger = true;

		if (IsMove && BoostGauge > 0)
		{
			IsBoostOn = true;
			BoostGauge -= 10.0f;
			FVector newVelocity = QuickBoostSpeed * QuickBoostDir;

			// 바닥에 있는 상태일때는 퀵부스트에 UpVector를 더해주지 않기 위한 조건문
			if (GetCharacterMovement()->IsFlying() || GetCharacterMovement()->IsFalling())
				GetCharacterMovement()->GravityScale = FlyingGravity;
			else
				newVelocity += GetActorUpVector() * 450.0f;
			
			ACharacter::LaunchCharacter(newVelocity,true,true);

			CanQuickBoost = false;
			BoostUsedTime = 0.0f;
			GetWorld()->GetTimerManager().SetTimer(QuickBoostCoolTimeHandle,this,&AArmoredCoreCharacter::ResetQuickBoostCoolTime,QuickBoostCoolTime,false);
		}
	}
}

void AArmoredCoreCharacter::ResetQuickBoostCoolTime()
{
	GetCharacterMovement()->GravityScale = BaseGravity;
	CanQuickBoost = true;
}

void AArmoredCoreCharacter::AssertBoost()
{
	UpdatePlayerState(EPlayerState::AssertBoost);

	// 공중이동 전, 순간 대쉬를 위한 timer 코드
	if(!GetWorld()->GetTimerManager().IsTimerActive(ToggleIsLandingTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(AssertBoostLaunchHandle,this,&AArmoredCoreCharacter::StartAssertBoostLaunch,0.3f,false);
	}
}

void AArmoredCoreCharacter::AssertBoostCancle()
{
	if (CurrentStateEnum == EPlayerState::AssertBoost)
	{
		UpdatePlayerState(EPlayerState::Falling);
	}
}

void AArmoredCoreCharacter::StartAssertBoostLaunch()
{
	if (!IsAssertBoostLaunch)
	{
		IsAssertBoostLaunch = true;
		LaunchCharacter(AssertBoostDir * 2000.0f,true,true);
		PlayMyMontage(AssertBoostLaunchMontage);
	}
}

void AArmoredCoreCharacter::UpdateAttackState()
{
	if (IsAttacking)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		AimDirection = FollowCamera->GetForwardVector();
		AimDirection.Normalize();
		RotateCharacterToAimDirection();
	}
}

void AArmoredCoreCharacter::MakeProjectile(EPlayerUsedWeaponPos weaponPos)
{
	FTransform transform;
	if (weaponPos == EPlayerUsedWeaponPos::LArm)
	{
		if (!LArmWeapon->IsProjectile)
			return;
	}
	else if (weaponPos == EPlayerUsedWeaponPos::RArm)
	{
		if (!RArmWeapon->IsProjectile)
			return;

		transform = RArmFirePos->GetComponentTransform();
		

		if (RArmWeapon->RemainArmor <= 0)
		{
			RArmWeapon->Reload();
		}
		else if (RArmWeapon->RemainArmor > 0)
		{
			RArmWeapon->RemainArmor -= 1;
			ABullet* projectile = GetWorld()->SpawnActor<ABullet>(BulletFactory,transform);
			if (projectile)
			{
				projectile->Damage = RArmWeapon->Damage;
				projectile->FireInDirection(AimDirection);
			}
		}
	}
	else if (weaponPos == EPlayerUsedWeaponPos::RShoulder)
	{
		if (!RShoulderWeapon->IsProjectile)
			return;
	}
}

void AArmoredCoreCharacter::LArmFirePressed()
{
	// IsAttacking = true;
	// if (!GetWorld()->GetTimerManager().IsTimerActive(LArmFireTimerHandle))
	// {
	// 	GetWorld()->GetTimerManager().SetTimer(LArmFireTimerHandle,[this](){this->MakeProjectile(EPlayerUsedWeaponPos::LArm);},0.3f,true);
	// }
}

void AArmoredCoreCharacter::LArmFireReleased()
{
	// IsAttacking = false;
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	//
	// if (GetWorld()->GetTimerManager().IsTimerActive(LArmFireTimerHandle))
	// {
	// 	GetWorld()->GetTimerManager().ClearTimer(LArmFireTimerHandle);
	// }
}

void AArmoredCoreCharacter::RArmFirePressed()
{
	IsAttacking = true;
	if (!GetWorld()->GetTimerManager().IsTimerActive(RArmFireTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(RArmFireTimerHandle,[this](){this->MakeProjectile(EPlayerUsedWeaponPos::RArm);},0.3f,true);
	}
}

void AArmoredCoreCharacter::RArmFireReleased()
{
	IsAttacking = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	if (GetWorld()->GetTimerManager().IsTimerActive(RArmFireTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(RArmFireTimerHandle);
	}
}

void AArmoredCoreCharacter::RotateCharacterToAimDirection()
{
	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw,0);
	FRotator newRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(),YawRotation,GetWorld()->GetDeltaSeconds(),5.0f);
	SetActorRotation(newRotation);
}

void AArmoredCoreCharacter::PlayMyMontage(UAnimMontage* montage)
{
	if (montage)
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			if (AnimInstance->Montage_IsPlaying(montage))
				return;
			AnimInstance->Montage_Play(montage);
			AnimInstance->OnMontageEnded.AddDynamic(this, &AArmoredCoreCharacter::OnAnimEnded);
		}
	}
}

void AArmoredCoreCharacter::OnAnimEnded(UAnimMontage* Montage,bool bInterrupted)
{
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
}
