#pragma once
#include <iostream>
#include <SFML/System/Vector3.hpp>
#include <array>
#include <vector>

struct Triangle
{
	sf::Vector3<float> a, b, c;

	Triangle(sf::Vector3<float> a, sf::Vector3<float> b, sf::Vector3<float> c) noexcept
		: a{ a }, b{ b }, c{ c }
	{
	}
};

template <typename size_t SIZE>
class Matrix
{
	std::array<std::array<float, SIZE>, SIZE> matrix;
public:
	constexpr Matrix() noexcept : matrix{} {}
	[[nodiscard]] auto get(size_t i, size_t j) noexcept -> float& { return matrix[i][j]; }
	[[nodiscard]] auto get(size_t i, size_t j) const noexcept -> float { return matrix[i][j]; }
};

inline std::ostream& operator<<(std::ostream& os, const sf::Vector3<float>& obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Triangle& obj)
{
	os << "[" << obj.a << ", " << obj.b << ", " << obj.c << "]";
	return os;
}

template <typename size_t SIZE>
inline std::ostream& operator<<(std::ostream& os, const Matrix<SIZE>& obj)
{
	for (size_t i{}; i < SIZE; i++)
	{
		for (size_t j{}; j < SIZE; j++)
		{
			os << obj.get(i, j) << " ";
		}
		os << std::endl;
	}
	return os;
}
