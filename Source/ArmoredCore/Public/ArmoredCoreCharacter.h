// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMechState.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ArmoredCoreCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle,
	Walking,
	Jumping,
	Flying,
	Falling,
	Landing,
	AssertBoost,
};

UENUM(BlueprintType)
enum class EPlayerWeapon : uint8
{
	Rifle,
	Missile,
	BeamSaber,
};

UENUM(BlueprintType)
enum class EPlayerUsedWeaponPos : uint8
{
	LArm,
	RArm,
	LShoulder,
	RShoulder,
};

UCLASS(config=Game)
class AArmoredCoreCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Boost Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BoostOnAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QuickBoostAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AssertBoostAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AssertBoostCancleAction;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LArmFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RArmFireAction;	


public:
	AArmoredCoreCharacter();
	
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void UpdatePlayerState(const EPlayerState newState);

	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void OnMoveComplete();

	// Jump & Fly
	
	UFUNCTION()
	void ToggleToJumpState();
	
	virtual void Jump() override;
	
	virtual void StopJumping() override;
	
	// Camera
	UFUNCTION()
	void UpdateCamera();
	
	// Boost Function
	UFUNCTION()
	void BoostOn();
	
	UFUNCTION()
	void UpdateBoostGauge();

	UFUNCTION()
	void UpdateBoostState();
	
	// QuickBoost Function
	UFUNCTION()
	void QuickBoost();

	UFUNCTION()
	void ResetQuickBoostCoolTime();
	
	// AssertBoost Function
	UFUNCTION()
	void AssertBoost();

	UFUNCTION()
	void AssertBoostCancle();

	UFUNCTION()
	void StartAssertBoostLaunch();

	// Attack Function
	UFUNCTION()
	void UpdateAttackState();

	UFUNCTION()
	void MakeProjectile(EPlayerUsedWeaponPos weaponPos);
	
	UFUNCTION()
	void LArmFirePressed();

	UFUNCTION()
	void LArmFireReleased();
	
	UFUNCTION()
	void RArmFirePressed();
	
	UFUNCTION()
	void RArmFireReleased();

	UFUNCTION()
	void RotateCharacterToAimDirection();

	UFUNCTION()
	void PlayMyMontage(UAnimMontage* montage);

	UFUNCTION()
	void OnAnimEnded(UAnimMontage* Montage,bool bInterrupted);

private:
	
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Scene Component
	UPROPERTY(EditAnywhere)
	class USceneComponent* LArmFirePos;

	UPROPERTY(EditAnywhere)
	class USceneComponent* RArmFirePos;

	// UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerMainUI* MainUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerMainUI> MainUIFactory;


	// Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* LandMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* JumpMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AssertBoostLaunchMontage;
	
	
	// State variance
	UPROPERTY()
	class UBaseState* CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	EPlayerState CurrentStateEnum;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	EPlayerState PreviousStateEnum;

	// TimerHandles
	UPROPERTY()
	FTimerHandle QuickBoostCoolTimeHandle;

	UPROPERTY()
	FTimerHandle AssertBoostLaunchHandle;

	UPROPERTY()
	FTimerHandle LArmFireTimerHandle;

	UPROPERTY()
	FTimerHandle RArmFireTimerHandle;

	UPROPERTY()
	FTimerHandle ChangeJumpStateTimerHandle;

	UPROPERTY()
	FTimerHandle ToggleIsLandingTimerHandle;
	
	// BaseMove variance
	UPROPERTY()
	FVector2D MovementVector;

	UPROPERTY(BlueprintReadOnly)
	bool IsMove;
	
	UPROPERTY()
	float WalkSpeed;

	UPROPERTY()
	FRotator WalkRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP{9080.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP{CurrentHP = MaxHP};
	
	
	// Boost variance
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Boost")
	bool IsBoostOn;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Boost")
	float BoostSpeed;

	UPROPERTY()
	FRotator BoostRotationRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float BoostGauge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float MaxBoostGauge;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float BoostUsedTime;

	UPROPERTY()
	bool IsBoostChargeStart;
	
	// QuickBoost variance
	UPROPERTY()
	FVector QuickBoostDir;
	
	UPROPERTY()
	bool CanQuickBoost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	bool IsQuickBoostTrigger;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="QuickBoost")
	float QuickBoostSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="QuickBoost")
	float QuickBoostCoolTime;

	// AssertBoost variance
	UPROPERTY()
	FVector AssertBoostDir;
	
	UPROPERTY()
	bool IsAssertBoostOn;

	UPROPERTY()
	bool IsAssertBoostLaunch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="AssertBoost")
	float AssertBoostSpeed;

	// Attack variance
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory;
	
	UPROPERTY(EditAnywhere)
	bool IsAttacking;
	
	UPROPERTY()
	FVector AimDirection;

	UPROPERTY()
	class UWeapon* LArmWeapon;
	UPROPERTY()
	class UWeapon* RArmWeapon;
	UPROPERTY()
	class UWeapon* RShoulderWeapon;
	
	// ETC
	UPROPERTY()
	float WalkCameraLagSpeed;
	
	UPROPERTY(EditAnywhere)
	float BoostCameraLagSpeed;
	
	UPROPERTY()
	float BaseGravity;

	UPROPERTY()
	float FlyingGravity;

	UPROPERTY()
	float FallingGravity;

	UPROPERTY(EditAnywhere)
	float MouseSensitivity;
};

