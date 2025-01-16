// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunction.generated.h"


/**
 * 
 */
enum class EEasingType
{
	EaseInQuint,
	EaseOutQuint,
	EaseInElastic,
	EaseOutElastic,
};

UCLASS()
class ARMOREDCORE_API UEasingFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static float EaseInQuint(float Time);
	static float EaseOutQuint(float Time);
	static float EaseInElastic(float Time);
	static float EaseOutElastic(float Time);
	
public:
	static float ApplyEasing(EEasingType EasingType, float Time);
};
