// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerMechState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerMechState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARMOREDCORE_API IPlayerMechState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 상태가 시작될 때 호출되는 메서드
	virtual void EnterState(class AArmoredCoreCharacter* Character) {};

	// 상태가 업데이트될 때 호출되는 메서드
	virtual void UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime) {};

	// 상태가 종료될 때 호출되는 메서드
	virtual void ExitState(class AArmoredCoreCharacter* Character) {};

	virtual void ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime);

	FVector newSocket;
};
