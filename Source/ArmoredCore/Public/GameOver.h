// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UGameOver : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void PlayMyAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient, BlueprintReadWrite)
	class UWidgetAnimation* OverlayAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient, BlueprintReadWrite)
	class UWidgetAnimation* TextAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient, BlueprintReadWrite)
	class UWidgetAnimation* EndAnimation;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Title;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Retry;
	
};
