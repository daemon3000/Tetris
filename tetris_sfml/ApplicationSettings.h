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
		sf::Vector2u iconSize;
		const sf::Uint8 *iconPixelData;
		unsigned int bitsPerPixel;
		bool fullscreen;

		ApplicationSettings() :
			title("SFML Game"),
			backgroundColor(0, 0, 0, 255),
			windowSize(800, 600),
			iconSize(0, 0),
			iconPixelData(nullptr),
			bitsPerPixel(32),
			fullscreen(false) { }
	};
}
