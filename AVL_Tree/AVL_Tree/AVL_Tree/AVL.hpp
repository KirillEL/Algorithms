#pragma once
#include "BST_Tree.hpp"
#include <iostream>

using namespace std;

template<class kt, class vt>
class AVL_Tree : public BST_Tree<kt, vt> {

protected:
	void balancing(typename BST_Tree<kt, vt>::Node* node);
	void L(typename BST_Tree<kt,vt>::Node* node);
	void R(typename BST_Tree<kt,vt>::Node* node);
	int get_height(typename BST_Tree<kt, vt>::Node* node, int height);
	void printTree(typename BST_Tree<kt, vt>::Node* node, int level);
public:
	AVL_Tree() {};
	bool insert(kt key, vt& value);
	bool remove(kt key);
	void print();
	vt& getData(kt& key); // поиск по ключу
};


