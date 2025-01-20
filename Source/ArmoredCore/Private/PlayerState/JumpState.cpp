// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"

void UJumpState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Display, TEXT("Entering UJumpState::EnterState"));
	Character->IsJumped = true;
}

void UJumpState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	Character->UpdatePlayerState(EPlayerState::Flying);
}

void UJumpState::ExitState(class AArmoredCoreCharacter* Character)
{
}
