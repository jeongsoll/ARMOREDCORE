// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClear.h"

void UGameClear::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameClear::PlayMyAnimation()
{
	if (MissionComplete)
	{
		PlayAnimation(MissionComplete);
	}
}
