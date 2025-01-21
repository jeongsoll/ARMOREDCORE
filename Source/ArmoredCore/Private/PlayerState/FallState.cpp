// Fill out your copyright notice in the Description page of Project Settings.


#include "FallState.h"

#include "ArmoredCoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFallState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UFallState::EnterState"));
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	Character->GetCharacterMovement()->GravityScale = Character->BaseGravity;
}

void UFallState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->GetCharacterMovement()->IsWalking())
		Character->UpdatePlayerState(EPlayerState::Landing);
}

void UFallState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UFallState::ExitState"));
}
