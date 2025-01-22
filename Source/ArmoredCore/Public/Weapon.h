// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmoredCoreCharacter.h"
#include "UObject/Object.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UWeapon : public UObject
{
	GENERATED_BODY()
public:
	UWeapon();

	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	float ReloadTime;
	UPROPERTY(EditAnywhere)
	int32 Magazine;
	UPROPERTY(EditAnywhere)
	int32 MaxArmor;
	UPROPERTY(EditAnywhere)
	int32 RemainArmor;

	void SetChoosenWeapon(EPlayerWeapon choosedWeapon);
};
