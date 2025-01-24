// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"

void UJumpState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UJumpState::EnterState"));
}

void UJumpState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	Character->UpdatePlayerState(EPlayerState::Flying);
}

void UJumpState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UJumpState::ExitState"));
}

void UJumpState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	Super::ChangeCameraOffset(Character , DeltaTime);
}
