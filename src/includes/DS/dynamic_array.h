#pragma once

#include <iostream>
#include <algorithm>

#include "iterators.h"

#define MIN_SIZE 2
#define SHRINK_RATIO 2.5

namespace DS{

	template <typename T>
	class DynamicArray
	{
	public:
		using value_type		=	T;
		using size_type			=	std::size_t;
		using pointer			=	DynamicArray::value_type*;
		using reference			=	DynamicArray::value_type&;
		using iterator			=	DS::RandomAccessIterator<T>;
		using const_pointer		=	const pointer;
		using const_reference	=	const reference;
		using const_iterator	=	const iterator;


		DynamicArray(): 
			m_Size(MIN_SIZE), 
			m_UsedCapacity(0), 
			m_Array(new value_type[m_Size]) {}

		DynamicArray(const size_type size)
			:m_Size(size ? size : MIN_SIZE), 
			m_UsedCapacity(0), 
			m_Array(new value_type[m_Size]) {}

		DynamicArray(const DynamicArray& other)
			:m_Size(other.m_Size), 
			m_UsedCapacity(other.m_UsedCapacity), 
			m_Array(new value_type[m_Size])
		{
			std::copy(other.m_Array, other.m_Array + m_Size, this->m_Array);
		}

		DynamicArray(DynamicArray&& other) noexcept
			:m_Size(other.m_Size),
			m_UsedCapacity(other.m_UsedCapacity),
			m_Array(other.m_Array)
		{
			other.m_Array = nullptr;
		}

		DynamicArray(std::initializer_list<value_type> elements)
		:m_Size(elements.size() ? elements.size() : MIN_SIZE),
		m_UsedCapacity(m_Size),
		m_Array(new value_type[m_Size])
		{
			std::copy(elements.begin(), elements.end(), m_Array);
		}

		DynamicArray& operator=(DynamicArray other)
		{
			swap(*this, other);
			return *this;
		}

		~DynamicArray()
		{
			delete[] m_Array;
		}


		reference front()					{return m_Array[0];}
		const_reference front() const		{return m_Array[0];}
		reference back()					{return m_Array[m_UsedCapacity - 1];}
		const_reference back() const		{return m_Array[m_UsedCapacity - 1];}
		iterator begin()					{return iterator(m_Array);}
		const_iterator begin() const		{return iterator(m_Array);}
		iterator end()						{return iterator(m_Array + m_UsedCapacity);}
		const_iterator end() const			{return iterator(m_Array + m_UsedCapacity);}


		void push_back(const_reference element)
		{
			if (m_UsedCapacity >= m_Size)
				reallocate(m_Size * 2);

			m_Array[m_UsedCapacity] = element;
			m_UsedCapacity++;
		}

		void push_back(value_type&& element)
		{
			if (m_UsedCapacity >= m_Size)
				reallocate(m_Size * 2);

			m_Array[m_UsedCapacity] = std::move(element);
			m_UsedCapacity++;
		}

		void push_back(const std::initializer_list<value_type>& elements)
		{
			for (auto e : elements)
			{
				if (m_UsedCapacity >= m_Size)
					reallocate(m_Size * 2);

				m_Array[m_UsedCapacity] = e;
				m_UsedCapacity++;
			}
		}

		void push_back(std::initializer_list<value_type>&& elements)
		{
			for (auto e : elements)
			{
				if (m_UsedCapacity >= m_Size)
					reallocate(m_Size * 2);

				m_Array[m_UsedCapacity] = std::move(e);
				m_UsedCapacity++;
			}
		}

		void pop_back()
		{
			m_UsedCapacity--;
			float ratio = m_Size / m_UsedCapacity;
			if (ratio > SHRINK_RATIO)
				reallocate(m_Size / 2);
		}

		reference operator[](size_type index)					{return m_Array[index];}
		const_reference operator[](size_type index) const		{return m_Array[index];}

		reference at(size_type index)							{validateIndex(index); return m_Array[index];}
		const_reference at(size_type index) const				{validateIndex(index); return m_Array[index];}

		friend void swap(DynamicArray& first, DynamicArray& second)
		{
			using std::swap;
			swap(first.m_Size, second.m_Size);
			swap(first.m_Array, second.m_Array);
		}

	private:

		size_type m_Size;
		size_type m_UsedCapacity;

		pointer m_Array;
		
		void reallocate(size_type newSize)
		{
			value_type* tempArray = new value_type[newSize];
			
			std::copy(m_Array, m_Array + std::min(newSize, m_Size), tempArray);

			std::swap(tempArray, m_Array);
			m_Size = newSize;

			delete[] tempArray;
		}

		inline void validateIndex(size_type index) const
		{
			if (index > m_Size)
				throw std::out_of_range("index out of bound.");
		}
	};

}
