// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertBoostState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAssertBoostState::EnterState(class AArmoredCoreCharacter* Character)
{
	if (Character->BoostGauge > 0.0f)
		Character->IsAssertBoostOn = true;
}

void UAssertBoostState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->IsAssertBoostOn)
	{
		// 부스터 사용시간 초기화
		Character->BoostUsedTime = 0.0f;
		
		Character->IsMove = true;
		Character->IsBoostOn = true;
		Character->MouseSensitivity = 0.1f;

		// 어썰트 부스트 방향 설정 및 캐릭터 회전 고정
		Character->AssertBoostDir = Character->GetFollowCamera()->GetForwardVector();
		Character->AssertBoostDir.Normalize();
		FRotator ControlRotation = Character->GetControlRotation();
		FRotator YawRotation(0, ControlRotation.Yaw,0);
		Character->SetActorRotation(YawRotation);

		// 순간 대쉬 후 공중이동
		if (Character->IsAssertBoostLaunch)
		{
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			Character->GetCharacterMovement()->GravityScale = Character->FlyingGravity;
			Character->AddMovementInput(Character->AssertBoostDir,7.0f,true);
			
			Character->BoostGauge -= DeltaTime * 25.0f;
		}
	}
	
	// 어썰트 부스트를 직접끄거나 부스트 게이지가 0이 된다면 falling으로 변경
	if (!Character->IsAssertBoostOn || Character->BoostGauge < 0.0f)
	{
		if (Character->IsAssertBoostLaunch)
		{
			Character->IsAssertBoostLaunch = false;
			Character->MouseSensitivity = 1.0f;
		}
		Character->UpdatePlayerState(EPlayerState::Falling);
	}
}

void UAssertBoostState::ExitState(class AArmoredCoreCharacter* Character)
{
	Character->IsAssertBoostOn = false;
}
