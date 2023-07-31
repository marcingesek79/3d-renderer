#pragma once
#include <SFML/Graphics.hpp>
#include "renderer.hpp"

class Window
{
	const uint32_t width;
	const uint32_t height;
	const std::string title;
	sf::RenderWindow window;
	Renderer& renderer;

	void handleEvents() noexcept;

public:
	Window(uint32_t width, uint32_t height, const std::string& title, Renderer& renderer) noexcept;
	void run() noexcept;
};
