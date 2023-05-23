#pragma once

#include <iterator>

namespace DS
{

	template <typename T>
	class RandomAccessIterator 
	{
	public:
		using interator_category	=	std::random_access_iterator_tag;
		using value_type			=	T;
		using pointer				=	RandomAccessIterator::value_type*;
		using reference				=	RandomAccessIterator::value_type&;
		using const_pointer			=	const pointer;
		using const_reference		=	const reference;
		using difference_type		=	std::ptrdiff_t;

		RandomAccessIterator(pointer ptr) :m_Pointer(ptr) {}

		reference operator*() { return *m_Pointer; }
		pointer operator->() { return m_Pointer; }
		const_reference operator*() const { return *m_Pointer; }
		const_pointer operator->() const { return m_Pointer; }

		RandomAccessIterator& operator++() { m_Pointer++; return *this; }
		RandomAccessIterator operator++(int) { RandomAccessIterator copy = *this; ++(*this); return copy; }

		bool operator==(const RandomAccessIterator& other) const { return (m_Pointer == other.m_Pointer); }
		bool operator!=(const RandomAccessIterator& other) const { return (m_Pointer != other.m_Pointer); }

	private:
		pointer m_Pointer;
	};

}
