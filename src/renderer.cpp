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

[[nodiscard]] auto Renderer::getProjectedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle
{
	std::array<sf::Vector3<float>, 3> triangle_vertices{ triangle.a, triangle.b, triangle.c };
	const auto [WIDTH, HEIGHT] = this->window.getSize();

	for (auto& vertex : triangle_vertices)
	{
		std::vector<float> vector{ vertex.x - 0.5f, vertex.y - 0.5f, vertex.z + 3.0f, 1.0f};
		std::vector<float> projected_vector = calc::multiplyVectorByMatrix(vector, matrix);

		auto projected_x = (projected_vector.at(0) + 1.0f) * WIDTH * 0.5f;
		auto projected_y = (projected_vector.at(1) + 1.0f) * HEIGHT * 0.5f;
		auto projected_z = projected_vector.at(2);

		vertex = { projected_x, projected_y, projected_z };
	}

	Triangle projected_triangle{ triangle_vertices.at(0), triangle_vertices.at(1), triangle_vertices.at(2) };
	return projected_triangle;
}

[[nodiscard]] auto Renderer::getProjectionMatrix(float fov, float z_near, float z_far) const noexcept -> Matrix<4>
{
	Matrix<4> projection_matrix{};
	const auto [WIDTH, HEIGHT] = this->window.getSize();

	auto aspect_ratio = static_cast<float>(HEIGHT) / static_cast<float>(WIDTH);
	auto fov_coeff = 1.0f / std::tan(calc::toRadians(fov * 0.5f));
	projection_matrix.get(0, 0) = aspect_ratio * fov_coeff;
	projection_matrix.get(1, 1) = fov_coeff;
	projection_matrix.get(2, 2) = (z_far + z_near) / (z_far - z_near);
	projection_matrix.get(3, 2) = (2.0f * z_far * z_near) / (z_near - z_far);
	projection_matrix.get(2, 3) = 1.0f;

	return projection_matrix;
}

void Renderer::render(const std::vector<Triangle>& model) const noexcept
{
	auto projection_matrix = this->getProjectionMatrix(calc::FOV, calc::Z_NEAR, calc::Z_FAR);

	for (const auto& triangle : model)
	{
		auto projected_triangle = this->getProjectedTriangle(triangle, projection_matrix);
		this->drawTriangle(projected_triangle);
	}
}
