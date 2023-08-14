#include "renderer.hpp"

Renderer::Renderer(sf::RenderWindow& window) noexcept
	: window{ window }, camera{}, rotation_angle{}
{
}

Camera& Renderer::getCamera() noexcept
{
	return this->camera;
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

[[nodiscard]] auto Renderer::getProjectionMatrix(float fov, float z_near, float z_far) const noexcept -> Matrix<4>
{
	Matrix<4> projection_matrix{};
	const auto [WIDTH, HEIGHT] = this->window.getSize();

	auto aspect_ratio = static_cast<float>(HEIGHT) / static_cast<float>(WIDTH);
	auto fov_coeff = 1.0f / std::tan(utils::toRadians(fov * 0.5f));
	projection_matrix.get(0, 0) = aspect_ratio * fov_coeff;
	projection_matrix.get(1, 1) = fov_coeff;
	projection_matrix.get(2, 2) = (z_far + z_near) / (z_far - z_near);
	projection_matrix.get(3, 2) = (2.0f * z_far * z_near) / (z_near - z_far);
	projection_matrix.get(2, 3) = 1.0f;

	return projection_matrix;
}

[[nodiscard]] auto Renderer::getProjectedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle
{
	std::array<sf::Vector3f, 3> triangle_vertices{ triangle.a, triangle.b, triangle.c };
	const auto [WIDTH, HEIGHT] = this->window.getSize();

	for (auto& vertex : triangle_vertices)
	{
		std::vector<float> vector{ vertex.x, vertex.y, vertex.z, 1.0f};
		std::vector<float> projected_vector = utils::multiplyVectorByMatrix(vector, matrix);

		auto projected_x = (projected_vector.at(0) + 1.0f) * WIDTH * 0.5f;
		auto projected_y = (projected_vector.at(1) + 1.0f) * HEIGHT * 0.5f;
		auto projected_z = projected_vector.at(2);

		vertex = { projected_x, projected_y, projected_z };
	}

	Triangle projected_triangle{ triangle_vertices.at(0), triangle_vertices.at(1), triangle_vertices.at(2) };
	return projected_triangle;
}

auto Renderer::getXRotationMatrix() const noexcept -> Matrix<4>
{
	Matrix<4> matrix{};

	matrix.get(0, 0) = 1.0f;
	matrix.get(1, 1) = std::cosf(this->rotation_angle);
	matrix.get(1, 2) = std::sinf(this->rotation_angle);
	matrix.get(2, 1) = -std::sinf(this->rotation_angle);
	matrix.get(2, 2) = std::cosf(this->rotation_angle);
	matrix.get(3, 3) = 1.0f;

	return matrix;
}

auto Renderer::getYRotationMatrix() const noexcept -> Matrix<4>
{
	Matrix<4> matrix{};

	matrix.get(0, 0) = std::cosf(this->rotation_angle);
	matrix.get(1, 1) = 1.0f;
	matrix.get(0, 2) = -std::sinf(this->rotation_angle);
	matrix.get(2, 0) = std::sinf(this->rotation_angle);
	matrix.get(2, 2) = std::cosf(this->rotation_angle);
	matrix.get(3, 3) = 1.0f;

	return matrix;
}

auto Renderer::getIdentityMatrix() const noexcept -> Matrix<4>
{
	Matrix<4> matrix{};

	matrix.get(0, 0) = 1.0f;
	matrix.get(1, 1) = 1.0f;
	matrix.get(2, 2) = 1.0f;
	matrix.get(3, 3) = 1.0f;

	return matrix;
}

auto Renderer::getRotatedTriangle(const Triangle& triangle, const Matrix<4>& matrix) const noexcept -> Triangle
{
	std::array<sf::Vector3f, 3> triangle_vertices{ triangle.a, triangle.b, triangle.c };

	for (auto& vertex : triangle_vertices)
	{
		std::vector<float> vector{ vertex.x, vertex.y, vertex.z, 1.0f };
		std::vector<float> rotated_vector = utils::multiplyVectorByMatrix(vector, matrix);
		vertex = { rotated_vector.at(0), 1 - rotated_vector.at(1), rotated_vector.at(2) };
	}

	Triangle rotated_triangle{ triangle_vertices.at(0), triangle_vertices.at(1), triangle_vertices.at(2) };
	return rotated_triangle;
}


auto Renderer::getTransformedTriangle(const Triangle& triangle, const sf::Vector3f& position) const noexcept -> Triangle
{
	std::array<sf::Vector3f, 3> triangle_vertices{ triangle.a, triangle.b, triangle.c };

	for (auto& vertex : triangle_vertices)
	{
		auto new_x = vertex.x - this->camera.x - position.x;
		auto new_y = vertex.y + this->camera.y + position.y + utils::CAMERA_Y_OFFSET;
		auto new_z = vertex.z + this->camera.z + position.z + utils::CAMERA_Z_OFFSET;
		vertex = { new_x, new_y, new_z };
	}

	Triangle transformed_triangle{ triangle_vertices.at(0), triangle_vertices.at(1), triangle_vertices.at(2) };
	return transformed_triangle;
}

void Renderer::render(const Entity& entity, float delta) noexcept
{
	const auto& [model, rotation, position] = entity;

	this->rotation_angle += rotation.speed * delta;
	auto projection_matrix = this->getProjectionMatrix(utils::FOV, utils::Z_NEAR, utils::Z_FAR);
	auto rotation_matrix = this->getIdentityMatrix();

	if (rotation.dir == RotationDirection::X)
		rotation_matrix = this->getXRotationMatrix();
	else if (rotation.dir == RotationDirection::Y)
		rotation_matrix = this->getYRotationMatrix();

	for (const auto& triangle : model)
	{
		auto rotated_triangle = this->getRotatedTriangle(triangle, rotation_matrix);
		auto transformed_triangle = this->getTransformedTriangle(rotated_triangle, position);
		auto projected_triangle = this->getProjectedTriangle(transformed_triangle, projection_matrix);
		this->drawTriangle(projected_triangle);
	}
}
