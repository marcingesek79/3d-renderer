#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types.hpp"

class Renderer
{
	sf::RenderWindow& window;

	void drawTriangle(Triangle triangle) const noexcept;
public:
	explicit Renderer(sf::RenderWindow& window) noexcept;
	void render(const std::vector<Triangle>& model) const noexcept;
};
