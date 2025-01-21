// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UFlyState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UFlyState::EnterState"));
	
	if (Character->BoostGauge > 0.0f)
	{
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		Character->GetCharacterMovement()->GravityScale = Character->FlyingGravity;
	}
	else
	{
		Character->UpdatePlayerState(EPlayerState::Falling);
	}
	
	
}

void UFlyState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	// 공중에서 움직임이 없을 때 플레이어의 input으로 힘의방향쪽으로 몸을 돌리는 기능으로 인해
	// 플레이어의 rotation이 이상하게 돌아가는 현상을 방지하기 위한 코드
	// 이 코드가 없으면 fly를 할 때 방향키 입력이 없으면 플레이어의 몸이 이상하게 돌아간다

	if (Character->MovementVector == FVector2D::ZeroVector)
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
		
	if (Character->BoostGauge > 0.0f)
	{
		ChangeCameraOffset(Character,DeltaTime);

		Character->IsMove = true;
		Character->IsBoostOn = true;
		Character->BoostUsedTime = 0.0f;
		Character->BoostGauge -= DeltaTime * 15.0f;
		Character->AddMovementInput(Character->GetActorUpVector(),0.75,true);
	}
	else
	{
		Character->UpdatePlayerState(EPlayerState::Falling);
	}
}

void UFlyState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("UFlyState::ExitState"));
}

void UFlyState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	newSocket = UKismetMathLibrary::VInterpTo(Character->GetCameraBoom()->SocketOffset,FVector(-80,0,-180),GetWorld()->GetDeltaSeconds(), 1.0f);
	Character->GetCameraBoom()->SocketOffset = newSocket;
}

