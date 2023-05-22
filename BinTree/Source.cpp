#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <windows.h>
using namespace std;
class Node {
	friend class BinTree;
public:
	int Data, num;
	Node* right, * left;
public:
	Node(int k = 0, int n = 0, Node* r=NULL, Node* l=NULL) {
		num = n;
		Data = k;
		right = r;
		left = l;
	}
	~Node() {
		num = 0;
		Data = 0;
		delete right;
		delete left;
	}
};

class BinTree {
private:
	Node* root;
	int size;
	void delete_tree(Node* nod) {
		if (nod)
		{
			delete_tree(nod->left);
			delete_tree(nod->right);
			delete nod;
		}
	}
	bool printLevel(Node* nod, int level)
	{
		if (nod == NULL) {
			return false;
		}
		if (level == 1)
		{
			cout << nod->Data << " ";// вернуть true, если хотя бы один узел присутствует на заданном уровне
			return true;
		}
		bool left = printLevel(nod->left, level - 1);
		bool right = printLevel(nod->right, level - 1);

		return left || right;
	}
public:
	BinTree() { root = new Node(); }
	BinTree(int key) { root = new Node(key); }
	BinTree(int key,int size) {
		root = new Node(key);
		for (int i = 0; i < size; i++) {
			insert(rand() % 13);
		}
	}
	~BinTree() {
		delete_tree(root);
	}
	void PrintTree(Node* p, int l, int r, int y) {
		if (p == NULL) return;
		int x = (l + r)/2;
		HANDLE hCon;
		COORD cPos;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		cPos.Y = y; // координата консоли по У
		cPos.X = x;  // координата консоли по Х  
		SetConsoleCursorPosition(hCon, cPos); // Установка курсора в положение (x,y)
		cout << p->Data;
		PrintTree(p->left, l, x, y + 3);
		PrintTree(p->right, x, r, y + 3);
	}
	Node* GetRoot() {
		return root;
	}
	Node* find(int key) {
		if (root == NULL)return root;
		Node* nod = root;
		Node* parent = NULL;
		while (nod && nod->Data != key) {
			if (nod->Data > key) { parent = nod; nod = nod->left; } //Движение по левой или правой ветви родительского узла
			else { parent = nod; nod = nod->right; }
		}
		return nod;
	}
	Node* find_prev(int key) {
		if (root == NULL)return root;
		if (root->Data == key) return root;
		Node* nod = root;
		Node* parent = NULL;
		while (nod && nod->Data != key) {
			if (nod->Data > key) { parent = nod; nod = nod->left; } //Движение по левой или правой ветви родительского узла
			else { parent = nod; nod = nod->right; }
		}
		return parent;
	}
	void insert(int key) {
		Node* nod = root;
		while (nod && nod->Data != key) {
			if (nod->Data > key && nod->left == NULL) {
				nod->left = new Node(key);//новый узел формируется по левой ветви
				size++;
				return;
			}
			if (nod->Data < key && nod->right == NULL) {
				nod->right = new Node(key);//новый узел формируется по правой ветви
				size++;
				return;
			}
			if (nod->Data > key){ nod = nod->left; } //Движение по левой или правой ветви родительского узла
			else{ nod = nod->right; }
		}
		
	}
	void erase(int key) {
		Node* nod = root;
		Node* parent = NULL;
		while (nod && nod->Data != key)
		{
			parent = nod;
			if (nod->Data > key)
			{
				nod = nod->left;
			}
			else
			{
				nod = nod->right;
			}
		}
		if (!nod)
			return;
		if (nod->left == NULL)
		{
			// Вместо nod подвешивается его правое поддерево
			if (parent && parent->left == nod) {
				parent->left = new Node(nod->right->Data, nod->right->num, nod->right->right, nod->right->left);
				size--;
			}
			if (parent && parent->right == nod) {
				parent->right = new Node(nod->right->Data, nod->right->num, nod->right->right, nod->right->left);
				size--;
			}
			delete nod;
			return;
		}
		if (nod->right == NULL)
		{
			// Вместо nod подвешивается его левое поддерево
			if (parent && parent->left == nod)
				parent->left = new Node(nod->left->Data, nod->left->num, nod->left->right, nod->left->left);
			if (parent && parent->right == nod)
				parent->right = new Node(nod->left->Data, nod->left->num, nod->left->right, nod->left->left);
			delete nod;
			return;
		}
		// У элемента есть два потомка, тогда на место элемента поставим
		// наименьший элемент из его правого поддерева
		Node* replace = nod->right;
		while (replace->left)
			replace = replace->left;
		int replace_value = replace->Data;
		erase(replace_value);
		nod->Data = replace_value;

	}
	Node* find_max() {
		if (root == NULL)return root;
		Node* nod = root;
		while (nod->right!=NULL) {
			nod = nod->right;
		}
		return nod;
	}
	Node* find_min() {
		if (root == NULL)return root;
		Node* nod = root;
		while (nod->left != NULL) {
			nod = nod->left;
		}
		return nod;
	}
	void inorderLKP(Node* nod) {
		if (nod != NULL) {
			// Обходим лево
			inorderLKP(nod->left);
			// Обходим корень
			cout << nod->Data << " -> ";
			// Обходим право
			inorderLKP(nod->right);
		}
	}
	void inorderKLP(Node* nod) {
		if (nod != NULL) {
			// Обходим корень
			cout << nod->Data << " -> ";
			// Обходим лево
			inorderKLP(nod->left);
			// Обходим право
			inorderKLP(nod->right);
		}
	}
	void inorderKPL(Node* nod) {
		if (nod != NULL) {
			// Обходим корень
			cout << nod->Data << " -> ";
			// Обходим право
			inorderKPL(nod->right);
			// Обходим лево
			inorderKPL(nod->left);
		}
	}
	void inorder(Node* nod)
	{
		// начинаем с уровня 1 — до высоты дерева
		int level = 1;
		// работать до тех пор, пока printLevel() не вернет false
		while (printLevel(nod, level)) {
			level++;
		}
	}
};

int main() {
	srand(time(NULL));
	BinTree* t = new BinTree(13);
	t->insert(2);
	t->insert(1);
	t->insert(6);
	t->insert(3);
	t->insert(11);
	t->insert(37);
	t->insert(24);
	t->insert(22);
	t->insert(106);
	t->insert(1005);
	//t->erase(37);
	//t->PrintTree(t->GetRoot(), 0, 40, 0);
	//cout << endl;
	t->inorder(t->GetRoot());
	//t->PrintTree(t->GetRoot(), 0, 40, 0);
	//cout << endl;
	//cout << t->find_max()->Data;
}