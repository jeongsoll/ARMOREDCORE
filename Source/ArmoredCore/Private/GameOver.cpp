// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameOver::PlayMyAnimation()
{
	if (OverlayAnimation && TextAnimation && EndAnimation)
	{
		PlayAnimation(OverlayAnimation);
		PlayAnimation(TextAnimation);
		PlayAnimation(EndAnimation);
	}
}
