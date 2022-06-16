#pragma once



template<typename kt, typename vt>
class BST_Tree {
public:
	BST_Tree();
	BST_Tree(const BST_Tree&);


protected:
	class Node {
	public:
		vt value;
		kt key;
		Node* left;
		Node* right;
		Node() {};
		Node(kt, vt);

		~Node() {};
	};



public:

	// размер дерева
	int getSize();
	bool clear_tree(); // очистка дерева
	bool is_clear_tree(); // проверка на пустоту
	bool insert(kt, vt&); // включение данных с заданным ключом
	bool remove(kt); // удаление данных с заданным ключом
	vt& getByWriteAndRead(kt); // доступ по чтению записи к данным по ключу
	void print(Node*, int level = 5); // вывести дерево
	void printTree();


	//Node* BST_Root_Insert(Node*, kt&, vt&, bool);
	
	Node* Create_Tree_Node(kt&, vt&);
	void printNode(Node*);
	void delete_node(Node*); // удаление узла

	int getCountKeysHigherThanInserted(int k);
	
	
	

	void setCounterKey(int);

	int getCountNodes();
	void clearCountNodes() {
		this->count_nodes = 0;
	}

	class Iterator {
		BST_Tree* tree;
		Node* cur;

	public:
		friend class BST_Tree;
		Iterator();
		Iterator(BST_Tree&);


		// прототипы прямого итератора
		Iterator& operator++();
		bool operator==(Iterator&);
		bool operator!=(Iterator&);
		vt& operator*();

		Node* nextNode(Node* cur);

	};


	class reverseIterator {
		BST_Tree* tree;
		Node* cur;
		friend class BST_Tree;
	public:
		reverseIterator();
		reverseIterator(BST_Tree&);

		// прототипы реверс итератора
		bool operator==(reverseIterator&);
		bool operator!=(reverseIterator&);
		reverseIterator& operator++();
		vt& operator*();
		Node* nextNode(Node* cur);


	};

	friend Iterator;
	friend reverseIterator;

	Iterator begin();
	Iterator end();
	reverseIterator rbegin();
	reverseIterator rend();




private:
	Node* root = NULL;
	long size_tree = 0;
	long count_nodes = 0;
	int counterKey = 0;




public:
	~BST_Tree(void);
};






