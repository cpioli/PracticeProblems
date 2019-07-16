#pragma once

#include <ostream>
#include <string>

template <typename T>
struct Node {
	Node *next;
	T m_Content;
	Node() : next(nullptr) {};
	Node(const T &_content) {
		next = nullptr;
		m_Content = _content;
	}
};

template<typename T>
class LinkedList {
private:
	Node<T> *m_head;
	Node<T> *m_tail;
	Node<T> *m_cursor; //a reusable cursor
	size_t m_length;
public:
	LinkedList<T>();
	LinkedList<T>(const T &_value);
	void clear();
	void push_front(const T &_value);
	void pop_front();
	void push_back(const T &_value);
	size_t length();
	friend std::ostream & operator<<(std::ostream &out, const LinkedList<T>& list)
	{
		Node<T> *cursor = list.m_head;
		while (cursor != nullptr) {
			out << cursor->m_Content << " ";
			cursor = cursor->next;
		}
		return out;
	}
};

template<typename T>
LinkedList<T>::LinkedList() {
	m_head = nullptr;
	m_tail = m_head;
	m_length = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const T &_value) {
	m_head = new Node<T>(_value);
	m_tail = m_head;
	m_length = 1;
}

template<typename T>
void LinkedList<T>::clear() {
	while (m_length > 0) {
		m_cursor = m_head;
		m_head = m_head->next;
		delete m_cursor;
		m_length--;
	}
}

template<typename T>
void LinkedList<T>::push_front(const T &_value) {
	if (m_length == 0) {
		m_head = new Node<T>(_value);
		m_tail = m_head;
		m_length++;
		return;
	}
	m_cursor = m_head;
	m_head = new Node<T>(_value);
	m_head->next = m_cursor;
	m_length++;
	return;
}

template<typename T>
void LinkedList<T>::pop_front() {
	if (m_length == 0) return;
	m_cursor = m_head;
	m_head = m_head->next;
	delete m_cursor;
	m_length--;
	return;
}

template<typename T>
void LinkedList<T>::push_back(const T &_value) {
	if (m_length == 0) {
		m_head = new Node<T>(_value);
		m_tail = m_head;
		m_length++;
		return;
	}
	m_tail->next = new Node<T>(_value);
	m_tail = m_tail->next;
	m_length++;
}

template<typename T>
size_t LinkedList<T>::length() {
	return m_length;
}