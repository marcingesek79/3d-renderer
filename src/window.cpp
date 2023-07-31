#include "window.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string& title, Renderer& renderer) noexcept
	: width{ width }, height{ height }, title{ title }, 
	window { sf::VideoMode{width, height}, title },
	renderer { renderer }
{
}

void Window::handleEvents() noexcept
{
	sf::Event event{};

	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window.close();
	}
}

void Window::run() noexcept
{
	this->renderer.print();

	while (this->window.isOpen())
	{
		handleEvents();
		this->window.clear();
		this->window.display();
	}
}
