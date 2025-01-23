// Fill out your copyright notice in the Description page of Project Settings.


#include "Aim.h"

#include "ArmoredCoreCharacter.h"
#include "Weapon.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UAim::NativeConstruct()
{
	Super::NativeConstruct();
	UMaterialInterface* MaterialInterface = LoadObject<UMaterialInterface>(
		nullptr, TEXT("/Game/JJH/Asset/LAProgBar.LAProgBar"));
	if (MaterialInterface)
	{
		LArmProgBarMatInst = UMaterialInstanceDynamic::Create(MaterialInterface, this);
        
		if (LArmProgBar && LArmProgBarMatInst)
		{
			// 프로그레스 바에 Material 설정
			LArmProgBar->SetBrushFromMaterial(LArmProgBarMatInst);
		}
	}
	CurrentArmor = 1;
	MaxArmor = 1;
}

void UAim::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	SetProgBar();
}

void UAim::SetProgBar()
{

	float LAper = CurrentArmor / MaxArmor * 0.25f;

}

void UAim::SetArmorValue(float currentArmor, float maxArmor)
{
	CurrentArmor = currentArmor;
	MaxArmor = maxArmor;
}
