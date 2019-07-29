#pragma once

#include <ostream>
#include <string>

template<typename T> class LinkedList;
template<typename T> class LinkedListIter;

template <typename T>
class LinkedListNode {

	friend class LinkedList<T>;
	friend class LinkedListIter<T>;
	private:
		LinkedListNode() : next(nullptr) {};
		LinkedListNode(const T &_content) : m_value(_content), next(nullptr) {};
		LinkedListNode(const T &_content, LinkedListNode<T> *next) : m_value(_content), next(next) {};
		//~LinkedListNode() { delete next; }
	public:


		LinkedListNode<T> *next;
		T m_value;
};

template<typename T> //for our purposes, T is the LinkedListNode
class LinkedListIterator : public std::iterator<std::forward_iterator_tag,
	LinkedListNode<T>>
{
public:
	LinkedListIterator<T>(LinkedListNode<T> *ptr = nullptr) { m_ptr = ptr; }
	LinkedListIterator<T>(const LinkedListIterator<T> &ptr) { this->m_ptr = ptr.getPtr(); }
	~LinkedListIterator<T>() {
		m_cursor = m_head;
		while (m_cursor != nullptr) {
			LinkedListNode<T> *next = m_cursor->next;
			delete m_cursor;
			m_cursor = next;
		}
	}

	LinkedListIterator<T>& operator=(const LinkedListIterator<T>& iter) = default;
	LinkedListIterator<T>& operator=(LinkedListNode<T>* ptr) { m_ptr = ptr; return(*this); }

	operator bool()const
	{
		if (m_ptr) return true;
		else	   return false;
	}

	bool operator==(const LinkedListIterator<T>& iter) const { return (m_ptr == iter.getConstPtr()); }
	bool operator!=(const LinkedListIterator<T>& iter) const { return (m_ptr != iter.getConstPtr()); }

	LinkedListIterator<T>&  operator++() { m_ptr = m_ptr->next; return (*this); }

	T&						operator*() { return m_ptr->m_value; }
	const T&				operator*()const { return *m_ptr->m_value; }
	T*						operator->() { return m_ptr->m_value; }

	LinkedListNode<T>*						getPtr()const { return m_ptr; }
	const LinkedListNode<T>*				getConstPtr()const { return m_ptr; }
protected:
	LinkedListNode<T>* m_ptr;
};

template<typename T>
class LinkedList {
private:
	LinkedListNode<T> *m_head, *m_tail, *m_cursor; //a reusable cursor
	size_t m_length;
public:
	typedef LinkedListIterator<T>	iterator;
	typedef LinkedListIterator<const T> const_iterator;

	LinkedList<T>() : m_head(nullptr), m_tail(nullptr), m_length(0) {};
	//LinkedList<T>(std::vector<T> v);
	~LinkedList<T>() { delete m_head; }
	LinkedList<T>(const T &_value);
	LinkedList<T>(const LinkedList<T>& rhs);

	bool empty() const { return m_head == nullptr; }
	size_t length() const {	return m_length; }

	//Iterators
	iterator begin() { return iterator(m_head); }
	iterator end() { return iterator(m_tail->next); }
	const_iterator cbegin() { return const_iterator(m_head); }
	const_iterator cend() { return const_iterator(m_tail); }

	void clear();
	void push_front(const T &_value);
	void pop_front();
	void push_back(const T &_value);
	bool insert_after(const T &_beforeValue, const T &_insertValue);
	bool insert_before(const T &_nextValue, const T &_insertValue);
	bool erase(const T &_deleteValue);
	bool erase_after(const T &_beforeValue);
	void reverse();
	void resize(size_t count);
	//void resize(size_t count, const T &value);
	friend std::ostream & operator<<(std::ostream &out, const LinkedList<T>& list)
	{
		LinkedListNode<T> *cursor = list.m_head;
		while (cursor != nullptr) {
			out << cursor->m_value << " ";
			cursor = cursor->next;
		}
		return out;
	}
	LinkedList<T>& operator+(const LinkedList<T>& rhs);
	LinkedList<T>& operator+=(const LinkedList<T>& rhs);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	bool operator==(const LinkedList<T>& rhs) { return rhs.m_head == this->m_head; }
};

template<typename T>
LinkedList<T>::LinkedList(const T &_value) {
	m_head = new LinkedListNode<T>(_value);
	m_tail = m_head;
	m_length = 1;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) {
	LinkedListNode<T> *newNode = new LinkedListNode<T>(rhs->m_head->m_value);
	m_head = newNode;
	m_tail = newNode;
	m_length = 1;
	m_cursor = m_head;
	LinkedListNode<T> *copyCursor = rhs.m_head->next;
	while (copyCursor != nullptr) {
		LinkedListNode<T> *nextNode = new LinkedListNode<T>(copyCursor->m_value);
		m_cursor->next = nextNode;
		m_tail = newNode;
		m_cursor = m_cursor->next;
		copyCursor = copyCursor->next;
		m_length++;
	}
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
	m_cursor->next = nullptr;
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
			if (m_cursor == m_tail) {
				push_back(_insertValue);
				return true;
			}
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
void LinkedList<T>::reverse() {
	if (empty() || m_head == m_tail) return;
	m_cursor = m_head->next;
	LinkedListNode<T> *pre_cursor, *post_cursor;
	pre_cursor = m_head;
	pre_cursor->next = nullptr;
	post_cursor = m_cursor->next;
	m_head = m_tail;
	m_tail = pre_cursor;
	while (post_cursor != nullptr) {
		m_cursor->next = pre_cursor;
		pre_cursor = m_cursor;
		m_cursor = post_cursor;
		post_cursor = post_cursor->next;
	}
	m_cursor->next = pre_cursor; //one last time
}

template<typename T>
void LinkedList<T>::resize(size_t count) {
	m_length = count;
	if (count == 0) {
		delete m_head;
		m_tail = nullptr;
		return;
	} else if (count == 1) {
		m_head->next = nullptr;
		m_tail = m_head;
		return;
	}
	if (m_head == nullptr) {
		LinkedListNode<T> *newNode = new LinkedListNode<T>();
		m_head = newNode;
		m_tail = newNode;
		count--;
	}
	m_cursor = m_head;
	LinkedListNode<T> *pre_cursor = m_head;
	while (count > 0) {
		pre_cursor = m_cursor;
		m_cursor = m_cursor->next;
		if (m_cursor == nullptr) {
			LinkedListNode<T> *newNode = new LinkedListNode<T>();
			pre_cursor->next = newNode;
			m_cursor = newNode;
		}
		//pre_cursor = m_cursor;
		//m_cursor = m_cursor->next;
		count--;
	}
	std::cout << "value in pre_cursor: " << pre_cursor->m_value << std::endl;
	if (m_cursor != nullptr) {
		std::cout << "Deleting " << m_cursor->m_value << std::endl;
		delete m_cursor;
		m_tail = pre_cursor;
		pre_cursor->next = nullptr;
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+(const LinkedList<T>& rhs) {
	LinkedListNode<T> *temp = rhs.m_head;
	m_cursor = m_tail;
	while (temp != nullptr) {
		LinkedListNode<T> *newNode = new LinkedListNode<T>(temp->m_value);
		this->m_cursor->next = newNode;
		this->m_cursor = this->m_cursor->next;
		temp = temp->next;
	}
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& rhs) {
	LinkedListNode<T> *temp = rhs.m_head;
	m_cursor = m_tail;
	while (temp != nullptr) {
		LinkedListNode<T> *newNode = new LinkedListNode<T>(temp->m_value);
		this->m_cursor->next = newNode;
		this->m_cursor = this->m_cursor->next;
		temp = temp->next;
	}
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	LinkedListNode<T> *temp = rhs.m_head;
	this->m_cursor = this->m_head;
	LinkedListNode<T> *pre_cursor = this->m_head;
	while (this->m_cursor != nullptr) { //insert as many values into the linkedlist as it can currently fit
		this->m_cursor->m_value = temp->m_value;
		if (temp->next == nullptr) { //if we stored all the values before m_cursor reaches nullptr
			this->m_tail = this->m_cursor; //set the tail
			delete this->m_cursor->next; //delete the rest
			temp = temp->next; //to prevent us from re-adding the end value
			return *this; //exit
		}
		temp = temp->next;
		if (pre_cursor != this->m_cursor) pre_cursor = pre_cursor->next;
		this->m_cursor = this->m_cursor->next;
	}
	while (temp != nullptr) { //if there are still elements in rhs that need adding
		LinkedListNode<T> *newNode = new LinkedListNode<T>(temp->m_value);
		pre_cursor->next = newNode;
		this->m_tail = newNode;
		pre_cursor = pre_cursor->next;
		temp = temp->next;
	}
	return *this;
}