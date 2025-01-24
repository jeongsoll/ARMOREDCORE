// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"

void UBaseState::EnterState(class AArmoredCoreCharacter* Character)
{
	IPlayerMechState::EnterState(Character);
}

void UBaseState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	IPlayerMechState::UpdateState(Character , DeltaTime);
}

void UBaseState::ExitState(class AArmoredCoreCharacter* Character)
{
	IPlayerMechState::ExitState(Character);
}

void UBaseState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	IPlayerMechState::ChangeCameraOffset(Character , DeltaTime);
}
