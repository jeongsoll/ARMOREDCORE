// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPUI.h"

#include "ArmoredCoreCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHPUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHPUI::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry , DeltaSeconds);
	auto* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (player)
	{
		currentHP = player->CurrentHP;
		maxHP = player->MaxHP;
		SetPlayerHPUI();
	}
}

void UPlayerHPUI::SetPlayerHPUI()
{
	float per = currentHP / maxHP;
	HPBar->SetPercent(per);

	CurrentHPText->SetText(FText::AsNumber(currentHP));
}
