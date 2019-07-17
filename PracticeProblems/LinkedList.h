#pragma once

#include <ostream>
#include <string>

template<typename T> class LinkedList;
template<typename T> class LinkedList_iter;

template <typename T>
class LinkedListNode {

	friend class LinkedList<T>;
	friend class LinkedList_iter<T>;
	private:
		LinkedListNode() : next(nullptr) {};
		LinkedListNode(const T &_content) : m_value(_content), next(nullptr) {};
		LinkedListNode(const T &_content, LinkedListNode<T> *next) : m_value(_content), next(next) {};
		~LinkedListNode() { delete next; }
	public:
		LinkedListNode<T> *next;
		T m_value;
};

template<typename T>
class LinkedList {
private:
	LinkedListNode<T> *m_head, *m_tail, *m_cursor; //a reusable cursor
	size_t m_length;
public:
	LinkedList<T>() : m_head(nullptr), m_tail(nullptr), m_length(0) {};
	~LinkedList<T>() { delete m_head; }
	LinkedList<T>(const T &_value);
	void clear();
	void push_front(const T &_value);
	void pop_front();
	void push_back(const T &_value);
	bool empty() { return head == nullptr; }
	size_t length();
	friend std::ostream & operator<<(std::ostream &out, const LinkedList<T>& list)
	{
		LinkedListNode<T> *cursor = list.m_head;
		while (cursor != nullptr) {
			out << cursor->m_value << " ";
			cursor = cursor->next;
		}
		return out;
	}
};

template<typename T>
LinkedList<T>::LinkedList(const T &_value) {
	m_head = new LinkedListNode<T>(_value);
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
	LinkedListNode<T> *newNode = new LinkedListNode<T>(_value, m_head);
	m_head = newNode;
	m_length++;
	if (m_tail == nullptr) {
		m_tail = newNode;
	}
	return;
}

template<typename T>
void LinkedList<T>::pop_front() {
	if (m_length == nullptr) return;
	m_cursor = m_head;
	m_head = m_head->next;
	delete m_cursor;
	m_length--;
	return;
}

template<typename T>
void LinkedList<T>::push_back(const T &_value) {
	LinkedListNode<T> *newNode = new LinkedListNode<T>(_value, nullptr);
	if (m_head == nullptr) {
		m_head = newNode;
	} else {
		m_tail->next = newNode;
	}
	m_tail = newNode;
	m_length++;
}

template<typename T>
size_t LinkedList<T>::length() {
	return m_length;
}