#pragma once

#include <SFML\Graphics.hpp>

namespace tetris
{
	namespace math
	{
		float clamp(float value, float min, float max);
		float clamp01(float value);
		float lerp(float from, float to, float t);
		float min(float a, float b);
		float max(float a, float b);
		int clamp(int value, int min, int max);
		int min(int a, int b);
		int max(int a, int b);
		bool isWithinRange(float value, float min, float max);
		bool isWithinRange(int value, int min, int max);
		int randomRange(int min, int max);
		
		namespace vector2
		{
			sf::Vector2f normalize(sf::Vector2f vec);
			sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f to, float t);
			float length(sf::Vector2f vec);
			float sqLength(sf::Vector2f vec);
		}
	}
}
