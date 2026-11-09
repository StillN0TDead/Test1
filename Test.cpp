#include <iostream>
#include"String.h"
#include"Matrix.h"
#include"SMatrix.h"
using namespace std;

int main()
{
	SMatrix a(3);
	Matrix b(3, 3);
	for (int i = 0; i < a.getColums(); i++)
		for (int j = 0; j < a.getRows(); j++)
		{
			a.at(i, j) = rand() % 10;
			b.at(i, j) = rand() % 10;
		}
	a.display();
	cout << endl<< "Matrix b:" << endl;
	b.display();
	cout << endl;
	a.Transpose().display();
	cout << endl << "Matrix b:" << endl;
	b.Transpose().display();
	cout << endl << "Sliced Matrix a:" << endl;
	a.slice(0, 0, 1, 2).display();
	cout << endl << "Matrix b:" << endl;
	b.slice(0, 0, 2, 3).display();
}
