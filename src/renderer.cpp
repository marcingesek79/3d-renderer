#include "renderer.hpp"

Renderer::Renderer(sf::RenderWindow& window) noexcept
	: window{ window }
{
}

void Renderer::drawTriangle(Triangle triangle) const noexcept
{
	sf::Vertex line[] = { 
		{{ triangle.a.x, triangle.a.y }},
		{{ triangle.b.x, triangle.b.y }},
		{{ triangle.c.x, triangle.c.y }},
		{{ triangle.a.x, triangle.a.y }}
	};
	this->window.draw(line, 4, sf::LinesStrip);
}

void Renderer::render(const std::vector<Triangle>& model) const noexcept
{
	for (const auto& triangle : model)
	{
		this->drawTriangle(triangle);
	}
}
