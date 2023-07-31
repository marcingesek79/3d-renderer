#pragma once
#include <vector>
#include "types.hpp"

class Renderer
{
private:
	std::vector<Triangle> model;
public:
	Renderer(const std::vector<Triangle>& model) noexcept;
	void print() const noexcept;
};
