#pragma once

#include <array>

struct Matrix
{
	template <int T>
	static std::array<char, T*T> hFlip(std::array<char, T*T> matrix, int size)
	{
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size/2 + 1; x++)
			{
				char r = matrix[T * y + size - x - 1];
				matrix[T * y + size - x - 1] = matrix[T * y + x];
				matrix[T * y + x] = r;
			}
		}

		return matrix;
	}

	template <int T>
	static std::array<char, T*T> transpose(std::array<char, T*T> matrix, int size)
	{
		auto copy = matrix;
		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
				copy[T * y + x] = matrix[T * x + y];
		return copy;
	}

	template <int T>
	static std::array<char, T*T> rotate(std::array<char, T*T> matrix, int size, bool clockwise)
	{
		for (int i = 0; i < 3; i++)
		{
			matrix = hFlip<T>(transpose<T>(matrix, size), size);
			if (clockwise) break;
		}
		return matrix;
	}
};

