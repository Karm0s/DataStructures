#pragma once

#include <iostream>
#include <algorithm>

#define MIN_SIZE 2
#define SHRINK_RATIO 2.5

template <typename T>
class DynamicArray
{
public:
	class Iterator
	{
	public:
		using interator_category = std::forward_iterator_tag;
		using difference_type    = std::ptrdiff_t;
		using value_type         = T;
		using pointer            = Iterator::value_type*;
		using reference          = Iterator::value_type&;

		Iterator(pointer ptr);

		reference operator*();
		pointer operator->();

		Iterator& operator++();
		Iterator operator++(int);

		friend bool operator==(const DynamicArray<T>::Iterator& first, const DynamicArray<T>::Iterator& second)
		{
			return (first.m_Pointer == second.m_Pointer);
		}
		friend bool operator!=(const DynamicArray<T>::Iterator& first, const DynamicArray<T>::Iterator& second)
		{
			return (first.m_Pointer != second.m_Pointer);
		}
	
	private:
		pointer m_Pointer;
	};
	DynamicArray();
	DynamicArray(const std::size_t size);
	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other) noexcept;
	DynamicArray(std::initializer_list<T> elements);

	DynamicArray& operator=(DynamicArray other);

	~DynamicArray();

	T& front();
	T& back();
	const T& front() const;
	const T& back() const;

	Iterator begin();
	Iterator end();

	void push_back(const T& element);
	void push_back(T&& element);
	void push_back(const std::initializer_list<T>& elements);
	void push_back(std::initializer_list<T>&& elements);

	void pop_back();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T& at(size_t index);
	const T& at(size_t index) const;

	friend void swap(DynamicArray& first, DynamicArray& second);

private:

	std::size_t m_Size;
	std::size_t m_UsedCapacity;

	T* m_Array;
	
	void reallocate(size_t newSize);
	inline void validateIndex(size_t index) const;
};


template<typename T>
DynamicArray<T>::Iterator::Iterator(pointer ptr)
	:m_Pointer(ptr)
{}

template<typename T>
DynamicArray<T>::Iterator::reference DynamicArray<T>::Iterator::operator*()
{
	return *m_Pointer;
}

template<typename T>
DynamicArray<T>::Iterator::pointer DynamicArray<T>::Iterator::operator->()
{
	return m_Pointer;
}

template<typename T>
typename DynamicArray<T>::Iterator& DynamicArray<T>::Iterator::operator++()
{
	m_Pointer++;
	return *this;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator++(int)
{
	Iterator copy = *this;
	++(*this);
	return copy;
}

template<typename T>
inline void DynamicArray<T>::reallocate(size_t newSize)
{
	T* tempArray = new T[newSize];
	
	std::copy(m_Array, m_Array + std::min(newSize, m_Size), tempArray);

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
	m_Size(elements.size() ? elements.size() : MIN_SIZE),
	m_UsedCapacity(m_Size),
	m_Array(new T[m_Size])
{
	std::copy(elements.begin(), elements.end(), m_Array);
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] m_Array;
}

template<typename T>
T& DynamicArray<T>::front()
{
	return m_Array[0];
}

template<typename T>
T& DynamicArray<T>::back()
{
	return m_Array[m_UsedCapacity - 1];
}

template<typename T>
const T& DynamicArray<T>::front() const
{
	return m_Array[0];
}

template<typename T>
const T& DynamicArray<T>::back() const
{
	return m_Array[m_Size - 1];
}

template<typename T>
DynamicArray<T>::Iterator DynamicArray<T>::begin()
{
	return DynamicArray<T>::Iterator(m_Array);
}

template<typename T>
DynamicArray<T>::Iterator DynamicArray<T>::end()
{
	return DynamicArray<T>::Iterator(m_Array + m_UsedCapacity);
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
		reallocate(m_Size * 2);

	m_Array[m_UsedCapacity] = std::move(element);
	m_UsedCapacity++;
}

template<typename T>
void DynamicArray<T>::push_back(const std::initializer_list<T>& elements)
{
	for (auto e : elements)
	{
		if (m_UsedCapacity >= m_Size)
			reallocate(m_Size * 2);

		m_Array[m_UsedCapacity] = e;
		m_UsedCapacity++;
	}
}

template<typename T>
void DynamicArray<T>::push_back(std::initializer_list<T>&& elements)
{
	for (auto e : elements)
	{
		if (m_UsedCapacity >= m_Size)
			reallocate(m_Size * 2);

		m_Array[m_UsedCapacity] = std::move(e);
		m_UsedCapacity++;
	}
}

template<typename T>
void DynamicArray<T>::pop_back()
{
	m_UsedCapacity--;
	float ratio = m_Size / m_UsedCapacity;
	if (ratio > SHRINK_RATIO)
		reallocate(m_Size / 2);
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
const T& DynamicArray<T>::operator[](size_t index) const
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

//template<typename T>
//bool operator==(const typename DynamicArray<T>::Iterator& first, const typename DynamicArray<T>::Iterator& second)
//{
//	return first.m_Pointer == second.m_Pointer;
//}
//
//template<typename T>
//bool operator!=(const typename DynamicArray<T>::Iterator& first, const typename DynamicArray<T>::Iterator& second)
//{
//	return !(first.m_Pointer == second.m_Pointer);
//}

template<typename T>
void swap(DynamicArray<T>& first, DynamicArray<T>& second)
{
	using std::swap;
	swap(first.m_Size, second.m_Size);
	swap(first.m_Array, second.m_Array);
}


/*
To Do:
Iterator
Front and back methods
*/
