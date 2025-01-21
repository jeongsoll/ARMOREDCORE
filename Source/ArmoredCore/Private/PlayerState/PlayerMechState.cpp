// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMechState.h"

#include "ArmoredCoreCharacter.h"
#include "GameFramework/SpringArmComponent.h"


// Add default functionality here for any IIPlayerState functions that are not pure virtual.

void IPlayerMechState::EnterState(class AArmoredCoreCharacter* Character)
{
}

void IPlayerMechState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
}

void IPlayerMechState::ExitState(class AArmoredCoreCharacter* Character)
{
}

void IPlayerMechState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->CurrentStateEnum != EPlayerState::Flying || Character->CurrentStateEnum != EPlayerState::AssertBoost)
	{
		newSocket = UKismetMathLibrary::VInterpTo(Character->GetCameraBoom()->SocketOffset,FVector(0,0,0),DeltaTime, 5.0f);
		Character->GetCameraBoom()->SocketOffset = newSocket;
	}
}
