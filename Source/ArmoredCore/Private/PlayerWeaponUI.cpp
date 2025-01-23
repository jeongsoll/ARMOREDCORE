// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponUI.h"

#include "ArmoredCoreCharacter.h"
#include "Weapon.h"
#include "Components/TextBlock.h"

void UPlayerWeaponUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerWeaponUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	auto* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (player)
	{
		SetRemainWeaponUI(NULL,player->LArmWeapon->RemainArmor,player->RShoulderWeapon->RemainArmor,player->RArmWeapon->RemainArmor);
		SetMaxWeaponUI(NULL,player->LArmWeapon->Magazine,player->RShoulderWeapon->Magazine,player->RArmWeapon->Magazine);
	}
}

void UPlayerWeaponUI::SetRemainWeaponUI(float LB, float LA, float RB, float RA)
{
	LeftShoulderRemain->SetText(FText::AsNumber(LB));
	LeftArmRemain->SetText(FText::AsNumber(LA));
	RightShoulderRemain->SetText(FText::AsNumber(RB));
	RightArmRemain->SetText(FText::AsNumber(RA));
}

void UPlayerWeaponUI::SetMaxWeaponUI(float LB, float LA, float RB, float RA)
{
	LeftShoulderMax->SetText(FText::AsNumber(LB));
	LeftArmMax->SetText(FText::AsNumber(LA));
	RightShoulderMax->SetText(FText::AsNumber(RB));
	RightArmMax->SetText(FText::AsNumber(RA));
}
