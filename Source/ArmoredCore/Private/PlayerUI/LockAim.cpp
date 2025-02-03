// Fill out your copyright notice in the Description page of Project Settings.


#include "LockAim.h"

#include "ArmoredCoreCharacter.h"
#include "JS_Boss.h"
#include "Components/Image.h"

void ULockAim::NativeConstruct()
{
	Super::NativeConstruct();
	
	UMaterialInterface* EnemyHPProgBarInterface = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/JJH/Aim/LockedEnemyHPProgBar.LockedEnemyHPProgBar'"));
	if (EnemyHPProgBarInterface)
	{
		EnemyHPProgBarMatInst = UMaterialInstanceDynamic::Create(EnemyHPProgBarInterface, this);
		if (EnemyHPProgBar && EnemyHPProgBarMatInst)
		{
			EnemyHPProgBar->SetBrushFromMaterial(EnemyHPProgBarMatInst);
		}
	}
}

void ULockAim::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	SetProgBar();
}

void ULockAim::SetProgBar()
{
	Super::SetProgBar();
	float HPper = CurrentHP / MaxHP * 0.25f;
	if (EnemyHPProgBarMatInst)
	{
		EnemyHPProgBarMatInst->SetScalarParameterValue(FName("Percentage"), HPper);
	}
}

void ULockAim::SetHPValue(float currentHP, float maxHP)
{
	CurrentHP = currentHP;
	MaxHP = maxHP;
}
