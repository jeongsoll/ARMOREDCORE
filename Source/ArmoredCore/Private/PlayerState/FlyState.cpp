// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFlyState::EnterState(class AArmoredCoreCharacter* Character)
{
	if (Character->IsJumped)
	{
		Character->IsJumped = false;
		Character->IsFlying = true;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void UFlyState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (!Character->IsMove && Character->IsFlying)
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	else if (Character->IsMove && Character->IsFlying)
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	
		
	if (Character->GetCharacterMovement()->IsFlying() && Character->BoostGauge > 0.0f)
	{
		Character->BoostUsedTime = 0.0f;
		Character->BoostGauge -= DeltaTime * 15.0f;
		Character->AddMovementInput(Character->GetActorUpVector(),0.75,true);
	}
	else if (Character->BoostGauge < 0.0f)
	{
		Character->UpdatePlayerState(EPlayerState::Falling);
	}
}

void UFlyState::ExitState(class AArmoredCoreCharacter* Character)
{
	Character->IsFlying = false;
}
