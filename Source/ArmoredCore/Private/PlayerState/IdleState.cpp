// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"

void UIdleState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UIdleState::EnterState"));
	Character->IsMove = false;
	Character->IsBoostOn = false;

}

void UIdleState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	ChangeCameraOffset(Character,DeltaTime);
	if (Character->MovementVector != FVector2D::ZeroVector)
		Character->UpdatePlayerState(EPlayerState::Walking);
}

void UIdleState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UIdleState::ExitState"));
	Character->IsMove = true;
}

void UIdleState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	Super::ChangeCameraOffset(Character , DeltaTime);
}
