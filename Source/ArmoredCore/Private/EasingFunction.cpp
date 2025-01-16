// Fill out your copyright notice in the Description page of Project Settings.


#include "EasingFunction.h"

#include <ThirdParty/Imath/Deploy/Imath-3.1.9/include/Imath/ImathPlatform.h>


float UEasingFunction::GetEasedValue(EEasingType EasingType, float Alpha)
{
	switch (EasingType)
	{
	case EEasingType::EaseInQuint:
		return EaseInQuint(Alpha);
	case EEasingType::EaseOutQuint:
		return EaseOutQuint(Alpha);
	case EEasingType::EaseInElastic:
		return EaseInElastic(Alpha);
	case EEasingType::EaseOutElastic:
		return EaseOutElastic(Alpha);
	default:
		return Alpha;
	}
}

float UEasingFunction::UpdateEasedAlpha(EEasingType EasingType, float& ElapsedTime, float TransitionDuration)
{
	float DeltaTime = GWorld->GetDeltaSeconds();
	ElapsedTime += DeltaTime;

	float Alpha = ElapsedTime / TransitionDuration;
	if (Alpha >= 1.0f)
	{
		Alpha = 1.0f;
	}

	return GetEasedValue(EasingType, Alpha);
}

float UEasingFunction::EaseInQuint(float Alpha)
{
	return FMath::Pow(Alpha, 5);
}

float UEasingFunction::EaseOutQuint(float Alpha)
{
	return 1 - FMath::Pow(1 - Alpha, 5);
}

float UEasingFunction::EaseInElastic(float Alpha)
{
	const float c5 = (2 * PI) / 4.5f;
	return Alpha == 0
		? 0
		: Alpha == 1
		? 1
		: -FMath::Pow(2, 10 * Alpha - 10) * FMath::Sin((Alpha * 10 - 10.75f) * c5);
}

float UEasingFunction::EaseOutElastic(float Alpha)
{
	const float c5 = (2 * PI) / 4.5f;
	return Alpha == 0
		? 0
		: Alpha == 1
		? 1
		: FMath::Pow(2, -10 * Alpha) * FMath::Sin((Alpha * 10 - 0.75f) * c5) + 1;
}