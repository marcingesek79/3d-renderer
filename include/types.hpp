#pragma once
#include <iostream>

struct Point3D
{
	double x, y, z;
	constexpr Point3D(double x, double y, double z) noexcept
		: x{ x }, y{ y }, z{ z }
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Point3D& obj);
};

inline std::ostream& operator<<(std::ostream& os, const Point3D& obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return os;
}

struct Triangle
{
	Point3D a, b, c;
	constexpr Triangle(Point3D a, Point3D b, Point3D c) noexcept
		: a{ a }, b{ b }, c{ c }
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
};

inline std::ostream& operator<<(std::ostream& os, const Triangle& obj)
{
	os << "[" << obj.a << ", " << obj.b << ", " << obj.c << "]";
	return os;
}
