// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBoostGaugeUI.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UPlayerBoostGaugeUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerBoostGaugeUI(AArmoredCoreCharacter* player);
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BoostGauge;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BoostOnBorder;
};
