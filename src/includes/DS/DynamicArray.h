#pragma once

#include <iostream>
#include <algorithm>

#define MIN_SIZE 2

template <typename T>
class DynamicArray
{
private:
	std::size_t m_Size;
	T* m_Array;

public:
	DynamicArray(const std::size_t size);
	DynamicArray(const DynamicArray& other);
	DynamicArray(std::initializer_list<T> elements);

	DynamicArray& operator=(DynamicArray other);

	~DynamicArray();

	T& operator[](size_t index);

	friend void swap(DynamicArray& first, DynamicArray& second);
};

template<typename T>
DynamicArray<T>::DynamicArray(const std::size_t size)
	:m_Size(size ? size : MIN_SIZE),
	m_Array(new T[m_Size])
{}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
	: m_Size(other.m_Size),
	m_Array(new T[m_Size])
{
	std::copy(other.m_Array, other.m_Array + m_Size, this->m_Array);
}
 
template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> elements) :
	m_Size(elements.size()),
	m_Array(m_Size ? new T[m_Size] : nullptr)
{
	std::copy(elements.begin(), elements.end(), m_Array);
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] m_Array;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> other)
{
	swap(*this, other);
	return *this;
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index)
{
	if (index >= m_Size)
		throw std::out_of_range("Index out of bound!");
	return m_Array[index];
}

template<typename T>
void swap(DynamicArray<T>& first, DynamicArray<T>& second)
{
	using std::swap;
	swap(first.m_Size, second.m_Size);
	swap(first.m_Array, second.m_Array);
}
