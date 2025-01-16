// Fill out your copyright notice in the Description page of Project Settings.


#include "EasingFunction.h"

#include <ThirdParty/Imath/Deploy/Imath-3.1.9/include/Imath/ImathPlatform.h>


float UEasingFunction::ApplyEasing(EEasingType EasingType, float Time)
{
	switch (EasingType)
	{
	case EEasingType::EaseInQuint:
		return EaseInQuint(Time);
	case EEasingType::EaseOutQuint:
		return EaseOutQuint(Time);
	case EEasingType::EaseInElastic:
		return EaseInElastic(Time);
	case EEasingType::EaseOutElastic:
		return EaseOutElastic(Time);
	default:
		return Time;
	}
}

float UEasingFunction::EaseInQuint(float Time)
{
	return Time * Time * Time * Time * Time;
}

float UEasingFunction::EaseOutQuint(float Time)
{
	return 1 - std::pow(1 - Time, 5); 
}

float UEasingFunction::EaseInElastic(float Time)
{
	const float c4 = (2 * M_PI) / 3;

	if (Time == 0)
		return 0;
	if (Time == 1)
		return 1;

	return -std::pow(2, 10 * Time - 10) * std::sin((Time * 10 - 10.75) * c4);
}

float UEasingFunction::EaseOutElastic(float Time)
{
	const float c4 = (2 * M_PI) / 3;

	if (Time == 0)
		return 0;
	if (Time == 1)
		return 1;

	return std::pow(2, -10 * Time) * std::sin((Time * 10 - 0.75) * c4) + 1;
}
