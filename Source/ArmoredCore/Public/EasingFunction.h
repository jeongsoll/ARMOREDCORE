// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunction.generated.h"


/**
 * 
 */
UENUM(BlueprintType)
enum class EEasingType : uint8
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
	// Ease In Quint
	static float EaseInQuint(float Alpha);

	// Ease Out Quint
	static float EaseOutQuint(float Alpha);

	// Ease In Elastic
	static float EaseInElastic(float Alpha);

	// Ease Out Elastic
	static float EaseOutElastic(float Alpha);
	
public:
	UFUNCTION(BlueprintCallable, Category = "Easing")
	static float GetEasedValue(EEasingType EasingType, float Alpha);
	
	UFUNCTION(BlueprintCallable, Category = "Easing")
	static float UpdateEasedAlpha(EEasingType EasingType, float& CurrentTime, float TotalDuration, float DeltaTime);
};
