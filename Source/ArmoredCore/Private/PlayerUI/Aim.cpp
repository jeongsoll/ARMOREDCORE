// Fill out your copyright notice in the Description page of Project Settings.


#include "Aim.h"

#include "ArmoredCoreCharacter.h"
#include "Weapon.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UAim::NativeConstruct()
{
	Super::NativeConstruct();
	UMaterialInterface* RAProgBarInterface = LoadObject<UMaterialInterface>(
		nullptr, TEXT("/Game/JJH/Aim/RAProgBar.RAProgBar"));
	if (RAProgBarInterface)
	{
		RArmProgBarMatInst = UMaterialInstanceDynamic::Create(RAProgBarInterface, this);
        
		if (RArmProgBar && RArmProgBarMatInst)
		{
			// 프로그레스 바에 Material 설정
			RArmProgBar->SetBrushFromMaterial(RArmProgBarMatInst);
		}
	}

	UMaterialInterface* RBProgBarInterface = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/JJH/Aim/RBProgBar.RBProgBar"));
	if (RBProgBarInterface)
	{
		RShoulderProgBarMatInst = UMaterialInstanceDynamic::Create(RBProgBarInterface, this);
		if (RShoulderProgBar && RShoulderProgBarMatInst)
		{
			RShoulderProgBar->SetBrushFromMaterial(RShoulderProgBarMatInst);
		}
	}
}

void UAim::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	SetProgBar();
}

void UAim::SetProgBar()
{
	float RAper = RACurrentAmmo / RAMaxAmmo * 0.25f;
	RArmProgBarMatInst->SetScalarParameterValue(FName("Percentage"), RAper);

	float RBper = RBCurrentAmmo / RBMaxAmmo * 0.25f;
	RShoulderProgBarMatInst->SetScalarParameterValue(FName("Percentage"), RBper);
}

void UAim::SetAmmoValue(EPlayerUsedWeaponPos weaponPos, float currentAmmo, float maxAmmo)
{
	if (weaponPos == EPlayerUsedWeaponPos::RArm)
	{
		RACurrentAmmo = currentAmmo;
		RAMaxAmmo = maxAmmo;
	}
	else if (weaponPos == EPlayerUsedWeaponPos::RShoulder)
	{
		RBCurrentAmmo = currentAmmo;
		RBMaxAmmo = maxAmmo;
	}
}
