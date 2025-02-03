// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClear.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UGameClear : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void PlayMyAnimation();
	
	UPROPERTY(meta = (BindWidgetAnim), Transient, BlueprintReadWrite)
	class UWidgetAnimation* MissionComplete;
};
