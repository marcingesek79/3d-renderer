#pragma once
#include <SFML/Graphics.hpp>

class Window
{
	uint32_t width;
	uint32_t height;
	std::string title;
	sf::RenderWindow window;

public:
	Window(uint32_t width, uint32_t height, const std::string& title) noexcept;
	void run() noexcept;
};
