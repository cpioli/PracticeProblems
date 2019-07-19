#pragma once

#include "LinkedList.h"

template<typename T> //for our purposes, T is the LinkedListNode
class LinkedListIterator : public std::iterator<std::forward_iterator_tag,
	T,
	ptrdiff_t, //the signed int type of the result of subtracting two pointers
	T*,
	T&>
{
public:
	LinkedListIterator<T>(T *ptr = nullptr) { m_ptr = ptr; }
	LinkedListIterator<T>(const LinkedListIterator<T> &ptr) { this->m_ptr = ptr.getPtr(); }
	~LinkedListIterator<T>(){}

	LinkedListIterator<T>& operator=(const LinkedListIterator<T>& iter) = default;
	LinkedListIterator<T>& operator=(T* ptr) { m_ptr = ptr; return(*this); }

	operator			   bool()const
	{
		if (m_ptr) return true;
		else	   return false;
	}

	bool operator==(const LinkedListIterator<T>& iter) const { return (m_ptr == iter.GetConstPtr()); }
	bool operator!=(const LinkedListIterator<T>& iter) const { return (m_ptr != iter.GetConstPtr()); }

	LinkedListIterator<T>&	operator+=(const ptrdiff_t& movement) { m_ptr += movement; return (*this); }
	LinkedListIterator<T>&  operator++() { ++m_ptr; return (*this); }
	LinkedListIterator<T>   operator++(ptrdiff_t) { auto temp(*this); ++m_ptr; return temp; }
	LinkedListIterator<T>   operator+(const ptrdiff_t &movement) { auto old_ptr = m_ptr; m_ptr += movement; auto temp(*this); m_ptr = old_ptr; return temp; }

	T&						operator*() { return *m_ptr; }
	const T&				operator*()const { return *m_ptr; }
	T*						operator->() { return m_ptr; }

	T*						getPtr()const { return m_ptr; }
	const T*				getConstPtr()const { return m_ptr; }
protected: 
	T* m_ptr;
};