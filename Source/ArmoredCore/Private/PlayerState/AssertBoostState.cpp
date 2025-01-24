// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertBoostState.h"

#include <filesystem>

#include "ArmoredCoreCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UAssertBoostState::EnterState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp,Warning,TEXT("UAssertBoostState::EnterState"));
	if (Character->BoostGauge > 0.0f)
		Character->IsAssertBoostOn = true;
}

void UAssertBoostState::UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	if (Character->IsAssertBoostOn)
	{
		// 카메라 offset 변경
		ChangeCameraOffset(Character,DeltaTime);
		
		// 부스터 사용시간 초기화
		Character->BoostUsedTime = 0.0f;

		// 부스터 상태 on으로 변경
		Character->IsBoostOn = true;

		// 마우스 감도 변경
		Character->MouseSensitivity = 0.1f;
		// 플레이어 input에 따른 rotation 변경 false
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;

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
			Character->AddMovementInput(Character->AssertBoostDir,Character->AssertBoostSpeed,true);
			
			Character->BoostGauge -= DeltaTime * 25.0f;
		}

		if (Character->BoostGauge <= 0.0f)
			Character->UpdatePlayerState(EPlayerState::Falling);
	}
	else
	{
		return;
	}
}

void UAssertBoostState::ExitState(class AArmoredCoreCharacter* Character)
{
	UE_LOG(LogTemp,Warning,TEXT("UAssertBoostState::ExitState"));

	Character->IsAssertBoostOn = false;
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	if (Character->IsAssertBoostLaunch)
	{
		Character->IsAssertBoostLaunch = false;
		Character->MouseSensitivity = 1.0f;
		Character->UpdatePlayerState(EPlayerState::Falling);
	}
}

void UAssertBoostState::ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime)
{
	newSocket = UKismetMathLibrary::VInterpTo(Character->GetCameraBoom()->SocketOffset,FVector(0,200,-15),DeltaTime, 3.0f);
	Character->GetCameraBoom()->SocketOffset = newSocket;
}
