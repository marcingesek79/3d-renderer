#pragma once
#include <iostream>
#include <SFML/System/Vector3.hpp>
#include <array>
#include <vector>

enum class RotationDirection
{
	NONE = 0,
	X,
	Y
};

struct Rotation
{
	RotationDirection dir;
	float speed;
};

struct Camera
{
	float x, y, z;
};

struct Triangle
{
	sf::Vector3f a, b, c;

	Triangle(sf::Vector3f a, sf::Vector3f b, sf::Vector3f c) noexcept
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

struct Entity
{
	std::vector<Triangle> model;
	Rotation rotation;
	sf::Vector3f position;

	Entity(std::vector<Triangle> model, Rotation rotation, sf::Vector3f position) noexcept
		: model{model}, rotation{rotation}, position{position}
	{
	}
};