// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Aim.generated.h"

/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UAim : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* LShoulderProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* LArmProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* RShoulderProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* RArmProgBar;

	class UMaterialInstanceDynamic* LArmProgBarMatInst;
	class UMaterialInstanceDynamic* RArmProgBarMatInst;
	class UMaterialInstanceDynamic* RShoulderProgBarMatInst;


	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetProgBar();
	void SetArmorValue(float currentArmor, float maxArmor);

	float CurrentArmor;
	float MaxArmor;
};
