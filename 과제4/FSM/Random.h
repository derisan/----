#pragma once

#include <random>

class Random
{
public:
	static void Init()
	{
		std::random_device rd;
		sEngine.seed(rd());
	}

	static float RandFloat(float min = 0.0f, float max = 1.0f)
	{
		std::uniform_real_distribution<float> urd(min, max);
		return urd(sEngine);
	}

	static int RandInt(int min = 0, int max = INT_MAX)
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(sEngine);
	}

private:
	static std::mt19937 sEngine;
};
