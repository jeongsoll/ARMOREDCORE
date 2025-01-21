// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkState.h"

#include "ArmoredCoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWalkState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UWalkState::EnterState"));
}

void UWalkState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	ChangeCameraOffset(Character,DeltaTime);
	if (Character->MovementVector == FVector2D::ZeroVector)
	{
		Character->IsMove = false;
		Character->UpdatePlayerState(EPlayerState::Idle);
	}
}

void UWalkState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UWalkState::ExitState"));
}
