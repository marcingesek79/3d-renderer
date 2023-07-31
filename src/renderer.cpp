#include "renderer.hpp"

Renderer::Renderer(const std::vector<Triangle>& model) noexcept
	: model{ model }
{
}

void Renderer::print() const noexcept
{
	for (const auto& elem : this->model)
	{
		std::cout << elem << std::endl;
	}
}