#pragma once
#include "types.hpp"

namespace calc
{
	constexpr auto PI = 3.14159265f;
	constexpr auto FOV = 90.0f;
	constexpr auto Z_NEAR = 0.1f;
	constexpr auto Z_FAR = 1000.0f;

	[[nodiscard]] static auto toRadians(float angle) noexcept -> float
	{
		return angle / 180.0f * PI;
	}

	template <typename size_t SIZE>
	[[nodiscard]] static auto multiplyVectorByMatrix(const std::vector<float>& vec, const Matrix<SIZE>& matrix) -> std::vector<float>
	{
		if (vec.size() != SIZE)
			throw std::invalid_argument("wrong size of vec or matrix");

		std::vector<float> output_vec{};

		for (size_t i{}; i < vec.size(); i++)
		{
			float sum{};
			for (size_t j{ }; j < SIZE; j++)
			{
				sum += vec.at(j) * matrix.get(j, i);
			}
			output_vec.emplace_back(sum);
		}

		if (output_vec.at(3) != 0.0)
		{
			output_vec.at(0) /= output_vec.at(3);
			output_vec.at(1) /= output_vec.at(3);
			output_vec.at(2) /= output_vec.at(3);
		}

		output_vec.pop_back();
		return output_vec;
	}
}