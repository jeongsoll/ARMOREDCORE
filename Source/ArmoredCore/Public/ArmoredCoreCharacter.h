// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMainUI.h"
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

enum class EPlayerWeapon : uint8
{
	Rifle,
	Missile,
	BeamSaber,
};

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
	
	void UpdatePlayerState(const EPlayerState newState);
	
	void Look(const FInputActionValue& Value);
	
	void Move(const FInputActionValue& Value);

	void OnMoveComplete();

	// Jump & Fly
	virtual void Jump() override;
	
	void ToggleToJumpState();
	
	virtual void StopJumping() override;
	
	// Camera
	void UpdateCamera();
	
	// Boost Function
	void BoostOn();
	
	void UpdateBoostGauge();

	void UpdateBoostState();
	
	// QuickBoost Function
	void QuickBoost();

	void ResetQuickBoostCoolTime();
	
	// AssertBoost Function
	void AssertBoost();

	void AssertBoostCancle();

	void StartAssertBoostLaunch();

	// Attack Function
	void UpdateAttackState();

	void MakeProjectile(EPlayerUsedWeaponPos weaponPos);
	
	void LArmFirePressed();

	void LArmFireReleased();
	
	void RArmFirePressed();
	
	void RArmFireReleased();

	void RotateCharacterToAimDirection();
	
	
private:
	
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere)
	class USceneComponent* LArmFirePos;

	UPROPERTY(EditAnywhere)
	class USceneComponent* RArmFirePos;

	UPROPERTY()
	class UPlayerMainUI* MainUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerMainUI> MainUIFactory;
	
	
	// Enum variance
	class IPlayerMechState* CurrentState;
	
	EPlayerState CurrentStateEnum;
	
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
	FVector2D MovementVector;

	UPROPERTY(BlueprintReadOnly)
	bool IsMove;
	
	float WalkSpeed;
	
	FRotator WalkRotationRate;

	UPROPERTY(EditAnywhere)
	float MaxHP{9080.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP{CurrentHP = MaxHP};
	
	
	// Boost variance
	bool IsBoostOn;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Boost")
	float BoostSpeed;
	
	FRotator BoostRotationRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float BoostGauge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float MaxBoostGauge;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float BoostUsedTime;

	bool IsBoostChargeStart;
	
	// QuickBoost variance
	FVector QuickBoostDir;
	
	bool CanQuickBoost;

	bool IsQuickBoostTrigger;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="QuickBoost")
	float QuickBoostSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="QuickBoost")
	float QuickBoostCoolTime;

	// AssertBoost variance
	FVector AssertBoostDir;
	
	bool IsAssertBoostOn;

	bool IsAssertBoostLaunch;

	// Attack variance
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory;
	
	UPROPERTY(EditAnywhere)
	bool IsAttacking;
	
	FVector AimDirection;

	class UWeapon* LArmWeapon;
	class UWeapon* RArmWeapon;
	class UWeapon* RShoulderWeapon;


	
	
	
	// ETC
	float WalkCameraLagSpeed;
	
	UPROPERTY(EditAnywhere)
	float BoostCameraLagSpeed;

	float BaseGravity;
	
	float FlyingGravity;

	float FallingGravity;

	UPROPERTY(EditAnywhere)
	float MouseSensitivity;
};

