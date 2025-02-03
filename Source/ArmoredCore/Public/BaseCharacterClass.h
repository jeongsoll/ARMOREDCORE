// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacterClass.generated.h"

UCLASS()
class ARMOREDCORE_API ABaseCharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void CharacterTakeDamage(float damage);

	UFUNCTION(BlueprintCallable)
	virtual void Dead();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DieMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaggerGauge;
	
};
