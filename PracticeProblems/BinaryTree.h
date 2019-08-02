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
	BinaryTreeNode<T>* erase(BinaryTreeNode<T> *root, const T& _value);
	BinaryTreeNode<T>* minValNode(BinaryTreeNode<T> *root) const;
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
	void erase(const T& _value);
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
BinaryTreeNode<T>* BinarySearchTree<T>::erase(BinaryTreeNode<T> *root, const T& _value) {
	if (root == nullptr) return root;
	if (_value < root->m_value) {
		root->left = erase(root->left, _value);
	}
	else if (_value > root->m_value) {
		root->right = erase(root->right, _value);
	}
	else {
		if (root->right == nullptr && root->left == nullptr) {
			delete root;
			return nullptr;
		}
		else if (root->right == nullptr) {
			m_cursor = root->left;
			delete root;
			return m_cursor;
		}
		else if (root->left == nullptr) {
			m_cursor = root->right;
			delete root;
			return m_cursor;
		}
		else {
			m_cursor = minValNode(root->right);
			root->m_value = m_cursor->m_value;
			root->right = erase(root->right, m_cursor->m_value);
		}
	}

	return root;
}

template<typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::minValNode(BinaryTreeNode<T> *root) const {
	if (root->left != nullptr) return minValNode(root->left);
	else return root;
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
	postorderPrintTraversal(root->left);
	postorderPrintTraversal(root->right);
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

template<typename T>
void BinarySearchTree<T>::erase(const T& _value) {
	erase(m_root, _value);
}

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