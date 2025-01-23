// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPUI.h"

#include "ArmoredCoreCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHPUI::NativeConstruct()
{
	Super::NativeConstruct();
	maxHP = 9080;
}

void UPlayerHPUI::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry , DeltaSeconds);
	AArmoredCoreCharacter* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (player)
	{
		SetPlayerHPUI(player->CurrentHP);
	}
}

void UPlayerHPUI::SetPlayerHPUI(float playerHP)
{
	float per = playerHP / maxHP;
	HPBar->SetPercent(per);

	CurrentHPText->SetText(FText::AsNumber(playerHP));
}
