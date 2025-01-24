// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWeaponUI.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UPlayerWeaponUI : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftShoulderRemain;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftShoulderMax;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftArmRemain;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftArmMax;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RightShoulderRemain;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RightShoulderMax;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RightArmRemain;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RightArmMax;

	UFUNCTION()
	void SetRemainWeaponUI(float LB, float LA, float RB, float RA);
	UFUNCTION()
	void SetMaxWeaponUI(float LB, float LA, float RB, float RA);
};
