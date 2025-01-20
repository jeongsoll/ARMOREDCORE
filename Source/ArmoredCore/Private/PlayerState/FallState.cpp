// Fill out your copyright notice in the Description page of Project Settings.


#include "FallState.h"

#include "ArmoredCoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFallState::EnterState(class AArmoredCoreCharacter* Character)
{
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	Character->GetCharacterMovement()->GravityScale = Character->BaseGravity;

	if (Character->BoostGauge < 0.0f)
	{
		Character->BoostGauge = 0.0f;
	}
}

void UFallState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->GetCharacterMovement()->IsWalking())
		Character->UpdatePlayerState(EPlayerState::Walking);
}

void UFallState::ExitState(class AArmoredCoreCharacter* Character)
{
	
}
