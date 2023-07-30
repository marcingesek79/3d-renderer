#include "../include/window.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string& title) noexcept
	: width{ width }, height{ height }, title{ title }, window { sf::VideoMode{width, height}, title }
{
}

void Window::run() noexcept
{
	while (this->window.isOpen())
	{
		sf::Event event{};
		while (this->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window.close();
		}

		this->window.clear();
		this->window.display();
	}
}
