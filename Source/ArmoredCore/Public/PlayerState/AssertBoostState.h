// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMechState.h"
#include "UObject/Object.h"
#include "AssertBoostState.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UAssertBoostState : public UObject, public IPlayerMechState
{
	GENERATED_BODY()
public:
	virtual void EnterState(class AArmoredCoreCharacter* Character) override;
	virtual void UpdateState(class AArmoredCoreCharacter* Character, float DeltaTime) override;
	virtual void ExitState(class AArmoredCoreCharacter* Character) override;
	virtual void ChangeCameraOffset(class AArmoredCoreCharacter* Character, float DeltaTime) override;
};
