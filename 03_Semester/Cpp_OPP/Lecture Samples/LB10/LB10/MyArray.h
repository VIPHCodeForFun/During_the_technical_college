#pragma once
#include <array>
template <class T, int N>
class MyArray {
public:
	const std::array<T, N> arr;
	MyArray(T a, T b, T c) : arr{ std::array<T, N>{a, b, c} } {};
};

