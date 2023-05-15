#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class DynamicArray
{
private:
	std::size_t m_Size;
	T* m_Array;

public:
	DynamicArray(const std::size_t size = 10):
		m_Size(size),
		m_Array(m_Size? new T[m_Size] : nullptr)
	{}

	DynamicArray(const DynamicArray& other):
		m_Size(other.m_Size),
		m_Array(m_Size? new T[m_Size] : nullptr)
	{
		std::copy(other.m_Array, other.m_Array + m_Size, this->m_Array);
	}

	DynamicArray(std::initializer_list<T> elements) :
		m_Size(elements.size()),
		m_Array(m_Size ? new T[m_Size] : nullptr)
	{
		std::copy(elements.begin(), elements.end(), m_Array);
	}

	DynamicArray& operator=(DynamicArray other)
	{
		swap(*this, other);
		return *this;
	}

	T& operator[](size_t index)
	{
		if (index >= m_Size)
			throw std::out_of_range("Index out of bound!");
		return m_Array[index];
	}

	friend void swap(DynamicArray& first, DynamicArray& second)
	{
		using std::swap;
		swap(first.m_Size, second.m_Size);
		swap(first.m_Array, second.m_Array);
	}

	~DynamicArray()
	{
		delete[] m_Array;
	}
};
