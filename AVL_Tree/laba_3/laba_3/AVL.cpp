#include "AVL.hpp"
#include <iostream>
#include <iomanip>

using namespace std;



template<class kt, class vt>
int AVL_Tree<kt, vt>::get_height(typename BST_Tree<kt, vt>::Node* node, int height) {
	if (node == nullptr) return 0;
	int left_h = 0;
	int right_h = 0;
	if ((node->left == nullptr) && (node->right == nullptr)) return height;

	if (node->left != nullptr) {
		left_h = get_height(node->left, height + 1);
	}

	if (node->right != nullptr) {
		right_h = get_height(node->right, height + 1);
	}

	if (left_h >= right_h) return left_h;
	else return right_h;
}


// балансировка
template<class kt, class vt>
void AVL_Tree<kt, vt>::balancing(typename BST_Tree<kt, vt>::Node* node) {
	int h_l = 0;
	int h_r = 0;

	while (node != nullptr) {
		h_r = get_height(node->right, 1);
		h_l = get_height(node->left, 1);
		node->bal = h_r - h_l;

		if ((h_r - h_l) >= 2) {
			if (get_height(node->right->left, 1) <= get_height(node->right->right, 1)) {
				L(node);
				h_r = get_height(node->right, 1);
				h_l = get_height(node->left, 1);
				node->bal = h_r - h_l;
				
			}
			else {
				R(node->right);
				L(node);
				h_r = get_height(node->right, 1);
				h_l = get_height(node->left, 1);
				node->bal = h_r - h_l;
				
				
			}
		}
		else if ((h_l - h_r) >= 2) {
			if (get_height(node->left->right, 1) <= get_height(node->left->left, 1)) {
				R(node);
				h_r = get_height(node->right, 1);
				h_l = get_height(node->left, 1);
				node->bal = h_r - h_l;
				
			}
			else {
				L(node->left);
				R(node);
				h_r = get_height(node->right, 1);
				h_l = get_height(node->left, 1);
				node->bal = h_r - h_l;
				
			}
		}
		
		node = BST_Tree<kt, vt>::search_parent(node, this->root);
		
	}

}


// поворот вправо
template<class kt, class vt>
void AVL_Tree<kt, vt>::R(typename BST_Tree<kt, vt>::Node* node) {
	int h_r = 0;
	int h_l = 0;
	typename BST_Tree<kt, vt>::Node* leftSon = node->left;

	if (node != this->root) {
		typename BST_Tree<kt, vt>::Node* parent = BST_Tree<kt, vt>::search_parent(node, this->root);
		if (parent == nullptr) return;
		if (node == parent->right) parent->right = leftSon;
		else parent->left = leftSon;
	}
	else this->root = leftSon;
	node->left = leftSon->right;
	leftSon->right = node;
}

// поворот влево
template<class kt, class vt>
void AVL_Tree<kt, vt>::L(typename BST_Tree<kt, vt>::Node* node) {
	typename BST_Tree<kt, vt>::Node* rightSon = node->right;
	int h_r = 0;
	int h_l = 0;
	if (node != this->root) {
		typename BST_Tree<kt, vt>::Node* parent = BST_Tree<kt, vt>::search_parent(node, this->root);
		if (node == parent->right) parent->right = rightSon;
		else parent->left = rightSon;
	}
	else this->root = rightSon;
	node->right = rightSon->left;
	rightSon->left = node;
	
}


// вывод дерева
template<class kt, class vt>
void AVL_Tree<kt, vt>::printTree(typename BST_Tree<kt, vt>::Node* node, int level) {
	if (node == nullptr) return;
	this->printTree(node->right, level +1 );
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << node->key << "(" << node->bal << ")" << "\n";
	this->printTree(node->left, level + 1);
}


// добавление элемента
template<class kt, class vt>
bool AVL_Tree<kt, vt>::insert(kt key, vt& value) {
	int h_r = 0;
	int h_l = 0;
	if (this->size_tree != 0) {
		if (this->searchKey(key, this->root) != nullptr) return false;
		this->count_nodes = 0;
		typename BST_Tree<kt, vt>::Node* insert_node = this->root;

		bool node_found = false;
		
		while (!node_found) { 
			this->count_nodes++;
			
				if (key >= insert_node->key) {
				if (insert_node->right != nullptr) {
					
					insert_node = insert_node->right; 
					continue;
				}
				else {
					insert_node->right = new typename BST_Tree<kt, vt>::Node;
					insert_node->right->key = key;
					insert_node->right->value = value;
					node_found = true;
					insert_node = insert_node->right;
					
				}
			}
			else {
				if (insert_node->left != nullptr) {
					
					insert_node = insert_node->left;
					continue;
				}
				else {
					insert_node->left = new typename BST_Tree<kt, vt>::Node;
					insert_node->left->key = key;
					insert_node->left->value = value;
					node_found = true;
					insert_node = insert_node->left;
				}
			}
			balancing(insert_node);
		}
	}
	else {
		this->count_nodes = 1;
		this->root = new typename BST_Tree<kt, vt>::Node;
		this->root->key = key;
		this->root->value = value;
	}
	this->size_tree++;
	return true;

}


// вывод
template<class kt, class vt>
void AVL_Tree<kt, vt>::print() {
	if (this->size_tree != 0) printTree(this->root, 0);
}


// удаление узла
template<class kt, class vt>
bool AVL_Tree<kt, vt>::remove(kt key) {
	
	this->count_nodes = 0;
	if (this->size_tree == 0) return false;

	typename BST_Tree<kt, vt>::Node* search_key = BST_Tree<kt, vt>::searchKey(key, this->root);
	typename BST_Tree<kt,vt>::Node* balance = nullptr;
	typename BST_Tree<kt, vt>::Node* par_2_son = nullptr;
	bool par_with_2_son = false;
	kt d_key = 0;
	vt d_value = 0;
	while (search_key != nullptr) {
		if ((search_key->left == nullptr) && (search_key->right == nullptr)) {
			typename BST_Tree<kt, vt>::Node* par = BST_Tree<kt, vt>::search_parent(search_key, this->root);
			if (par != nullptr) {
				if (par->left == search_key) par->left = nullptr;
				if (par->right == search_key) par->right = nullptr;
				delete search_key;
				balance = par;
			}
			else {
				search_key = nullptr;
			}
		}
		else if ((search_key->left != nullptr) && (search_key->right == nullptr)) {
			typename BST_Tree<kt, vt>::Node* par = BST_Tree<kt, vt>::search_parent(search_key, this->root);

			if (par != nullptr) {
				if (par->left == search_key) par->left = search_key->left;
				if (par->right == search_key) par->right = search_key->left;

				balance = par;
			}
			else {
				this->root = search_key->left;
				balance = this->root;
			}
			delete search_key;
		}
		else if ((search_key->left == nullptr) && (search_key->right != nullptr)) {
			typename BST_Tree<kt, vt>::Node* par = BST_Tree<kt, vt>::search_parent(search_key, this->root);

			if (par != nullptr) {
				if (par->left == search_key) par->left = search_key->right;
				if (par->right == search_key) par->right = search_key->right;

				balance = par;
			}
			else {
				this->root = search_key->right;
				balance = this->root;
			}
			delete search_key;
		}
		else {
			typename BST_Tree<kt, vt>::Node* sub = BST_Tree<kt, vt>::search_end(search_key->left);
			par_with_2_son = true;
			par_2_son = search_key;
			d_key = sub->key;
			
			d_value = sub->value;

			search_key = sub;
			continue;
		}

		if (par_with_2_son) {
			par_2_son->key = d_key;
			par_2_son->value = d_value;
		}
		balancing(balance);
		this->size_tree--;
		return true;
	}
	return false;
}


// поиск по ключу
template<class kt, class vt>
vt& AVL_Tree<kt, vt>::getData(kt& key) {
	this->count_nodes = 1;
	if (this->root = nullptr) throw overflow_error("ИСКЛЮЧЕНИЕ\n");

	typename BST_Tree<kt, vt>::Node* s_node = this->root;

	while ((s_node != nullptr) && (s_node->key != key)) {
		this->count_nodes++;
		if (key >= s_node->key) {
			s_node = s_node->right;
			continue;
		}
		else {
			s_node = s_node->left;
			continue;
		}
	}

	if (s_node == nullptr) throw overflow_error("ИСКЛЮЧЕНИЕ\n");
	else return s_node->value;
}