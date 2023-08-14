#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types.hpp"
#include "utils.hpp"

class Renderer
{
	sf::RenderWindow& window;
	Camera camera;
	float rotation_angle;

	void drawTriangle(Triangle triangle) const noexcept;

	[[nodiscard]] auto getProjectionMatrix(float fov, float z_near, float z_far) const noexcept -> Matrix<4>;
	[[nodiscard]] auto getXRotationMatrix() const noexcept -> Matrix<4>;
	[[nodiscard]] auto getYRotationMatrix() const noexcept -> Matrix<4>;
	[[nodiscard]] auto getIdentityMatrix() const noexcept -> Matrix<4>;

	[[nodiscard]] auto getProjectedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle;
	[[nodiscard]] auto getRotatedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle;
	[[nodiscard]] auto getTransformedTriangle(const Triangle& triangle, const sf::Vector3f& position) const noexcept -> Triangle;
public:
	explicit Renderer(sf::RenderWindow& window) noexcept;
	[[nodiscard]] Camera& getCamera() noexcept;
	void render(const Entity& entity, float delta) noexcept;
};
