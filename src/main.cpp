#include "models.hpp"
#include "renderer.hpp"

int main()
{
	const uint32_t WIDTH{ 1280 };
	const uint32_t HEIGHT{ 720 };
	const std::string TITLE{ "3D Renderer" };

	sf::RenderWindow window{ sf::VideoMode{ WIDTH, HEIGHT }, TITLE, sf::Style::Close };
	Renderer renderer{ window };
	sf::Clock clock{};

	float rotation_speed = 1.5f;
	Entity y_rotating_cube{ models::Cube, { RotationDirection::Y, rotation_speed }, { 0.0f, 0.0f, 0.0f } };
	Entity x_rotating_cube{ models::Cube, { RotationDirection::X, rotation_speed }, { 2.0f, 0.0f, 0.0f } };
	Entity static_pyramid{ models::Pyramid, { RotationDirection::NONE, rotation_speed }, { -2.0f, 0.0f, 0.0f } };

	while (window.isOpen())
	{
		window.clear();
		sf::Event event{};
		sf::Time dt = clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		renderer.render(static_pyramid, dt.asSeconds());
		renderer.render(x_rotating_cube, dt.asSeconds());
		renderer.render(y_rotating_cube, dt.asSeconds());
		
		window.display();
	}
	
	return EXIT_SUCCESS;
}
