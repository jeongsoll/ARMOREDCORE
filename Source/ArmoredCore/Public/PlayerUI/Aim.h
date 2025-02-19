// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Aim.generated.h"

enum class EPlayerUsedWeaponPos : uint8;
/**
 * 
 */
UCLASS()
class ARMOREDCORE_API UAim : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SetProgBar();
	UFUNCTION()
	void SetAmmoValue(EPlayerUsedWeaponPos weaponPos, float currentAmmo, float maxAmmo);
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* LShoulderProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* LArmProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* RShoulderProgBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* RArmProgBar;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* LArmProgBarMatInst;
	UPROPERTY()
	class UMaterialInstanceDynamic* RArmProgBarMatInst;
	UPROPERTY()
	class UMaterialInstanceDynamic* RShoulderProgBarMatInst;
	
	UPROPERTY()
	float RACurrentAmmo{1.0f};
	UPROPERTY()
	float RAMaxAmmo{1.0f};
	UPROPERTY()
	float RBCurrentAmmo{1.0f};
	UPROPERTY()
	float RBMaxAmmo{1.0f};
};
