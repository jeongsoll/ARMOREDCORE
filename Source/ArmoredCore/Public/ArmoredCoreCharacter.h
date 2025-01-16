// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ArmoredCoreCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

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
	UInputAction* LArmFireAction;

	// TimerHandles
	FTimerHandle QuickBoostCoolTimeHandle;
	
	FTimerHandle AssertBoostLaunchHandle;

	FTimerHandle LArmFireTimerHandle;

	FTimerHandle ToggleIsJumpTimerHandle;

public:
	AArmoredCoreCharacter();
	

protected:
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void OnMoveComplete();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	// Jump & Fly
	virtual void Jump() override;
	
	void Fly();
	
	virtual void StopJumping() override;

	void ToggleIsJump();
	
	// Boost Function
	void BoostOn();
	
	void UpdateBoostGauge();

	void UpdateBoostState();

	
	// QuickBoost Function
	void QuickBoost();

	void ResetQuickBoostCoolTime();
	
	// AssertBoost Function
	void AssertBoost();

	void StartAssertBoostLaunch();

	void UpdateAssertBoostOnOff();

	// Attack Function
	void UpdateAttackState();

	void MakeProjectile();
	
	void FirePressed();

	void FireReleased();

	void RotateCharacterToAimDirection();

	// ETC
	void ToggleRotationToMovement();

	void UpdateCameraSettingsByMovementState();
	
	void LerpRotateCameraByMoveInput();

	
private:
	FVector2D MovementVector;
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Leg;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LArm;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* RArm;

	UPROPERTY(EditAnywhere)
	class USceneComponent* LArmFirePos;

	UPROPERTY(EditAnywhere)
	class USceneComponent* RArmFirePos;

	
	// BaseMove variance
	bool IsMove;
	
	float WalkSpeed;
	
	FRotator WalkRotationRate;

	bool IsJumping;

	bool IsFlying;
	
	// Boost variance
	bool IsBoostOn;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Boost")
	float BoostSpeed;
	
	FRotator BoostRotationRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Boost")
	float BoostGauge;
	
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
	
	// ETC
	float WalkCameraLagSpeed;
	
	UPROPERTY(EditAnywhere)
	float BoostCameraLagSpeed;
	
	//UPROPERTY(EditAnywhere)
	//float QuickBoostCameraLagSpeed;

	float BaseGravity;
	
	UPROPERTY(EditAnywhere)
	float FlyingGravity;

	UPROPERTY(EditAnywhere)
	float MouseSensitivity;

	float ElapsedTime;
};

