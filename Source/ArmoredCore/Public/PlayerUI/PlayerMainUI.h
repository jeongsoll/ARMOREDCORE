// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainUI.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UPlayerMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UPlayerHPUI* PlayerHPUI;

	UPROPERTY(meta=(BindWidget))
	class UPlayerBoostGaugeUI* PlayerBoostGaugeUI;

	UPROPERTY(meta=(BindWidget))
	class UPlayerWeaponUI* PlayerWeaponUI;

	UPROPERTY(meta=(BindWidget))
	class UAim* PlayerAim;

	UPROPERTY(meta=(BindWidget))
	class ULockAim* PlayerLockAim;
	
};
