#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types.hpp"
#include "utils.hpp"

class Renderer
{
	sf::RenderWindow& window;

	void drawTriangle(Triangle triangle) const noexcept;
	[[nodiscard]] auto getProjectionMatrix(float fov, float z_near, float z_far) const noexcept -> Matrix<4>;
	[[nodiscard]] auto getProjectedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle;
	[[nodiscard]] auto getTransformedTriangle(const Triangle& triangle, const sf::Vector3f& camera) const noexcept -> Triangle;
public:
	explicit Renderer(sf::RenderWindow& window) noexcept;
	void render(const std::vector<Triangle>& model, const sf::Vector3f& camera) const noexcept;
};
