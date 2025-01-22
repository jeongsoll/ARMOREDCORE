// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBoostGaugeUI.h"

#include "ArmoredCoreCharacter.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"

class AArmoredCoreCharacter;

void UPlayerBoostGaugeUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerBoostGaugeUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	AArmoredCoreCharacter* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (player)
	{
		SetPlayerBoostGaugeUI(player);
	}
}

void UPlayerBoostGaugeUI::SetPlayerBoostGaugeUI(AArmoredCoreCharacter* player)
{
	float per = player->BoostGauge / player->MaxBoostGauge;
	BoostGauge->SetPercent(per);

	if (player->IsBoostOn)
	{
		BoostOnBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BoostOnBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	
}
