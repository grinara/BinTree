#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <windows.h>
#include <vector>
using namespace std;
class Node {
	friend class BinTree;
private:
	int Data;
	Node* right, * left;
public:
	Node(int k = 0, Node* r=NULL, Node* l=NULL) {
		Data = k;
		right = r;
		left = l;
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
public:
	BinTree() { root = NULL; size = 0; }
	BinTree(int key) { root = new Node(key); size = 1; }
	BinTree(int key,int size) {
		root = new Node(key);
		for (int i = 0; i < size; i++) {
			insert(rand() % 13);
		}
	}
	BinTree(BinTree& c) {
		size = c.size;
		root = new Node(c.root->Data);
		vector<Node*> aa = c.inorder();
		for (int i = 0; i < aa.size();i++) {
			insert(aa[i]->Data);
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
		//Node* parent = NULL;
		while (nod && nod->Data != key) {
			if (nod->Data > key) { nod = nod->left; } //Движение по левой или правой ветви родительского узла
			else { nod = nod->right; }
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
				parent->left = nod->right;
				size--;
			}
			if (parent && parent->right == nod) {
				parent->right = nod->right;
				size--;
			}
			delete nod;
			return;
		}
		if (nod->right == NULL)
		{
			// Вместо nod подвешивается его левое поддерево
			if (parent && parent->left == nod)
				parent->left = nod->left;
			if (parent && parent->right == nod)
				parent->right = nod->left;
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
	void inorderLPK(Node* nod) {
		if (nod != NULL) {
			// Обходим лево
			inorderLPK(nod->left);
			// Обходим право
			inorderLPK(nod->right);
			// Обходим корень
			cout << nod->Data << " -> ";
		}
	}
	vector<Node*> inorder() {
		vector<Node*> a1;
		a1.push_back(root);
		for (int i = 0; a1.size() < size; i++) {
			if(a1[i]->left!=NULL){ a1.push_back(a1[i]->left); }
			if(a1[i]->right!=NULL){ a1.push_back(a1[i]->right); }
		}
		return a1;
	}
	BinTree& operator = (BinTree &c) {
		if (this != &c) {
			delete_tree(root);
			this->root = new Node(c.root->Data);
			vector<Node*> a1 = c.inorder();
			for (int i = 0; i < a1.size(); i++) {
				insert(a1[i]->Data);
			}
		}
		return *this;
	}
};

int main() {
	srand(time(NULL));
	BinTree t(13);
	t.insert(2);
	t.insert(1);
	t.insert(6);
	t.insert(3);
	t.insert(11);
	t.insert(37);
	t.insert(24);
	t.insert(22);
	t.insert(106);
	t.insert(1005);
	BinTree tt;
	tt = t;
	t.erase(37);
	tt.PrintTree(tt.GetRoot(), 0, 40, 0);
	//t->inorderLPK(t->GetRoot());
	//cout << endl;
	//t->inorder(t->GetRoot());
	//t->PrintTree(t->GetRoot(), 0, 40, 0);
	//cout << endl;
	//cout << t->find_max()->Data;
}