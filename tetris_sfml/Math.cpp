#include <random>
#include "Math.h"

using namespace tetris;

std::random_device rd;
std::default_random_engine generator(rd());

float math::clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

float math::clamp01(float value)
{
	if (value < 0.0f)
		return 0.0f;
	if (value > 1.0f)
		return 1.0f;
	return value;
}

float math::lerp(float from, float to, float t)
{
	return from + (to - from) * clamp01(t);
}

float math::min(float a, float b)
{
	if(a <= b)
		return a;
	else
		return b;
}

float math::max(float a, float b)
{
	if(a >= b)
		return a;
	else
		return b;
}

int math::clamp(int value, int min, int max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	return value;
}

int math::min(int a, int b)
{
	if(a <= b)
		return a;
	else
		return b;
}

int math::max(int a, int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

bool math::isWithinRange(float value, float min, float max)
{
	return value >= min && value <= max;
}

bool math::isWithinRange(int value, int min, int max)
{
	return value >= min && value <= max;
}

int math::randomRange(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max - 1);
	return distribution(generator);
}

sf::Vector2f math::vector2::normalize(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return (length > 0.0f) ? sf::Vector2f(vec.x / length, vec.y / length) : vec;
}

sf::Vector2f math::vector2::lerp(sf::Vector2f from, sf::Vector2f to, float t)
{
	t = clamp01(t);
	return sf::Vector2f(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t);
}

float math::vector2::length(sf::Vector2f vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float math::vector2::sqLength(sf::Vector2f vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}


