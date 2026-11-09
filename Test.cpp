#include <iostream>
#include"String.h"
#include"Matrix.h"
#include"SMatrix.h"
using namespace std;

int main()
{
	SMatrix a(3);
	for (int i = 0; i < a.getColums(); i++)
		for (int j = 0; j < a.getRows(); j++)
			a.at(i, j) = rand() % 10;
	a.display();
	cout << endl;
	a.Transpose().display();

}
