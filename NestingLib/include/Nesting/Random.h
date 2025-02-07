#pragma once

#include <random>

namespace Random
{
	template<typename T>
	T Create(const T& min, const T& max)
	{
		static std::random_device random_device;

		std::mt19937 gen(random_device());
		std::uniform_int_distribution<T> uniform_dist(min, max);

		return uniform_dist(gen);
	}

	template<>
	inline double Create(const double& min, const double& max)
	{
		 static std::random_device random_device;

		 std::mt19937 gen(random_device());
		 std::uniform_real_distribution<double> uniform_dist(min, max);
		 
		 return uniform_dist(gen);
	}
}