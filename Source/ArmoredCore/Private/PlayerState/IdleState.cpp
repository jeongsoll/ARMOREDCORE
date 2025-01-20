// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"

void UIdleState::EnterState(class AArmoredCoreCharacter* Character)
{
	Character->IsMove = false;
}

void UIdleState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->PreviousStateEnum == EPlayerState::Falling)
	{
		//Character->IsLanding = true;
	}
}

void UIdleState::ExitState(class AArmoredCoreCharacter* Character)
{
}
