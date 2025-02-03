// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerUI/Aim.h"
#include "LockAim.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API ULockAim : public UAim
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SetProgBar() override;
	UFUNCTION()
	void SetHPValue(float currentHP, float maxHP);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* EnemyHPProgBar;
	UPROPERTY()
	class UMaterialInstanceDynamic* EnemyHPProgBarMatInst;

	UPROPERTY()
	float CurrentHP{1.0f};
	UPROPERTY()
	float MaxHP{1.0f};
	
};
