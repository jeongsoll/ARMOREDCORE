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
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BoostOnAction;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QuickBoostAction;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AssertBoostAction;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LArmFireAction;
	
	FTimerHandle QuickBoostCoolTimeHandle;
	
	FTimerHandle AssertBoostLaunchHandle;

	FTimerHandle LArmFireTimerHandle;

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

	virtual void Jump() override;
	
	virtual void StopJumping() override;
	
	void ToggleRotationToMovement();

	void LerpRotateCameraByMoveInput();

	// Boost Function
	void BoostOn();

	void QuickBoost();

	void UpdateBoostState();

	void UpdateCameraSettingsByMovementState();

	void ResetQuickBoostCoolTime();

	void Fly();

	void AssertBoost();

	void StartAssertBoostLaunch();

	void UpdateAssertBoostOnOff();

	void UpdateBoostGauge();

	// attack function
	void UpdateAttackState();

	void MakeProjectile();
	
	void FirePressed();

	void FireOnGoing();

	void FireReleased();

	void RotateCharacterToAimDirection();

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
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory;
	
	UPROPERTY(EditAnywhere)
	bool IsMove;
	
	// Boost Variance
	UPROPERTY(EditAnywhere)
	bool IsBoostOn;

	UPROPERTY(EditAnywhere)
	bool IsAssertBoostOn;
	
	UPROPERTY(EditAnywhere)
	bool CanQuickBoost;

	UPROPERTY(EditAnywhere)
	bool IsQuickBoostTrigger;
	
	UPROPERTY(EditAnywhere)
	FVector QuickBoostDir;

	UPROPERTY(EditAnywhere)
	FVector AssertBoostDir;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float QuickBoostSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float QuickBoostCoolTime;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BoostSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator WalkRotationRate;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator BoostRotationRate;

	UPROPERTY(EditAnywhere)
	bool IsAssertBoostLaunch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostGauge;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsBoostChargeStart;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BoostUsedTime;

	// attack variance
	UPROPERTY(EditAnywhere)
	bool IsAttacking;
	
	// camera variance
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WalkCameraLagSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BoostCameraLagSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float QuickBoostCameraLagSpeed;

	UPROPERTY(EditAnywhere)
	float BaseGravity;
	
	UPROPERTY(EditAnywhere)
	float FlyingGravity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MouseSensitivity;

	UPROPERTY(EditAnywhere)
	FVector AimDirection;
};

