// Fill out your copyright notice in the Description page of Project Settings.


#include "LandState.h"

#include "ArmoredCoreCharacter.h"
#include "Kismet/GameplayStatics.h"

void ULandState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("ULandState::EnterState"));
	UGameplayStatics::PlaySound2D(Character,Character->LandingSound);
}

void ULandState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->PreviousStateEnum == EPlayerState::Falling)
	{
		// 착지 연출

		if (Character->MovementVector == FVector2D::ZeroVector)
		{
			Character->PlayMyMontage(Character->LandMontage);
			Character->UpdatePlayerState(EPlayerState::Idle);
		}
		else
			Character->UpdatePlayerState(EPlayerState::Walking);
	}
}

void ULandState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("ULandState::ExitState"));
}

void ULandState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	Super::ChangeCameraOffset(Character , DeltaTime);
}
