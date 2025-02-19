// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPUI.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UPlayerHPUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerHPUI();

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHPText;

	UPROPERTY()
	float maxHP;
	UPROPERTY()
	float currentHP;
};
