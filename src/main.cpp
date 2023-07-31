#include "window.hpp"
#include "models.hpp"

int main()
{
	const uint32_t WIDTH{ 1280 };
	const uint32_t HEIGHT{ 720 };
	const std::string TITLE{ "3D Renderer" };

	Renderer renderer{ Models::Cube3D };
	Window window{ WIDTH, HEIGHT, TITLE, renderer };
	window.run();

	return EXIT_SUCCESS;
}
