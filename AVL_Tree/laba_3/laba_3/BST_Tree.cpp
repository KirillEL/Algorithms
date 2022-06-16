#include "BST_Tree.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


template<class kt, class vt>
BST_Tree<kt, vt>::Node::Node(kt key, vt value) {
	this->key = key;
	this->value = value;
	this->left = NULL;
	this->right = NULL;
}


template<class kt, class vt>
BST_Tree<kt, vt>::BST_Tree() {
	this->root = nullptr;
	this->size_tree = 0;

}


template<class kt, class vt>
BST_Tree<kt, vt>::BST_Tree(const BST_Tree& tr) {
	this->root = tr->root;
	this->length_tree = tr->length_tree;
	//--
}


template<class kt, class vt>
BST_Tree<kt, vt>::~BST_Tree() {
	this->clear_tree();
	this->size_tree = 0;
}


template<class kt, class vt>
int BST_Tree<kt, vt>::getSize() {
	return this->size_tree;
}




template<class kt, class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::Create_Tree_Node(kt& key, vt& value) {
	Node* node = new Node(key, value);
	return node;

}



template<class kt, class vt>
bool BST_Tree<kt, vt>::is_clear_tree() {
	if (this->getSize() != 0) {
		return false;
	}
	return true;
}




template<class kt, class vt>
bool BST_Tree<kt, vt>::clear_tree() {
	this->delete_node(this->root);
	this->root = nullptr;
	this->size_tree = 0;
	return true;
}

template<class kt, class vt>
void BST_Tree<kt, vt>::delete_node(Node* node) {
	if (node == nullptr) return;
	if (node->left != nullptr) {
		delete_node(node->left);
	}
	if (node->right != nullptr) {
		delete_node(node->right);
	}
	delete node;
}


template<class kt, class vt>
void BST_Tree<kt, vt>::printNode(Node* node) {
	if (node == nullptr) return;
	cout << node->key << "  ";
	printNode(node->left);
	printNode(node->right);
}


template<class kt, class vt>
void BST_Tree<kt, vt>::print(Node* node, int level) {
	if (node == nullptr) return;
	this->print(node->right, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << node->key << "\n";
	this->print(node->left, level + 1);
}

template<class kt, class vt>
void BST_Tree<kt, vt>::printTree() {
	print(this->root);
	cout << "t -> Lt -> Rt" << endl;
	printNode(this->root);

}



// вставка по ключу
template<class kt, class vt>
bool BST_Tree<kt, vt>::insert(kt key, vt& value) {
	if (this->root == nullptr) {
		this->root = new Node(key, value);
		this->size_tree++;
		return true;
	}
	Node* node = this->root;
	Node* pr = nullptr;
	while (node != nullptr) {
		pr = node;
		this->count_nodes++;
		if (key == node->key) {
			return false;
		}
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (key < pr->key) {
		pr->left = new Node(key, value);
		this->size_tree++;
	}
	else {
		pr->right = new Node(key, value);
		this->size_tree++;
	}
	return true;

}

// удаление по ключу
template<class kt, class vt>
bool BST_Tree<kt, vt>::remove(kt key) {
	Node* cur = this->root;
	Node* prev = nullptr;
	while (cur != nullptr && cur->key != key) {
		prev = cur;
		this->count_nodes++;
		if (key < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	if (cur == nullptr) {
		return false;
	}
	this->size_tree--;
	if (cur->left == nullptr || cur->right == nullptr) {
		Node* newCur;
		if (cur->left == nullptr) {
			newCur = cur->right;
		}
		else {
			newCur = cur->left;
		}

		if (prev == nullptr) {
			return newCur;
		}
		if (cur == prev->left) {
			prev->left = newCur;
		}
		else {
			prev->right = newCur;
		}
		delete cur;
	}
	else {
		Node* p = nullptr;
		Node* temp;
		temp = cur->right;
		while (temp->left != nullptr) {
			p = temp;
			temp = temp->left;
		}
		if (p != nullptr) {
			p->left = temp->right;
		}
		else {
			cur->right = temp->right;
		}
		cur->key = temp->key;
		cur->value = temp->value;
		delete temp;
	}
	return true;
}



template<class kt, class vt>
vt& BST_Tree<kt, vt>::getByWriteAndRead(kt key) {
	Node* node = this->root;
	while (node != nullptr && node->key != key) {
		this->count_nodes++;
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (node == nullptr) {
		throw exception("Исключение\n");
	}
	return node->value;
}



template<class kt, class vt>
int BST_Tree<kt, vt>::getCountNodes() {
	return this->count_nodes;
}


// ДОПОЛНИТЕЛЬНАЯ ОПЕРАЦИЯ =============


template<class kt, class vt>
int BST_Tree<kt, vt>::getCountKeysHigherThanInserted(int k) {
	recursiveTraversal(this->root, k);
	return this->counterKey;
}

template<class kt, class vt>
void BST_Tree<kt, vt>::recursiveTraversal(Node* node, int k) {
	if (node == nullptr) return;
	if (k < node->key) this->counterKey++;
	recursiveTraversal(node->left, k);
	recursiveTraversal(node->right, k);
}

template<class kt, class vt>
void BST_Tree<kt, vt>::setCounterKey(int k) {
	this->counterKey = k;
}


template<class kt,class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::search_parent(Node* node, Node* st_node) {
	if (st_node == nullptr) return st_node;

	if (node == root) return nullptr;

	if ((node == st_node->left) || (node == st_node->right)) return st_node;
	if (st_node->key <= node->key) return search_parent(node, st_node->right);
	if (st_node->key > node->key) return search_parent(node, st_node->left);
	return nullptr;
}

template<class kt,class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::searchKey(kt& key, Node* node) {
	if (node == nullptr) return nullptr;
	count_nodes++;
	if (node->key == key) return node;
	if (node->right != nullptr) {
		if (key >= node->key) return searchKey(key, node->right);
	}
	if (node->left != nullptr) {
		if (key < node->key) return searchKey(key, node->left);
	}
	return nullptr;
}


template<class kt, class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::search_end(Node* node) {
	if (node->right != nullptr) return search_end(node->right);
	else return node;
}

// ПРЯМОЙ ИТЕРАТОР ===========




template<class kt, class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::Iterator::nextNode(Node* cur) {
	if (cur == nullptr) return nullptr;
	Node* node = nextNode(cur->left);
	if (node != nullptr) {
		return node;
	}
	if (cur->key > this->cur->key) {
		return cur;
	}
	node = nextNode(cur->right);
	if (node != nullptr) {
		return node;
	}
	return nullptr;
}



template<class kt, class vt>
typename BST_Tree<kt, vt>::Node* BST_Tree<kt, vt>::reverseIterator::nextNode(Node* cur) {
	if (cur == nullptr) return nullptr;
	Node* node = nextNode(cur->right);
	if (node != nullptr) {
		return node;
	}
	if (cur->key < this->cur->key) {
		return cur;
	}
	node = nextNode(cur->left);
	if (node != nullptr) {
		return node;
	}
	return nullptr;

}



template<class kt, class vt>
BST_Tree<kt, vt>::Iterator::Iterator() {
	this->tree = nullptr;
	this->cur = nullptr;
}

template<class kt, class vt>
BST_Tree<kt, vt>::Iterator::Iterator(BST_Tree& tr) {
	this->tree = &tr;
	this->cur = tr.root;
	if (this->cur != nullptr) {
		while (cur->left != nullptr) {
			cur = cur->left;
		}
	}
}


// прямой итератор begin
template<class kt, class vt>
typename BST_Tree<kt, vt>::Iterator BST_Tree<kt, vt>::begin() {
	Iterator b(*this);
	return b;
}

// прямой итератор end
template<class kt, class vt>
typename BST_Tree<kt, vt>::Iterator BST_Tree<kt, vt>::end() {
	Iterator e(*this);
	e.cur = nullptr;
	return e;
}


// operator++ прямой итератор
template<class kt, class vt>
typename BST_Tree<kt, vt>::Iterator& BST_Tree<kt, vt>::Iterator::operator++() {
	if (this->cur != nullptr) {
		this->cur = nextNode(this->tree->root);
		return *this;
	}
	else {
		throw exception("exception\n");
	}
}

// operator == прямой итератор
template<class kt, class vt>
bool BST_Tree<kt, vt>::Iterator::operator==(Iterator& it) {
	return ((this->tree) == (it.tree)) && ((this->cur) == (it.cur));
}

// оператор != прямй итератор
template<class kt, class vt>
bool BST_Tree<kt, vt>::Iterator::operator!=(Iterator& it) {
	return ((this->tree) != (it.tree)) || ((this->cur) != (it.cur));
}


template<class kt, class vt>
vt& BST_Tree<kt, vt>::Iterator::operator*() {
	if (this->cur != nullptr) {
		return this->cur->value;

	}
	else {
		throw exception("exception\n");
	}
}



// ОБРАТНЫЙ ИТЕРАТОР ====================

template<class kt, class vt>
BST_Tree<kt, vt>::reverseIterator::reverseIterator() {
	this->tree = nullptr;
	this->cur = nullptr;
}

template<class kt, class vt>
BST_Tree<kt, vt>::reverseIterator::reverseIterator(BST_Tree& tr) {
	this->tree = &tr;
	this->cur = tr.root;
	if (this->cur != nullptr) {
		while (cur->right != nullptr) {
			this->cur = cur->right;
		}
	}
}

template<class kt, class vt>
vt& BST_Tree<kt, vt>::reverseIterator::operator*() {
	if (this->cur != nullptr) {
		return this->cur->value;
	}
	else {
		throw exception("exception\n");
	}
}




// обратный итератор rbegin()
template<class kt, class vt>
typename BST_Tree<kt, vt>::reverseIterator BST_Tree<kt, vt>::rbegin() {
	reverseIterator rb(*this);
	return rb;
}

// обратный итератор rend()
template<class kt, class vt>
typename BST_Tree<kt, vt>::reverseIterator BST_Tree<kt, vt>::rend() {
	reverseIterator end(*this);
	end.cur = nullptr;
	return end;
}





// operator++ обратный итератор
template<class kt, class vt>
typename BST_Tree<kt, vt>::reverseIterator& BST_Tree<kt, vt>::reverseIterator::operator++() {
	if (this->cur != nullptr) {
		this->cur = nextNode(this->tree->root);
		return *this;
	}
	else {
		throw exception("exception\n");
	}
}



// operator == обратный итератор
template<class kt, class vt>
bool BST_Tree<kt, vt>::reverseIterator::operator==(reverseIterator& it) {
	return ((this->tree == it.tree) && (this->cur == it.cur));
}

// оператор != обратный итератор
template<class kt, class vt>
bool BST_Tree<kt, vt>::reverseIterator::operator!=(reverseIterator& it) {
	return ((this->tree != it.tree) || (this->cur != it.cur));
}



