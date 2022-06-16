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
		int bal = 0; // ������������
		Node() {
		};
		Node(kt, vt);
		~Node() {};
	};
public:
	// ������ ������
	int getSize();
	bool clear_tree(); // ������� ������
	bool is_clear_tree(); // �������� �� �������
	bool insert(kt, vt&); // ��������� ������ � �������� ������
	bool remove(kt); // �������� ������ � �������� ������
	vt& getByWriteAndRead(kt); // ������ �� ������ ������ � ������ �� �����
	void print(Node*, int level = 5); // ������� ������
	void printTree();
	Node* Create_Tree_Node(kt&, vt&);
	void printNode(Node*);
	void delete_node(Node*); // �������� ����
	int getCountKeysHigherThanInserted(int k);
	void recursiveTraversal(Node*, int);
	void setCounterKey(int);
	int getCountNodes();
	void clearCountNodes() {
		this->count_nodes = 0;
	}
	Node* search_parent(Node* node, Node* st_node);
	Node* searchKey(kt& key, Node* node);
	Node* search_end(Node*);
	class Iterator {
	protected:
		BST_Tree* tree;
		Node* cur;

	public:
		friend class BST_Tree;
		Iterator();
		Iterator(BST_Tree&);
		// ��������� ������� ���������
		Iterator& operator++();
		bool operator==(Iterator&);
		bool operator!=(Iterator&);
		vt& operator*();
		Node* nextNode(Node* cur);
	};
	class reverseIterator {
	protected:
		BST_Tree* tree;
		Node* cur;
		
	public:
		friend class BST_Tree;
		reverseIterator();
		reverseIterator(BST_Tree&);

		// ��������� ������ ���������
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
protected:
	Node* root = NULL;
	long size_tree = 0;
	int count_nodes = 0;
	int counterKey = 0;
public:
	~BST_Tree(void);
};







