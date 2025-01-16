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

float UEasingFunction::UpdateEasedAlpha(EEasingType EasingType, float& CurrentTime, float TotalDuration, float DeltaTime)
{
	
	CurrentTime += DeltaTime;

	float Alpha = CurrentTime / TotalDuration;
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

	if (Alpha == 0)
	{
		return 0;
	}
	else if (Alpha == 1)
	{
		return 1;
	}
	else
	{
		return -FMath::Pow(2, 10 * Alpha - 10) * FMath::Sin((Alpha * 10 - 10.75f) * c5);
	}
}

float UEasingFunction::EaseOutElastic(float Alpha)
{
	const float c5 = (2 * PI) / 4.5f;

	if (Alpha == 0)
	{
		return 0;
	}
	else if (Alpha == 1)
	{
		return 1;
	}
	else
	{
		return FMath::Pow(2, -10 * Alpha) * FMath::Sin((Alpha * 10 - 0.75f) * c5) + 1;
	}
}