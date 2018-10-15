#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

template <class ItemType>
struct TreeNode {
	ItemType contents;
	TreeNode *left;
	TreeNode *right;
	char BalanceFactor;
};

template <class ItemType>
class Tree
{
public:
	Tree();
	~Tree();
	void insertItem(ItemType item);
	void printTree();
	void searchForItem(ItemType item);
	void deleteItem(ItemType item);

private:
	void Insert(TreeNode<ItemType> *&root, ItemType item, bool &taller);
	void leftBalance(TreeNode<ItemType> *&root,bool &taller);
	void rightBalance(TreeNode<ItemType> *&root, bool &taller);
	void rotateLeft(TreeNode<ItemType> *&root);
	void rotateRight(TreeNode<ItemType> *&root);

	void Delete(TreeNode<ItemType> *&root, ItemType item , bool &shorter);
	void deleteNode(TreeNode<ItemType> *&root, bool &shorter);
	void deleteRightBalance(TreeNode<ItemType> *&root, bool &shorter);
	void deleteLeftBalance(TreeNode<ItemType> *&root, bool &shorter);
	void getPredecessor(TreeNode<ItemType> *root, ItemType &data);

	void Print(TreeNode<ItemType> *&root);
	void Search(TreeNode<ItemType> *&root, ItemType item);

	TreeNode<ItemType> *root;
};

template <class ItemType>
Tree<ItemType>::Tree() {
}

template <class ItemType>
Tree<ItemType>::~Tree() {}

template <class ItemType>
void Tree<ItemType>::insertItem(ItemType item) {
	bool taller;
	Insert(root, item, taller);
}

template <class ItemType>
void Tree<ItemType>::Insert(TreeNode<ItemType> *&root, ItemType item, bool &taller) {
	// If the tree is null then create a new treenode here with the input.
	if (root == NULL) {
		root = new TreeNode<ItemType>;
		root->contents = item;
		root->left = NULL;
		root->right = NULL;
		root->BalanceFactor = 'E';
		taller = true;
	}
	// If the input is already in the tree return this error.
	else if (item == root->contents){
		cerr << "Duplicate item is not allowed in the AVL tree." << endl;
	}
	// If the input is less than the current node call insert on the left node/subtree.
	else if (item < root->contents) {
		Insert(root->left, item, taller);
		if (taller) {
			switch (root->BalanceFactor) {
			case 'E':
				root->BalanceFactor = 'L';
				break;
			case 'R':
				root->BalanceFactor = 'E';
				taller = false;
				break;
			case 'L':
				leftBalance(root, taller);
				break;
			}
		}
	}
	// If the input is greater than the current node call insert on the right node/subtree.
	else if (item > root->contents) {
		Insert(root->right, item, taller);
		if (taller) {
			switch (root->BalanceFactor) {
			case 'E':
				root->BalanceFactor = 'R';
				break;
			case 'R':
				rightBalance(root,taller);
				break;
			case 'L':
				root->BalanceFactor = 'E';
				taller = false;
				break;
			}
		}
	}
}

template <class ItemType>
void Tree<ItemType>::rightBalance(TreeNode<ItemType> *&root, bool &taller) {
	TreeNode<ItemType> *rs = root->right;
	TreeNode<ItemType> *ls;

	switch (rs->BalanceFactor) {
	case 'E':
		cerr << "The tree is already balanced." << endl;
		break;
	case 'R':
		root->BalanceFactor = rs->BalanceFactor = 'E';
		rotateLeft(root);
		taller = false;
		break;
	case 'L':
		ls = rs->left;
		switch (ls->BalanceFactor) {
		case 'E':
			root->BalanceFactor = rs->BalanceFactor = 'E';
			break;
		case 'R':
			root->BalanceFactor = 'L';
			rs->BalanceFactor = 'E';
			break;
		case 'L':
			root->BalanceFactor = 'E';
			rs->BalanceFactor = 'R';
			break;
		}
		ls->BalanceFactor = 'E';
		rotateRight(root->right);
		rotateLeft(root);
		taller = false;
		break;
	}
}

template <class ItemType>
void Tree<ItemType>::leftBalance(TreeNode<ItemType> *&tree, bool &taller) {
	TreeNode<ItemType> *ls = root->left;
	TreeNode<ItemType> *rs;

	switch (ls->BalanceFactor) {
	case 'E':
		cerr << "The tree is already balanced." << endl;
		break;
	case 'R':
		rs = ls->right;
		switch (rs->BalanceFactor) {
		case 'E':
			root->BalanceFactor = ls->BalanceFactor = 'E';
			break;
		case'R':
			root->BalanceFactor = 'E';
			ls->BalanceFactor = 'L';
			break;
		case 'L':
			root->BalanceFactor = 'R';
			ls->BalanceFactor = 'E';
			break;
		}
		rs->BalanceFactor = 'E';
		rotateLeft(root->left);
		rotateRight(root);
		taller = false;
		break;
	case 'L':
		root->BalanceFactor = ls->BalanceFactor = 'E';
		rotateRight(root);
		taller = false;
		break;
	}
}

template <class ItemType>
void Tree<ItemType>::rotateLeft(TreeNode<ItemType> *&root){
	TreeNode<ItemType> *rs;

	if (root == NULL) {
		cerr << "Cannot rotate an empty tree in rotateLeft." << endl;
	}
	else if (root->right == NULL) {
		cerr << "Cannot make an empty subtree the root in rotateLeft." << endl;
	}
	else {
		rs = root->right;
		root->right = rs->left;
		rs->left = root;
		root = rs;
	}
}

template <class ItemType>
void Tree<ItemType>::rotateRight(TreeNode<ItemType> *&root) {
	TreeNode <ItemType> *ls;

	if (root == NULL) {
		cerr << "Cannot rotate an empty tree in rotateRight." << endl;
	}
	else if (root->left == NULL) {
		cerr << "Cannot make an empty subtree the root in rotateRight." << endl;
	}
	else {
		ls = root->left;
		root->left = ls->right;
		ls->right = root;
		root = ls;
	}
}

template <class ItemType>
void Tree<ItemType>::printTree() {
	Print(root);
}

template <class ItemType>
void Tree<ItemType>::Print(TreeNode<ItemType> *&root) {
	if (root == NULL) {
		cerr << "The tree is empty";
		return;
	}

	if (root->left != NULL) {
		Print(root->left);
	}

	// Printing out the contents of this Node.
	cout << "Contents: " << left << setw(15) << root->contents;
	if (root->left != NULL) {
		cout << "Left: " << setw(15) << root->left->contents;
	}
	else {
		cout << "Left: " << setw(15) << "NULL";
	}
	if (root->right != NULL) {
		cout << "Right: " << setw(15) << root->right->contents;
	}
	else {
		cout << "Right: " << setw(15) << "NULL";
	}
	cout << "Balance Factor : " << setw(15) << root->BalanceFactor << endl;

	if (root->right != NULL) {
		Print(root->right);
	}
}

template <class ItemType>
void Tree<ItemType>::searchForItem(ItemType item) {
	Search(root, item);
}

template <class ItemType>
void Tree<ItemType>::Search(TreeNode<ItemType> *&root, ItemType item) {
	if (root == NULL) {
		cout << "The item could not be found in the tree." << endl;
	}
	else if (item > root->contents) {
		Search(root->right, item);
	}
	else if (item < root->contents) {
		Search(root->left, item);
	}
	else if (item == root->contents) {
		cout << "The item is in the tree!" << endl;
	}
}

template <class ItemType>
void Tree<ItemType>::deleteItem(ItemType item) {
	bool shorter;
	Delete(root, item, shorter);
}

template <class ItemType>
void Tree<ItemType>::Delete(TreeNode<ItemType> *&root, ItemType item, bool &shorter) {
	if (root != NULL) {
		if (item < root->contents) {
			Delete(root->left, item, shorter);
			if (shorter) {
				switch (root->BalanceFactor) {
				case 'E':
					root->BalanceFactor = 'R';
					shorter = false;
					break;
				case 'R':
					deleteRightBalance(root, shorter);
					break;
				case 'L':
					root->BalanceFactor = 'E';
					break;
				}
			}
		}
		else if (item > root->contents) {
			Delete(root, item, shorter);
			if (shorter) {
				switch (root->BalanceFactor) {
				case 'E':
					root->BalanceFactor = 'L';
					shorter = false;
					break;
				case 'R':
					root->BalanceFactor = 'E';
					break;
				case 'L':
					deleteLeftBalance(root, shorter);
					break;
				}
			}
		}
		else {
			deleteNode(root, shorter);
		}
	}
	else {
		cout << "\nNOTE: " << item << "is not in the tree and cannot be deleted.";
	}
}

template <class ItemType>
void Tree<ItemType>::deleteNode(TreeNode<ItemType> *&root, bool &shorter) {
	ItemType data;
	TreeNode<ItemType> *tempPtr;
	tempPtr = root;
	if (root->left == NULL) {
		root = root->right;
		delete tempPtr;
		shorter = true;
	}
	else if (root->right == NULL) {
		root = root->left;
		delete tempPtr;
		shorter = true;
	}
	else {
		getPredecessor(root, data);
		root->contents = data;
		Delete(root->left, data, shorter);
		if (shorter) {
			switch (root->BalanceFactor) {
			case 'E':
				root->BalanceFactor = 'R';
				shorter = false;
				break;
			case 'R':
				deleteRightBalance(root, shorter);
				break;
			case 'L':
				root->BalanceFactor = 'E';
				break;
			}
		}
	}
}

template <class ItemType>
void Tree<ItemType>::getPredecessor(TreeNode<ItemType> *root, ItemType &data) {
	root = root->left;
	while (root->right != NULL) {
		root = root->right;
	}
	data = root->contents;
}

template <class ItemType>
void Tree<ItemType>::deleteRightBalance(TreeNode<ItemType> *&root, bool &shorter) {
	TreeNode<ItemType> *rs = root->right;
	TreeNode<ItemType> *ls;
	switch (rs->BalanceFactor) {
	case 'E':
		root->BalanceFactor = 'R';
		rs->BalanceFactor = 'L';
		rotateLeft(root);
		shorter = false;
		break;
	case 'R':
		root->BalanceFactor = rs->BalanceFactor = 'E';
		rotateLeft(root);
		shorter = true;
		break;
	case 'L':
		ls = rs->left;
		switch (ls->BalanceFactor) {
		case 'E':
			root->BalanceFactor = rs->BalanceFactor = 'E';
			break;
		case 'R':
			root->BalanceFactor = 'L';
			rs->BalanceFactor = 'E';
			break;
		case 'L':
			root->BalanceFactor = 'E';
			rs->BalanceFactor = 'R';
			break;
		}
		ls->BalanceFactor = 'E';
		rotateRight(root->right);
		rotateLeft(root);
		shorter = true;
	}
}

template <class ItemType>
void Tree<ItemType>::deleteLeftBalance(TreeNode<ItemType> *&root, bool &shorter) {
	TreeNode<ItemType> *ls = root->left;
	TreeNode<ItemType> *rs;
	switch (ls->BalanceFactor) {
	case 'E':
		root->BalanceFactor = 'L';
		ls->BalanceFactor = 'R';
		rotateRight(root);
		shorter = false;
		break;
	case 'R':
		rs = ls->right;
		switch (rs->BalanceFactor) {
		case 'E':
			root->BalanceFactor = ls->BalanceFactor = 'e';
			break;
		case 'R':
			root->BalanceFactor = 'E';
			ls->BalanceFactor = 'L';
			break;
		case 'L':
			root->BalanceFactor = 'R';
			ls->BalanceFactor = 'E';
			break;
		}
		rs->BalanceFactor = 'E';
		rotateLeft(root->left);
		rotateRight(root);
		shorter = true;
		break;
	case 'L':
		root->BalanceFactor = ls->BalanceFactor = 'E';
		rotateRight(root);
		shorter = true;
		break;
	}
}