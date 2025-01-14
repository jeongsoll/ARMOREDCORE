// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArmoredCoreCharacter.h"

#include "Bullet.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FrameTypes.h"
#include "InputActionValue.h"
#include "InteractiveToolManager.h"
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
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
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

	// 임시용 바디
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Leg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Leg"));
	LArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LArm"));
	RArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RArm"));

	LArmFirePos = CreateDefaultSubobject<USceneComponent>(TEXT("LArmFirePos"));
	RArmFirePos = CreateDefaultSubobject<USceneComponent>(TEXT("RArmFirePos"));
	
	Body->SetupAttachment(GetMesh());
	Leg->SetupAttachment(GetMesh());
	LArm->SetupAttachment(GetMesh());
	RArm->SetupAttachment(GetMesh());

	LArmFirePos->SetupAttachment(LArm);
	LArmFirePos->SetRelativeLocation(FVector(53.0f, 0.0f, 0.0f));
	RArmFirePos->SetupAttachment(RArm);
	RArmFirePos->SetRelativeLocation(FVector(53.0f, 0.0f, 0.0f));

	if (Body and LArm and RArm and Leg)
	{
		UStaticMesh* AllBodyMesh = LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube.cube"));
		if (AllBodyMesh)
		{
			Body->SetStaticMesh(AllBodyMesh);
			Leg->SetStaticMesh(AllBodyMesh);
			LArm->SetStaticMesh(AllBodyMesh);
			RArm->SetStaticMesh(AllBodyMesh);
		}

		UMaterial* AllBodyMaterial = LoadObject<UMaterial>(nullptr,TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
		if (AllBodyMaterial)
		{
			Body->SetMaterial(0, AllBodyMaterial);
			Leg->SetMaterial(0, AllBodyMaterial);
			LArm->SetMaterial(0, AllBodyMaterial);
			RArm->SetMaterial(0, AllBodyMaterial);
		}

		Body->SetRelativeScale3D(FVector3d(0.65f,0.65f,1.0f));
		Body->SetRelativeLocation(FVector3d(0.0f,0.0f,20.0f));

		Leg->SetRelativeScale3D(FVector3d(1.0f,1.2f,0.4f));
		Leg->SetRelativeLocation(FVector3d(0.0f,0.0f,-50.0f));

		LArm->SetRelativeScale3D(FVector3d(1.5f,0.2f,0.2f));
		LArm->SetRelativeLocation(FVector3d(35.0f,-50.0f,0.0f));

		RArm->SetRelativeScale3D(FVector3d(1.5f,0.2f,0.2f));
		RArm->SetRelativeLocation(FVector3d(35.0f,50.0f,0.0f));
	}
}

void AArmoredCoreCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	WalkRotationRate = GetCharacterMovement()->RotationRate;
	WalkCameraLagSpeed = CameraBoom->CameraLagSpeed;
	
	IsMove = false;
	IsBoostOn = false;

	// 부스트 사용하는 기술(퀵 부스트, 어썰트 부스트) 사용 후
	// 이어서 부스트 사용하는 기술을 사용하지 않은 상태로 3초가 지나면
	// 부스트를 회복한다.
	BoostGauge = 100.0f;
	IsBoostChargeStart = false;
	BoostUsedTime = 0.0f;
	
	CanQuickBoost = true;
	IsQuickBoostTrigger = false;
	QuickBoostSpeed = 4000.0f;
	QuickBoostCameraLagSpeed = 3.5f;

	IsAssertBoostOn = false;
	IsAssertBoostLaunch = false;

	BoostSpeed = 600.0f;
	BoostRotationRate = FRotator(0,150,0);
	BoostCameraLagSpeed = 8.0f;

	BaseGravity = 1.75f;
	FlyingGravity = 0.1f;

	MouseSensitivity = 1.0f;
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
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Ongoing, this, &AArmoredCoreCharacter::Fly);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AArmoredCoreCharacter::OnMoveComplete);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::Look);

		// Boost
		EnhancedInputComponent->BindAction(BoostOnAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::BoostOn);
		EnhancedInputComponent->BindAction(QuickBoostAction, ETriggerEvent::Triggered, this, &AArmoredCoreCharacter::QuickBoost);
		EnhancedInputComponent->BindAction(AssertBoostAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::AssertBoost);

		// Fire
		EnhancedInputComponent->BindAction(LArmFireAction, ETriggerEvent::Started, this, &AArmoredCoreCharacter::FirePressed);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AArmoredCoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Body and LArm and RArm and Leg)
	{
		if (IsBoostOn)
		{
			UMaterial* AllBodyMaterial = LoadObject<UMaterial>(nullptr,TEXT("/Script/Engine.Material'/Game/JJH/BoostMaterial.BoostMaterial'"));
			if (AllBodyMaterial)
			{
				Body->SetMaterial(0, AllBodyMaterial);
			}
		}
		else
		{
			UMaterial* AllBodyMaterial = LoadObject<UMaterial>(nullptr,TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
			if (AllBodyMaterial)
			{
				Body->SetMaterial(0, AllBodyMaterial);
			}
		}
	}

	CheckBoostOn();
	CheckBoostGauge();
	CheckCamera();
	SetQuickBoostSpeed();
	CheckAssertBoostOn();
}

void AArmoredCoreCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		IsMove = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		QuickBoostDir = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
		QuickBoostDir.Normalize();
		
	}
}

void AArmoredCoreCharacter::OnMoveComplete()
{
	IsMove = false;
	IsBoostOn = false;
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

void AArmoredCoreCharacter::BoostOn()
{
	if (IsMove)
		IsBoostOn = true;
}

void AArmoredCoreCharacter::QuickBoost()
{
	if (CanQuickBoost)
	{
		IsQuickBoostTrigger = true;

		if (IsMove && BoostGauge > 0)
		{
			BoostGauge -= 10.0f;
			if (GetCharacterMovement()->IsFlying() || GetCharacterMovement()->IsFalling())
				GetCharacterMovement()->GravityScale = FlyingGravity;
			IsBoostOn = true;
			ACharacter::LaunchCharacter(QuickBoostDir * QuickBoostSpeed,true,true);

			CameraBoom->CameraLagSpeed = QuickBoostCameraLagSpeed;
			CanQuickBoost = false;
			BoostUsedTime = 0.0f;
			//퀵부스트 쿨타임 0.5초로 하드코딩
			GetWorld()->GetTimerManager().SetTimer(QuickBoostCoolTimeHandle,this,&AArmoredCoreCharacter::ResetQuickBoostCoolTime,0.65f,false);
		}
	}
}

void AArmoredCoreCharacter::CheckBoostOn()
{
	if (!IsMove && GetCharacterMovement()->IsWalking() && IsBoostOn)
		IsBoostOn = false;
	
	if (IsBoostOn)
	{
		GetCharacterMovement()->MaxWalkSpeed = BoostSpeed;
		GetCharacterMovement()->RotationRate = BoostRotationRate;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCharacterMovement()->RotationRate = WalkRotationRate;
	}
}

void AArmoredCoreCharacter::CheckCamera()
{
	// 퀵 부스트 사용 시, 플레이어의 몸이 먼저 이동하고 카메라가 따라가는 걸 구현 하기 위한 함수
	// 카메라 Lag speed를 조정해서 구현
	if (IsQuickBoostTrigger)
	{
		//임의로 카메라 lag의 원래속도로의 복구속도를 3.0 * deltatime으로 설정해놓음
		CameraBoom->CameraLagSpeed += (3.0f * GetWorld()->DeltaTimeSeconds);
		if (IsBoostOn)
		{
			if (CameraBoom->CameraLagSpeed > BoostCameraLagSpeed)
				IsQuickBoostTrigger = false;
		}
		else
		{
			if (CameraBoom->CameraLagSpeed > WalkCameraLagSpeed)
				IsQuickBoostTrigger = false;
		}
	}
	else
	{
		if (IsBoostOn)
			CameraBoom->CameraLagSpeed = BoostCameraLagSpeed;
		else
			CameraBoom->CameraLagSpeed = WalkCameraLagSpeed;
	}

	// 어썰트 부스트 사용 시, 카메라 offset이 달라지는 것을 lerp로 처리
	if (IsAssertBoostOn)
	{
		FVector newSocket = UKismetMathLibrary::VInterpTo(CameraBoom->SocketOffset,FVector(0,200,-15),GetWorld()->GetDeltaSeconds(), 3.0f);
		CameraBoom->SocketOffset = newSocket;
	}
	else
	{
		FVector newSocket = UKismetMathLibrary::VInterpTo(CameraBoom->SocketOffset,FVector(0,0,0),GetWorld()->GetDeltaSeconds(), 5.0f);
		CameraBoom->SocketOffset = newSocket;
	}
	
}

void AArmoredCoreCharacter::ResetQuickBoostCoolTime()
{
	GetCharacterMovement()->GravityScale = BaseGravity;
	CanQuickBoost = true;
}

void AArmoredCoreCharacter::Fly()
{
	IsBoostOn = true;
	if (GetCharacterMovement()->IsFlying())
	{
		AddMovementInput(GetActorUpVector(),1,true);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void AArmoredCoreCharacter::SetQuickBoostSpeed()
{
	// fly 상태일 때 launch character로 인해 전진하는 값이 다르기에 따로 설정해주기 위한 함수
	if (GetCharacterMovement()->IsFlying() || GetCharacterMovement()->IsFalling())
		QuickBoostSpeed = 1700.0f;
	else
		QuickBoostSpeed = 4000.0f;
}

void AArmoredCoreCharacter::StopJumping()
{
	// AChracter의 Stop Jumping을 override하여 movementmode를 설정해줌
	Super::StopJumping();
	GetCharacterMovement()->SetMovementMode(MOVE_Falling);
}

void AArmoredCoreCharacter::AssertBoost()
{
	IsAssertBoostOn = !IsAssertBoostOn;
	if (IsAssertBoostOn)
	{
		GetWorld()->GetTimerManager().SetTimer(AssertBoostLaunchHandle,this,&AArmoredCoreCharacter::AssertBoostStartLaunch,0.3f,false);
		IsMove = true;
		IsBoostOn = true;

		// 플레이어가 컨트롤러에 의해 로테이션 하는 기능을 막고 카메라가 향하는 방향으로 로테이션을 돌리도록 변경
		// 카메라 offset 변경
		GetCharacterMovement()->bOrientRotationToMovement = false;
		MouseSensitivity = 0.1f;
	}
	else
	{
		// 어썰트 부스트를 중간에 끊었을 때를 방지하기 위한 코드
		IsAssertBoostLaunch = false;
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		GetCharacterMovement()->GravityScale = BaseGravity;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		MouseSensitivity = 1.0f;
	}
}

void AArmoredCoreCharacter::AssertBoostStartLaunch()
{
	IsAssertBoostLaunch = true;
	ACharacter::LaunchCharacter(AssertBoostDir * 1000.0f,true,true);
}

void AArmoredCoreCharacter::CheckAssertBoostOn()
{
	if (IsAssertBoostOn)
	{
		AssertBoostDir = FollowCamera->GetForwardVector() + FollowCamera->GetRightVector();
		AssertBoostDir.Normalize();
		FRotator ControlRotation = GetControlRotation();
		FRotator YawRotation(0, ControlRotation.Yaw,0);
		SetActorRotation(YawRotation);

		if (IsAssertBoostLaunch)
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			GetCharacterMovement()->GravityScale = FlyingGravity;
			AddMovementInput(AssertBoostDir,2.0f,true);
		}
	}
	else
	{
		if (IsAssertBoostLaunch)
		{
			// 어썰트 부스트를 부스트 게이지 만큼 다 사용한 후 부스트가 꺼질 때를 위한 코드
			IsAssertBoostLaunch = false;
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			GetCharacterMovement()->GravityScale = BaseGravity;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			MouseSensitivity = 1.0f;
		}
	}
}

void AArmoredCoreCharacter::CheckBoostGauge()
{
	if (BoostUsedTime >= 3.0f)
	{
		if (BoostGauge < 100.0f &&
			!GetCharacterMovement()->IsFlying() &&
			!GetCharacterMovement()->IsFalling())
			IsBoostChargeStart = true;
	}
	else
		BoostUsedTime += GetWorld()->GetDeltaSeconds();

	// 비행 상태일때 부스트 게이지 관리
	if (GetCharacterMovement()->IsFlying() && BoostGauge > 0)
	{
		BoostUsedTime = 0.0f;
		if (IsAssertBoostOn)
			BoostGauge -= GetWorld()->GetDeltaSeconds() * 10.0f;
		else
			BoostGauge -= GetWorld()->GetDeltaSeconds() * 5.0f;
	}
	else if (BoostGauge < 0)
	{
		BoostGauge = 0.0f;
		IsAssertBoostOn = false;
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

void AArmoredCoreCharacter::MakeBullet()
{
	FTransform transform = LArmFirePos->GetComponentTransform();
	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletFactory,transform);
}

void AArmoredCoreCharacter::FirePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("FirePressed"));
	FVector FireDir = FollowCamera->GetForwardVector();
	FireDir.Normalize();
	FTransform transform = LArmFirePos->GetComponentTransform();
	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletFactory,transform);

	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw,0);
	SetActorRotation(YawRotation);
	Projectile->FireInDirection(FireDir);
}















