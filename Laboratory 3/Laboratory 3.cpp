// Laboratory 3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h> 
#include <sstream>
#include <conio.h>
#include <stdlib.h>

struct NodeData {
	int value;
	int row_position;
	int column_position;
};

struct Node {
	NodeData data;
	Node* next;
};

#pragma warning(disable : 4996);
void gotoxy(int x, int y);
int DisplayMainMenu();
Node *reading(std::string file, Node *head, int &row_number, int &column_number);
Node *NewElement(int value, int row_position, int column_position);
Node *AddEnd(Node *head, Node *new_element);
void PrintList(Node *head);
Node *MatrixAddition(Node *matrix1, Node *matrix2, int row_number, int column_number);
void swap(struct Node *a, struct Node *b);
void bubbleSort(Node *start);
Node *Transposition(Node *start);
Node *MatrixMultiplication(Node *matrix1, Node *matrix2, int row1, int col1, int row2, int column2);
void PrintMatrix(Node *head, int row_number, int column_number);
void MainMenu_Addition();
void MainMenu_Multiplication();


int main()
{
	while (1)
	{
		int selection = DisplayMainMenu();
		switch (selection)
		{
			case 1:
			{
				MainMenu_Addition();
				break;
			}	
			case 2:
			{
				MainMenu_Multiplication();
				break;
			}
			case 3:

				break;
			case 4:

			default:
				return 0;
		};
	}
	return 0;

}

void MainMenu_Addition() {
	Node *head1 = NULL;
	Node *head2 = NULL;
	int row1, row2, column1, column2;
	head1 = reading("input", head1, row1, column1);
	PrintList(head1);
	std::cout << "Matrix1" << "\n";
	PrintMatrix(head1, row1, column1);
	head2 = reading("input2", head2, row2, column2);
	PrintList(head2);
	std::cout << "Matrix2" << "\n";
	PrintMatrix(head2, row2, column2);
	if ((row1 == row2) && (column1 == column2)) {
		Node *head_result = NULL;
		head_result = MatrixAddition(head1, head2, row1, column1);
		PrintList(head_result);
		std::cout << "Sum of two matrices:" << "\n";
		PrintMatrix(head_result, row1, column1);
	}
}

void MainMenu_Multiplication() {
	Node *head1 = NULL;
	Node *head2 = NULL;
	int row1, row2, column1, column2;
	head1 = reading("input3", head1, row1, column1);
	PrintList(head1);
	std::cout << "Matrix1" << "\n";
	PrintMatrix(head1, row1, column1);
	head2 = reading("input4", head2, row2, column2);
	PrintList(head2);
	std::cout << "Matrix2" << "\n";
	PrintMatrix(head2, row2, column2);
	if (column1 == row2) {
		Node *head_transposed = Transposition(head2);
		PrintList(head_transposed);
		std::cout << "Matrix2 transposed" << "\n";
		PrintMatrix(head_transposed, row2, column2);
		Node *head_result = NULL;
		head_result = MatrixMultiplication(head1, head_transposed, row1, column1, column2, row2);
		PrintList(head_result);
		std::cout << "Multiplication of two matrices:" << "\n";
		PrintMatrix(head_result, row1, column2);
	}
	else {
		::system("cls");  // clear screen
		gotoxy(5, 4);
		std::cout << "Error";
		system("pause");
	}
}

int DisplayMainMenu()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Addition of two matrices";

	gotoxy(5, 7);
	std::cout << "2. Multiplication of two matrices";

	gotoxy(5, 8);
	std::cout << "3. Save and output";

	gotoxy(5, 9);
	std::cout << "4. Exit";

	gotoxy(5, 10);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

Node *MatrixAddition(Node *matrix1, Node *matrix2, int row_number, int column_number) {
	Node *result = NULL;
	while ((matrix1 != NULL) && (matrix2 != NULL)) {
		if ((matrix1->data.row_position > matrix2->data.row_position) ||
			((matrix1->data.row_position == matrix2->data.row_position) && (matrix1->data.column_position > matrix2->data.column_position))) {
			result = AddEnd(result, NewElement(matrix2->data.value, matrix2->data.row_position, matrix2->data.column_position));
			matrix2 = matrix2->next;
		} else if ((matrix1->data.row_position < matrix2->data.row_position) ||
			((matrix1->data.row_position == matrix2->data.row_position) && (matrix1->data.column_position < matrix2->data.column_position))) {
			result = AddEnd(result, NewElement(matrix1->data.value, matrix1->data.row_position, matrix1->data.column_position));
			matrix1 = matrix1->next;
		}
		else {
			int value = matrix1->data.value + matrix2->data.value;
			result = AddEnd(result, NewElement(value, matrix1->data.row_position, matrix1->data.column_position));
			matrix1 = matrix1->next;
			matrix2 = matrix2->next;
		}
	}

	while (matrix1 != NULL) {
		result = AddEnd(result, NewElement(matrix1->data.value, matrix1->data.row_position, matrix1->data.column_position));
		matrix1 = matrix1->next;
	}
	while (matrix2 != NULL) {
		result = AddEnd(result, NewElement(matrix2->data.value, matrix2->data.row_position, matrix2->data.column_position));
		matrix2 = matrix2->next;
	}
	return result;
}

Node *reading(std::string file, Node *head, int &row_number, int &column_number) {
	::system("cls");  // clear screen
	FILE *matrix;
	char filename[25];
	std::string str_filename;
	str_filename = file + ".txt";
	std::stringstream(str_filename) >> filename;
	matrix = fopen(filename, "r");

	int n, m; // nuber of rows and columns
	fscanf(matrix, "%d", &n);
	row_number = n;
	fscanf(matrix, "%d", &m);
	column_number = m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int k;
			fscanf(matrix, "%d", &k);
			if (k != 0) {
				head = AddEnd(head, NewElement(k, i, j));
			}

		}
	return head;
}

Node *NewElement(int value, int row_position, int column_position) {
	Node *new_element = new Node();
	new_element->data.value = value;
	new_element->data.row_position = row_position;
	new_element->data.column_position = column_position;
	new_element->next = NULL;
	return new_element;
}

Node *AddEnd(Node *head, Node *new_element) {
	Node *x = head;
	if (head == NULL)
		return new_element;

	while (x->next != NULL) {
		x = x->next;
	}

	x->next = new_element;
	return head;
}

Node *Transposition(Node *start) {
	Node *x = start;
	while (x != NULL) {
		int temp = x->data.row_position;
		x->data.row_position = x->data.column_position;
		x->data.column_position = temp;
		x = x->next;
	}
	bubbleSort(start);
	return start;
}

Node *MatrixMultiplication(Node *matrix1, Node *matrix2, int row1, int column1, int row2, int column2) {
	Node *x = matrix1;
	Node *y = matrix2;
	int row_result = 0;
	int column_result = 0;
	Node *result = NULL;
	
	while (x != NULL) {
		Node *current_Xrow = x;
		y = matrix2;
		while (y != NULL) {
			int const_row1 = x->data.row_position;
			int const_row2 = y->data.row_position;
			int value = 0;

			while ((x->data.row_position == const_row1) && (y->data.row_position == const_row2)) {
				if (x->data.column_position == y->data.column_position) {
					value = value + x->data.value*y->data.value;
					x = x->next;
					y = y->next;
				} else 
					if (x->data.column_position < y->data.column_position) x = x->next;
				else if (x->data.column_position > y->data.column_position) y = y->next;
				if (x == NULL) break;
				if (y == NULL) break;
			}
			if (value != 0) result = AddEnd(result, NewElement(value, const_row1, const_row2));
			if (y != NULL) {
				x = current_Xrow;
				while (y->data.row_position == const_row2) y = y->next;
			}
		}
		while ((x != NULL) && (x->data.row_position == current_Xrow->data.row_position)) x = x->next;
	}

	return result;
}

void bubbleSort(Node *start)
{
	int swapped;
	Node *ptr1;
	Node *lptr = NULL;
	if (start == NULL) //if list is empty
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->data.row_position > ptr1->next->data.row_position)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

void swap(Node *a, Node *b)
{
	NodeData temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void gotoxy(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void PrintList(Node *head) {
	::system("cls");  // clear screen
	Node *x = head;
	while (x != NULL) {
		std::cout << x->data.row_position << " " << x->data.column_position << " " << x->data.value << "\n";
		x = x->next;
	}
	system("pause");
}

void PrintMatrix(Node *head, int row_number, int column_number) {
	std::cout << "Matrix representation: " << "\n";
	Node *x = head;
	int cur_row = 0;
	int cur_col = 0;
	int row = x->data.row_position;
	int column = x->data.column_position;
	int value = x->data.value;
	x = x->next;
	while ((cur_row <= row_number - 1) && (cur_col <= column_number - 1)) {
 		while (cur_row != row) {
			for (int i = cur_col; i < column_number; i++) std::cout << 0 << " ";
			cur_col = 0;
			std::cout << "\n";
			cur_row++;
		}
    	for (int i = cur_col; i < column; i++) { 
			std::cout << 0 << " ";
			cur_col++;
		};
		if ((cur_col == column) && (cur_row == row)) {
			std::cout << value << " ";
			cur_col++;
			if (x != NULL) {
				row = x->data.row_position;
				column = x->data.column_position;
				value = x->data.value;
				x = x->next;
			} else value = 0;
		}
		if ((cur_row < row) || ((x == NULL) && (value == 0))) {
			for (int i = cur_col; i < column_number; i++) {
				std::cout << 0 << " ";
				cur_col++;
			};
		}
		if (cur_col == column_number) {
			std::cout << "\n";
			cur_col = 0;
			cur_row++;
		}
	}
	system("pause");
}