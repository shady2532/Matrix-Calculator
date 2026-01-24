#include <iostream>
#include <cmath>
#include <vector>
#include "matrix.h"
using namespace std;

int main()
{
	// matrices are classes
	Matrix<long long> matrixA;				// matrix A
	Matrix<long long> matrixB;				// matrix B
	Matrix<long long> sumMatrix;			// this was for storing the sum
	Matrix<long long> subMatrix;			// this one for the subtraction
	Matrix<long long> multiplicationMatrix; // this for the multiplication of (A & B)
	Matrix<double> divisionMatrix;			// this for the division of (A & B)
	// some variables that I don't know how it got so many like this
	long long choice;				  // variable to choose operation
	long long rowA, colA, rowB, colB; // rows and columns for our 2 matrices

	cout << "Please enter dimensions of Matrix A:" << endl;
	cin >> rowA >> colA;
	cout << "Please enter values of Matrix A:" << endl;
	// entering values of matrix A
	matrixA.resize(rowA, colA);
	cin >> matrixA;

	cout << "Please enter dimensions of Matrix B:" << endl;
	cin >> rowB >> colB;
	cout << "Please enter values of Matrix B:" << endl;
	// entering values of matrix B
	matrixB.resize(rowB, colB);
	cin >> matrixB;

	long long *product = new long long[colA];
	double *product2 = new double[colA];

	while (true)
	{
		cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: // sum
			// sum operation
			sumMatrix = matrixA + matrixB;
			// cout result of sum
			cout << sumMatrix;
			break;

		case 2: // subtract
			// subtract operation
			subMatrix = matrixA - matrixB;
			// cout result of subtract
			cout << subMatrix;
			break;

		case 3: // multiplication
			// multiplication operation
			multiplicationMatrix = matrixA * matrixB;
			// cout result of multiplication
			cout << multiplicationMatrix;
			break;

		case 4: // INVEEEEEERSE
			// it's a must that matrix B is a square matrix to get inverse of B and for multiplication no.columns of A equals no.rows of B
			if (colA != rowB or rowB != colB or matrixB.getDeterminant() == 0)
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
			{
				// division by 1x1 matrix
				if (rowB == 1)
				{
					for (int i = 0; i < rowA; i++)
					{
						for (int j = 0; j < colA; j++)
							cout << matrixA(i, j) / matrixB(0, 0) << " ";
						cout << endl;
					}
				}
				// division by 2x2 or more matrix
				else
				{
					divisionMatrix = matrixA * matrixB.getInverse<>();
					cout << divisionMatrix;
				}
			}
			break;

		case 5: // DETERMINANTS
			if (rowA != colA) // it's a must that a matrix must be a square matrix to get it's determinant which means the rows equals the columns
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
				cout << matrixA.getDeterminant() << endl; // getting the result of a determinant and a new line
			break;

		case 6: // DETERMINANTS
			if (rowB != colB) // it's a must that a matrix must be a square matrix to get it's determinant which means the rows equals the columns
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
				cout << matrixB.getDeterminant() << endl; // getting the result of a determinant and a new line
			break;

		case 7: // program break
			cout << "Thank You!" << endl; // nothing to explain here lol
			return 0;
		}
	}
}