#pragma once
#include "cmath"

enum class EEasingType
{
	EaseInQuint,
	EaseOutQuint,
	EaseInElastic,
	EaseOutElastic,
};

class Easing
{
private:
	static float EaseInQuint(float Time);
	static float EaseOutQuint(float Time);
	static float EaseInElastic(float Time);
	static float EaseOutElastic(float Time);
	
public:
	static float ApplyEasing(EEasingType EasingType, float Time);

};
