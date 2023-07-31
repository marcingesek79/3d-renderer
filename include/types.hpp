#pragma once
#include <iostream>
#include <SFML/System/Vector3.hpp>

struct Triangle
{
	sf::Vector3f a, b, c;

	Triangle(sf::Vector3f a, sf::Vector3f b, sf::Vector3f c) noexcept
		: a{ a }, b{ b }, c{ c }
	{
	}
};

inline std::ostream& operator<<(std::ostream& os, const sf::Vector3f& obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Triangle& obj)
{
	os << "[" << obj.a << ", " << obj.b << ", " << obj.c << "]";
	return os;
}
