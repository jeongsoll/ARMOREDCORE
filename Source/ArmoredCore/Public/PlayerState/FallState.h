// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "PlayerMechState.h"
#include "UObject/Object.h"
#include "FallState.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UFallState : public UBaseState
{
	GENERATED_BODY()
public:
	virtual void EnterState(class AArmoredCoreCharacter* Character) override;
	virtual void UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime) override;
	virtual void ExitState(class AArmoredCoreCharacter* Character) override;
	virtual void ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime) override;
};
