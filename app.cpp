#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"
#include <cstring>
#include <string>

using namespace std;


void clear();
bool readFile(const char*, BST*);
int menu();

int main() {
	char file[] = "student.txt";
	BST tree;
	int source;
	int order;
	Student student;
	int search = 0;
	//readFile(file, &tree);
	//tree.PrintID();
	//tree.display(2, 2);
	//tree.deepestNodes();
	//student.id = search;
	//tree.CloneSubtree(tree, student);
	//tree.printLevelNode();
	//tree.printPath();

	int choice = 0;

	do {
		choice = menu();//choice the function

		if (choice == 1) {
			if(readFile(file, &tree)) {
				cout << "Successfully loaded student list." << endl;
				clear();
			}
			else{
				cout << "Failed to load student list." << endl;
				clear();
			}
		}
		else if (choice == 2) {
			tree.deepestNodes();
			clear();
		}
		else if (choice == 3) {
			cout << "Please select your choice (1 or 2): " << endl;
			cout << "1. Ascending order" << endl;
			cout << "2. Descending order" << endl;
			int order = 0;
			cout << endl;
			cout << "Choice-> ";
			cin >> order;
			cout << "You want to (1 or 2): " << endl;
			cout << "1. Print to screen" << endl;
			cout << "2. Print to file name 'student-info.txt' " << endl;
			int source = 0;
			cout << endl;
			cout << "Choice-> ";
			cin >> source;
			system("cls");
			if (tree.display(order, source)) {
				cout << endl;
				if (source == 2)
					cout << "Successfully print to file.... \n\n" << endl;
			}
			clear();
		}
		else if (choice == 4) {
			cout << "Student ID List" << endl;
			cout << "===========================================" << endl;
			tree.PrintID();
			cout << "===========================================" << endl;
			cout << "Enter the value that you want to clone: ";
			cin >> search;
			cout << endl;
			student.id = search;
			tree.CloneSubtree(tree, student);
			clear();
		}

		else if (choice == 5) {
			tree.printLevelNode();
			clear();
		}

		else if (choice == 6) {
			tree.printPath();
			clear();
		}

		else if (choice == 7) {
			cout << "Exit the program.\n\n" << endl;
		}

	} while (choice != 7);
	system("pause");
	return 0;
}

bool readFile(const char* file, BST* tree) {
	ifstream infile;
	Student student;
	string s;
	infile.open(file);

	if (!file) {
		cout << "Cannot open the file!!!";
		return false;
	}

	while (!infile.eof()) { // Read all student information
		infile.ignore(13);
		infile >> student.id;
		infile.ignore(8);
		infile.getline(student.name, 30);
		infile.ignore(10);
		infile.getline(student.address, 100);
		infile.ignore(6);
		infile >> student.DOB;
		infile.ignore(15);
		infile >> student.phone_no;
		infile.ignore(9);
		infile >> student.course;
		infile.ignore(7);
		infile >> student.cgpa;
		getline(infile, s); // Pass the empty line between each student

		tree->insert(student);
	}
	infile.close();
	return true;
}

int menu() {
	int select = 0;
	do {
		cout << "**********************************************************************************" << endl;
		cout << "\t\t Welcome to binary search tree menu" << endl;
		cout << "**********************************************************************************" << endl;
		cout << "Please select a function:" << endl;
		cout << "1.Read data to BST \n2.Print deepest nodes \n3.Display student \n4.Clone Subtree \n5.Print Level Nodes \n6.Print Path \n7.Exit " << endl;
		cout << "\nSelect:";
		cin >> select;
		cout << endl;
		if (select == 1)
			return 1;
		if (select == 2)
			return 2;
		if (select == 3)
			return 3;
		if (select == 4)
			return 4;
		if (select == 5)
			return 5;
		if (select == 6)
			return 6;
		if (select == 7)
			return 7;
		cout << "Please key in 1~7 only." << endl;
		cout << endl;
	} while (select != 7);//only key in 1-7
	return 0;
}

void clear() {
	cout << endl;
	cout << "Hit enter to return to the menu....." << "\n\n\n\n";
	cout << "<- Exit ";
	cin.ignore();
	cin.get();
	system("cls"); //clean output

};