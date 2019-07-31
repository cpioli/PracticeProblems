#pragma once

template<typename T> class BinarySearchTree;

template<typename T>
class BinaryTreeNode {
	friend class BinarySearchTree<T>;
public:
	BinaryTreeNode<T>() : left(nullptr), right(nullptr) {};
	BinaryTreeNode<T>(const T& _value) : m_value(_value), left(nullptr), right(nullptr) {};
	T m_value;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
};

template<typename T>
class BinarySearchTree {
private:
	BinaryTreeNode<T> *m_root, *m_cursor;

	void insert(const T& _value, BinaryTreeNode<T> *root);
	bool find(const T& _value, BinaryTreeNode<T> *root) const;

	void inorderPrintTraversal(BinaryTreeNode<T> *root) const;
	void postorderPrintTraversal(BinaryTreeNode<T> *root) const;
	void preorderPrintTraversal(BinaryTreeNode<T> *root) const;

public:
	BinarySearchTree<T>(): m_root(nullptr), m_cursor(nullptr) {};
	BinarySearchTree<T>(const T& _value) {
		m_root = new BinaryTreeNode<T>(_value);
		m_cursor = nullptr;
	}
	~BinarySearchTree<T>() {};
	
	void insert(const T& _value);
	bool erase(const T& _value);
	bool find(const T& _value) const;
	void rebalance();

	void inorderPrint();
	void postorderPrint();
	void preorderPrint();
};

//
//	private functions
//

template<typename T>
inline void BinarySearchTree<T>::insert(const T &_value, BinaryTreeNode<T> *root) {
	//assumes root != nullptr
	if (_value <= root->m_value) {
		if (root->left == nullptr) {
			root->left = new BinaryTreeNode<T>(_value);
		}
		else {
			insert(_value, root->left);
		}
	}
	else
	{
		if (root->right == nullptr) {
			root->right = new BinaryTreeNode<T>(_value);
		}
		else {
			insert(_value, root->right);
		}
	}
}

template<typename T>
bool BinarySearchTree<T>::find(const T& _value, BinaryTreeNode<T> *root) const {
	if (root == nullptr) return false;
	else if (root->m_value == _value) return true;
	else if (root->m_value > _value) return find(_value, root->left);
	else if (root->m_value < _value) return find(_value, root->right);
}

template<typename T>
void BinarySearchTree<T>::inorderPrintTraversal(BinaryTreeNode<T> *root) const {
	if (root == nullptr) return;
	inorderPrintTraversal(root->left);
	std::cout << root->m_value << " ";
	inorderPrintTraversal(root->right);
}

template<typename T>
void BinarySearchTree<T>::postorderPrintTraversal(BinaryTreeNode<T> *root) const {
	if (root == nullptr) return;
	inorderPrintTraversal(root->left);
	inorderPrintTraversal(root->right);
	std::cout << root->m_value << " ";
}

template<typename T>
void BinarySearchTree<T>::preorderPrintTraversal(BinaryTreeNode<T> *root) const {
	if (root == nullptr) return;
	std::cout << root->m_value << " ";
	preorderPrintTraversal(root->left);
	preorderPrintTraversal(root->right);
}

//
// public functions
//


template<typename T>
void BinarySearchTree<T>::insert(const T& _value) {
	if (m_root == nullptr) m_root = new BinaryTreeNode<T>(_value);
	else
		insert(_value, m_root);

}

/*
algorithm: if left-or-right side of target node is null, have target pointer 
		   point to the next node
		   if both are full, delete the target and replace it with a leaf from
		   the left side to rebalance the tree
*/
/*template<typename T>
bool BinarySearchTree<T>::erase(const T& _value) {
	if (m_root->m_value == _value) {

	}
	BinaryTreeNode<T> *pre_cursor = m_root;
	if()
	while (!m_cursor) {
		if (_value = m_cursor->m_value) {

		}
	}
}*/

template<typename T>
bool BinarySearchTree<T>::find(const T& _value) const {
	return find(_value, m_root);
}

template<typename T>
void BinarySearchTree<T>::inorderPrint() {
	inorderPrintTraversal(m_root);
	std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::postorderPrint() {
	postorderPrintTraversal(m_root);
	std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::preorderPrint() {
	preorderPrintTraversal(m_root);
	std::cout << std::endl;
}