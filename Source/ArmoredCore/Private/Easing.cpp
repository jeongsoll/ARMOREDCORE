#include "C:\Project\ARMOREDCORE\Intermediate\Build\Win64\x64\ArmoredCoreEditor\Development\UnrealEd\SharedPCH.UnrealEd.Project.ValApi.Cpp20.InclOrderUnreal5_4.h"
#include "Easing.h"

#include <ThirdParty/hlslcc/hlslcc/src/hlslcc_lib/compiler.h>


float Easing::ApplyEasing(EEasingType EasingType, float Time)
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

float Easing::EaseInQuint(float Time)
{
	return Time * Time * Time * Time * Time;
}

float Easing::EaseOutQuint(float Time)
{
	return 1 - std::pow(1 - Time, 5); 
}

float Easing::EaseInElastic(float Time)
{
	const float c4 = (2 * M_PI) / 3;

	if (Time == 0)
		return 0;
	if (Time == 1)
		return 1;

	return -std::pow(2, 10 * Time - 10) * std::sin((Time * 10 - 10.75) * c4);
}

float Easing::EaseOutElastic(float Time)
{
	const float c4 = (2 * M_PI) / 3;

	if (Time == 0)
		return 0;
	if (Time == 1)
		return 1;

	return std::pow(2, -10 * Time) * std::sin((Time * 10 - 0.75) * c4) + 1;
}


