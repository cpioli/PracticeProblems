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
	bool insert_after(const T &_beforeValue, const T &_insertValue);
	bool insert_before(const T &_nextValue, const T &_insertValue);
	bool erase(const T &_deleteValue);
	bool erase_after(const T &_beforeValue);
	bool empty() { return m_head == nullptr; }
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
	delete m_head; //should propogate with the destructor
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
	if (empty()) return;
	m_cursor = m_head;
	m_head = m_head->next;
	delete m_cursor;
	m_length--;
	return;
}

template<typename T>
void LinkedList<T>::push_back(const T &_value) {
	LinkedListNode<T> *newNode = new LinkedListNode<T>(_value, nullptr);
	if (empty()) {
		m_head = newNode;
	} else {
		m_tail->next = newNode;
	}
	m_tail = newNode;
	m_length++;
}

template<typename T>
bool LinkedList<T>::insert_after(const T &_beforeValue, const T &_insertValue) {
	if (empty()) return false;
	m_cursor = m_head;
	while (m_cursor != nullptr) {
		if (m_cursor->m_value == _beforeValue) {
			LinkedListNode<T> *newNode = new LinkedListNode<T>(_insertValue, m_cursor->next);
			m_cursor->next = newNode;
			m_length++;
			return true;
		}
		m_cursor = m_cursor->next;
	}
	return false;
}

template<typename T>
bool LinkedList<T>::insert_before(const T &_nextValue, const T &_insertValue) {
	if (empty()) return false;
	m_cursor = m_head;
	if (m_cursor->m_value == _nextValue) { //if _insertValue needs to go into head
		push_front(_insertValue);
		return true;
	}
	LinkedListNode<T> *pre_cursor = m_cursor;
	m_cursor = m_cursor->next;
	while (m_cursor != nullptr) {
		if (m_cursor->m_value == _nextValue) {
			LinkedListNode<T> *newNode = new LinkedListNode<T>(_insertValue, m_cursor);
			pre_cursor->next = newNode;
			m_length++;
			return true;
		}
		m_cursor = m_cursor->next;
		pre_cursor = pre_cursor->next;
	}
	return false;
}

template<typename T>
bool LinkedList<T>::erase(const T &_deleteValue) {
	if (empty()) return false;
	if (m_head->m_value == _deleteValue) {
		pop_front();
		return true;
	}
	m_cursor = m_head->next;
	LinkedListNode<T> *pre_cursor = m_head;
	while (m_cursor->next != nullptr) {
		if (m_cursor->m_value == _deleteValue) {
			pre_cursor->next = m_cursor->next;
			m_cursor->next = nullptr; //without this the destructor will propogate through the rest of the linked list
			delete m_cursor;
			m_length--;
			return true;
		}
		m_cursor = m_cursor->next;
	}
	return false;
}

template<typename T>
bool LinkedList<T>::erase_after(const T &_beforeValue) {
	if (empty()) return false;
	m_cursor = m_head;
	while (m_cursor != nullptr) {
		if (m_cursor->m_value == _beforeValue) {
			LinkedListNode<T> *temp = m_cursor->next;
			m_cursor->next = temp->next;
			if (m_tail == temp) m_tail = m_cursor;
			else temp->next = nullptr;
			delete temp;
			m_length--;
			return true;
		}
		m_cursor = m_cursor->next;
	}
	return false;
}

template<typename T>
size_t LinkedList<T>::length() {
	return m_length;
}