#pragma once

#include <iostream>
#include <algorithm>

#define MIN_SIZE 2

template <typename T>
class DynamicArray
{
private:
	T* m_Array;

	std::size_t m_Size; // Used for allocation
	std::size_t m_UsedCapacity; // track used amount
	
	void reallocate(); 
	inline void validateIndex(size_t index) const;

public:
	DynamicArray();
	DynamicArray(const std::size_t size);
	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other) noexcept;
	DynamicArray(std::initializer_list<T> elements);

	DynamicArray& operator=(DynamicArray other);

	~DynamicArray();

	void push_back(const T& element);
	void push_back(T&& element);

	T& operator[](size_t index);

	T& at(size_t index);
	const T& at(size_t index) const;

	friend void swap(DynamicArray& first, DynamicArray& second);
};

template<typename T>
void DynamicArray<T>::reallocate()
{
	std::size_t newSize = m_Size * 2;
	T* tempArray = new T[newSize];
	
	std::copy(m_Array, m_Array + m_Size, tempArray);

	std::swap(tempArray, m_Array);
	m_Size = newSize;

	delete[] tempArray;
}

template<typename T>
inline void DynamicArray<T>::validateIndex(size_t index) const
{
	if (index > m_Size)
		throw std::out_of_range("index out of bound.");
}

template<typename T>
DynamicArray<T>::DynamicArray()
	:m_Size(MIN_SIZE),
	m_UsedCapacity(0),
	m_Array(new T[m_Size])
{}

template<typename T>
DynamicArray<T>::DynamicArray(const std::size_t size)
	:m_Size(size ? size : MIN_SIZE),
	m_UsedCapacity(0),
	m_Array(new T[m_Size])
{}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
	: m_Size(other.m_Size),
	m_UsedCapacity(other.m_UsedCapacity),
	m_Array(new T[m_Size])
{
	std::copy(other.m_Array, other.m_Array + m_Size, this->m_Array);
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
	:m_Size(other.m_Size),
	m_UsedCapacity(other.m_UsedCapacity),
	m_Array(other.m_Array)
{
	other.m_Array = nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> elements) :
	m_Size(elements.size()),
	m_UsedCapacity(m_Size),
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
void DynamicArray<T>::push_back(const T& element)
{
	if (m_UsedCapacity >= m_Size)
		reallocate();

	m_Array[m_UsedCapacity] = element;
	m_UsedCapacity++;
}

template<typename T>
void DynamicArray<T>::push_back(T&& element)
{
	if (m_UsedCapacity >= m_Size)
		reallocate();

	m_Array[m_UsedCapacity] = std::move(element);
	m_UsedCapacity++;
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
	return m_Array[index];
}

template<typename T>
T& DynamicArray<T>::at(size_t index)
{
	validateIndex(index);
	return m_Array[index];
}

template<typename T>
const T& DynamicArray<T>::at(size_t index) const
{
	validateIndex(index);
	return m_Array[index];
}

template<typename T>
void swap(DynamicArray<T>& first, DynamicArray<T>& second)
{
	using std::swap;
	swap(first.m_Size, second.m_Size);
	swap(first.m_Array, second.m_Array);
}
