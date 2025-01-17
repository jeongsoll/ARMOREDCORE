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

float UEasingFunction::UpdateEasedAlpha(EEasingType EasingType, float CurrentTime, float TotalDuration, float DeltaTime)
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
	const float c5 = (2.0f * PI) / 3.0f;

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
		return FMath::Pow(2.f, -10.f * Alpha) * FMath::Sin((Alpha * 10.f - 0.75f) * c5) + 1;
	}
}

float UEasingFunction::EaseOutBounce(float Alpha)
{
	if (Alpha < 1 / 2.75f)
	{
		return 7.5625f * Alpha * Alpha;
	}
	else if (Alpha < 2 / 2.75f)
	{
		Alpha -= 1.5f / 2.75f;
		return 7.5625f * Alpha * Alpha + 0.75f;
	}
	else if (Alpha < 2.5 / 2.75f)
	{
		Alpha -= 2.25f / 2.75f;
		return 7.5625f * Alpha * Alpha + 0.9375f;
	}
	else
	{
		Alpha -= 2.625f / 2.75f;
		return 7.5625f * Alpha * Alpha + 0.984375f;
	}
}

float UEasingFunction::EaseOutBack(float Alpha)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1;

	return 1 + c3 * FMath::Pow(Alpha - 1, 3) + c1 * FMath::Pow(Alpha - 1, 2);
}

float UEasingFunction::EaseInOutBack(float Alpha)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	if (Alpha < 0.5f)
	{
		return (FMath::Pow(2 * Alpha, 2) * ((c2 + 1) * 2 * Alpha - c2)) / 2;
	}
	else
	{
		return (FMath::Pow(2 * Alpha - 2, 2) * ((c2 + 1) * (Alpha * 2 - 2) + c2) + 2) / 2;
	}
}
