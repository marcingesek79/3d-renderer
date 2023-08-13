#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types.hpp"
#include "calc.hpp"

class Renderer
{
	sf::RenderWindow& window;

	void drawTriangle(Triangle triangle) const noexcept;
	[[nodiscard]] auto getProjectedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle;
	[[nodiscard]] auto getProjectionMatrix(float fov, float z_near, float z_far) const noexcept -> Matrix<4>;
public:
	explicit Renderer(sf::RenderWindow& window) noexcept;
	void render(const std::vector<Triangle>& model) const noexcept;
};
