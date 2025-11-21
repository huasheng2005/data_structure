#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::display(int order, int source) {
	BTNode* curr;

	curr = root;
	if (root == NULL) {// special case tree is empty
		cout << "Tree is empty!!" << endl;
		return false;
	}
	if (source == 1) {
		if (order == 1) {
			inOrderPrint();
		}
		if (order == 2) {
			PrintDescending(curr);
		}
	}
	if (source == 2) {
		ofstream outfile;
		outfile.open("student-info.txt");
		if (order == 1) {
			fileAscending(curr, outfile);
		}
		if (order == 2) {
			fileDescending(curr, outfile);
		}
		outfile.close();
	}
	return true;
}

void BST::PrintDescending(BTNode* curr) {//For display with descending
	if (curr == NULL) {
		return;
	}
	PrintDescending(curr->right);// exchange the left and right
	curr->item.print(cout);
	PrintDescending(curr->left);
}

void BST::fileAscending(BTNode* curr, ofstream& outfile) {//For write file with ascending
	if (curr == NULL) {
		return;
	}
	fileAscending(curr->left, outfile);
	curr->item.print(outfile);
	fileAscending(curr->right, outfile);
}

void BST::fileDescending(BTNode* curr, ofstream& outfile) {// For write file with descending
	if (curr == NULL) {
		return;
	}
	fileDescending(curr->right, outfile);
	curr->item.print(outfile);
	fileDescending(curr->left, outfile);
}

bool BST::deepestNodes() {
	BTNode* curr;
	int depth = 0;//For track the depth level
	int MAXdepth;// Find the deepest nodes
	if (root == NULL) { //special case tree is empty
		cout << "The tree is empty" << endl;
		return false;
	}
	curr = root;
	countNodes(curr, depth, MAXdepth);// Find the deepest nodes
	cout << "The Deepest Node is :";
	printNodes(curr, depth, MAXdepth);// Print the deepest nodes
	cout << endl;
	return true;
}

void BST::PrintID() {
	if (root == NULL) return;// handle special case
	else PrintID2(root);// do normal process
	cout << endl;
}

void BST::PrintID2(BTNode* cur) {
	if (cur == NULL) {
		return;
	}
	cout << cur->item.id << " ";
	PrintID2(cur->left);
	PrintID2(cur->right);
	
}

void BST::countNodes(BTNode* curr, int depth, int& MAXdepth) {
	if (depth > MAXdepth) {// Renew the MAXdepth
		MAXdepth = depth;
	}
	if (curr == NULL) {
		return;
	}
	countNodes(curr->left, depth + 1, MAXdepth);//Recurse left and right
	countNodes(curr->right, depth + 1, MAXdepth);

	return;
}

void BST::printNodes(BTNode* curr, int depth, int MAXdepth) {
	if (curr == NULL) {
		return;
	}
	if (depth == MAXdepth - 1) {// If the depth reaches the deepest
		cout << curr->item.id << "  ";
	}
	printNodes(curr->left, depth + 1, MAXdepth);//Recurse left and right
	printNodes(curr->right, depth + 1, MAXdepth);
}



BTNode* BST::findNode(BTNode* curr, type item) {//Find the node that we want
	while (curr != NULL) {
		if (item.id == curr->item.id) {
			return curr;
		}
		else if (item.id < curr->item.id) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	return NULL; //return NULL when cannot find
}

bool BST::CloneSubtree(BST t1, type item) {
	if (t1.empty()) { //special case tree is empty
		cout << "Tree is empty" << endl;
		return false;
	}
	BTNode* curr;
	curr = t1.root;
	BST tree2;
	BTNode* cloneSubtreeRoot;

	cloneSubtreeRoot = findNode(curr, item);//Find the nodes which is subtree root
	curr = cloneSubtreeRoot;
	CloneSubtree2(curr, t1, item, tree2);//Put all subtree element in the tree2
	if (tree2.empty()) {// If the node not in the tree
		cout << "Cannot clone the tree" << endl;
		return false;
	}
	else {
		cout << "Tree1 List" << endl;
		cout << "======================================" << endl;
		t1.preOrderPrint(); // Display the t1
		cout << "Subtree List" << endl;
		cout << "======================================" << endl;
		tree2.preOrderPrint();//Display the tree2
		return true;
	}
}
void BST::CloneSubtree2(BTNode* curr, BST tree, type item, BST& tree2) {
	if (curr == NULL) {
		return;
	}
	tree2.insert(curr->item);
	CloneSubtree2(curr->left, tree, item, tree2);
	CloneSubtree2(curr->right, tree, item, tree2);
	return;
}

bool BST::printLevelNode() {
	if (empty()) {
		//special case tree is empty
		cout << "Tree is empty!!!" << endl;
		return false;
	}
	Queue q;
	BTNode* curr;
	q.enqueue(root);
	int level = 1;
	while (!q.empty()) {
		int size = q.count; // Count how many node in a level
		cout << "Level " << level << " Nodes: ";
		// Display the number in each level node
		for (int i = 0; i < size; ++i) {
			q.dequeue(curr);
			cout << curr->item.id << " ";
			//Enqueue next level node
			if (curr->left) {
				q.enqueue(curr->left);
			}
			if (curr->right) {
				q.enqueue(curr->right);
			}
		}
		level++;
		cout << endl;
	}
	cout << endl;
	return true;
}



bool BST::printPath() {
	if (root == NULL) {
		cout << "Tree is empty.\n";
		return false;
	}

	cout << "Below are all the external paths for the tree:\n";
	stack<BTNode*> path;
	printPath2(root, path);//Start from top
	return true;
}

void BST::printPath2(BTNode* curr, stack<BTNode*>& path) {
	if (curr == NULL) return;

	path.push(curr); // Push current node to path

	if (curr->left == NULL && curr->right == NULL) {// If it's a leaf node, print the path
		stack<BTNode*> tempStack = path;
		stack<BTNode*> reverseStack;

		while (!tempStack.empty()) {// Reverse the path into reverseStack
			reverseStack.push(tempStack.top());
			tempStack.pop();
		}

		while (!reverseStack.empty()) {// Print from root to leaf
			cout << reverseStack.top()->item.id << " ";
			reverseStack.pop();
		}
		cout << endl;
	}

	printPath2(curr->left, path);
	printPath2(curr->right, path);

	path.pop(); // Backtrack after visiting children
}