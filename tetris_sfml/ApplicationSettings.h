#pragma once

#include <SFML/Graphics.hpp>

namespace tetris
{
	struct ApplicationSettings
	{
	public:
		std::string title;
		sf::Color backgroundColor;
		sf::Vector2u windowSize;
		unsigned int bitsPerPixel;
		bool fullscreen;

		ApplicationSettings() :
			title("SFML Game"),
			backgroundColor(0, 0, 0, 255),
			windowSize(800, 600),
			bitsPerPixel(32),
			fullscreen(false) { }
	};
}
