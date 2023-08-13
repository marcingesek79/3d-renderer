#include "models.hpp"
#include "renderer.hpp"

int main()
{
	const uint32_t WIDTH{ 1280 };
	const uint32_t HEIGHT{ 720 };
	const std::string TITLE{ "3D Renderer" };

	sf::RenderWindow window{ sf::VideoMode{ WIDTH, HEIGHT }, TITLE };
	Renderer renderer{ window };

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		renderer.render(models::Cube3D);
		window.display();
	}
	
	return EXIT_SUCCESS;
}
