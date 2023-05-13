#pragma once

#include <iostream>

template <typename T>
class DynamicArray
{
private:
	std::size_t m_Size;
	T* m_Array;

public:
	DynamicArray(const std::size_t size = 10)
	{
		m_Size = size;
		m_Array = new T[m_Size];
	}

	T& operator[](int index)
	{
		if (index >= m_Size)
			throw std::out_of_range("Index out of bound!");
		return m_Array[index];
	}

	~DynamicArray()
	{
		delete[] m_Array;
	}
};
