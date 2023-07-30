#include <iostream>
#include "../include/window.hpp"

int main()
{
	const uint32_t WIDTH{ 1280 };
	const uint32_t HEIGHT{ 720 };
	const std::string TITLE{ "3D Renderer" };

	Window window{ WIDTH, HEIGHT, TITLE };
	window.run();

	return EXIT_SUCCESS;
}
