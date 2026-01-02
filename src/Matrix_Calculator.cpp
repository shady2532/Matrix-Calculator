#include <iostream>
#include <cmath>
#include <vector>
#include "command.h"
#include "matrix.h"
using namespace std;

int main()
{
	// matrices are classes
	Matrix<long long> matrixA; // matrix A
	Matrix<double> matdouble1; // matrix A in a form of double
	Matrix<long long> matrixB; // matrix B
	Matrix<double> matdouble2; // matrix B in a form of double

	Matrix<long long> sumMatrix; // this was for storing the sum

	Matrix<long long> subMatrix; // this one for the subtraction

	Matrix<long long> multiplicationMatrix; // this for the mutilplication of (A & B)

	Matrix<long long> mat_m2lob;   // wad7a lw7dha aho
	Matrix<double> inversemat;	   // wad7a aktr mn elly 2blha
	Matrix<double> divisionMatrix; // this for the multiplication of (A & inverse of B)

	// for assigning values in a matrix I used 2D vectors
	// first pushing back values in a 1D vector
	// then pushing back the 1D vector in a 2D vector

	// some variables that I don't know how it got so many like this
	long long choice;			// variable to choose operation
	long long sum = 0;			// summation
	long long sub = 0;			// subtraction
	long long productSum = 0;	// multiplication for (A & B)
	long long determinant1 = 0; // determinant of matrix 1
	long long determinant2 = 0; // determinant of matrix 2
	long long r1, c1, r2, c2;	// rows and columns for our 2 matrices
	long long sign;				// this one is for the sign of the inverse matrix B
	double productSum2 = 0;		// multiplication for (A & inverse of B)

	// those honestly I named them with nothing in mind
	// I even forgot what they are for xD
	// but i know one thing tho...
	double value;	  // this is double
	long long valuee; // this is long long
	double asd;		  // this is asd
	long long lol;	  // this is lol
	// kidding i just used them to push back the values in the matrices as it was the only way to add elements to them
	// i just got lost when i was naming them

	cout << "Please enter dimensions of Matrix A:" << endl;
	cin >> r1 >> c1;
	cout << "Please enter values of Matrix A:" << endl;
	// entering values of matrix A
	matrixA.resize(r1, c1);
	cin >> matrixA;

	cout << "Please enter dimensions of Matrix B:" << endl;
	cin >> r2 >> c2;
	cout << "Please enter values of Matrix B:" << endl;
	// entering values of matrix B
	matrixB.resize(r2, c2);
	cin >> matrixB;

	long long *product = new long long[c1];
	double *product2 = new double[c1];

	// matrix 1 doubled
	for (int i = 0; i < r1; i++)
	{
		vector<double> ff;
		for (int j = 0; j < c1; j++)
		{
			value = matrixA[i][j];
			ff.push_back(value); // this loop is for pushing elements in a 1D vector
		}
		matdouble1.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
	}
	// matrix 2 doubled
	for (int i = 0; i < r2; i++)
	{
		vector<double> ff;
		for (int j = 0; j < c2; j++)
		{
			value = matrixB[i][j];
			ff.push_back(value); // this loop is for pushing elements in a 1D vector
		}
		matdouble2.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
	}

	while (true)
	{
		cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):" << endl;
		cin >> choice;

		// program break
		if (choice == 7)
		{
			cout << "Thank You!" << endl; // nothing to explain here lol
			break;
		}
		// sum
		if (choice == 1)
		{
			// sum operation
			sumMatrix = matrixA + matrixB;
			// cout result of sum
			cout << sumMatrix;
		}
		// subtract
		if (choice == 2)
		{
			// subtract operation
			subMatrix = matrixA - matrixB;
			// cout result of subtract
			cout << subMatrix;
		}
		// multiplication
		if (choice == 3)
		{
			// multiplication operation
			multiplicationMatrix = matrixA * matrixB;
			// cout result of multiplication
			cout << multiplicationMatrix;
		}
		// DETERMINANTS
		if (choice == 5)
		{
			if (r1 != c1) // it's a must that a matrix must be a square matrix to get it's determinant which means the rows equals the columns
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
				cout << matrixA.getDeterminant() << endl; // getting the result of a determinant and a new line
		}
		if (choice == 6)
		{
			if (r2 != c2) // it's a must that a matrix must be a square matrix to get it's determinant which means the rows equals the columns
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
				cout << matrixB.getDeterminant() << endl; // getting the result of a determinant and a new line
		}
		// INVEEEEEERSE
		if (choice == 4)
		{
			// it's a must that matrix B is a square matrix to get inverse of B and for multiplication no.columns of A equals no.rows of B
			if (c1 != r2 or r2 != c2 or matrixB.getDeterminant() == 0)
				cout << "The operation you chose is invalid for the given matrices." << endl;
			else
			{
				// division by 1x1 matrix
				if (r2 == 1)
				{
					for (int i = 0; i < r1; i++)
					{
						for (int j = 0; j < c1; j++)
							cout << matrixA(i, j) / matrixB(0, 0) << " ";
						cout << endl;
					}
				}
				// division by 2x2 matrix
				else if (r2 == 2)
				{
					swap(matrixB(0, 0), matrixB(1, 1)); // here we swap s[0][0] with s[1][1] (special case)		// 1 2      4 -2
					for (int i = 0; i < r2; i++)		// 3 4      -3 1
					{
						vector<long long> ff;
						for (int j = 0; j < r2; j++)
						{
							sign = i + j;	   // sign variable
							if (sign % 2 == 0) // then we check the signs of the matrix to get the adjoint
								value = matrixB(i, j);
							else
								value = -matrixB(i, j);
							ff.push_back(value); // this loop is for pushing elements in a 1D vector
						}
						mat_m2lob.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
					}
					double inversedet = (double)1 / matrixB.getDeterminant(); // here is a double called inversedet which gets 1/determinant of B
					for (long long i = 0; i < r2; i++)
					{
						vector<double> ff;
						for (int j = 0; j < r2; j++)
						{
							asd = inversedet * mat_m2lob(i, j); // here we divide the matrix above by the determinant of the real B matrix
							ff.push_back(asd);					// this loop is for pushing elements in a 1D vector
						}
						inversemat.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
					}
				}
				// division by matrix YxZ
				else
				{
					// adjoint of matrix B (no signs)
					vector<vector<long long>> adj_B;
					for (long long i = 0; i < r2; i++) // this loop iterates on the rows of matrix B
					{
						vector<long long> y;
						for (long long j = 0; j < r2; j++) // this one iterates on the elements in every column of matrix B
						{
							vector<vector<long long>> z;
							for (long long subi = 0; subi < r2; subi++) // this loop for assigning rows in the 2D new submatrix
							{
								if (subi == i) // this checks if we are on the same row as the main matrix or not
									continue;  // if yes continue
								vector<long long> ff;
								for (long long subj = 0; subj < r2; subj++) // this loop for assigning values of rows' elements of the submatrix
								{
									if (subj == j) // this checks if we are on the same column as the main matrix or not
										continue;  // if yes continue
									valuee = matrixB[subi][subj];
									ff.push_back(valuee); // this loop is for pushing elements in a 1D vector of the new submatrix
								}
								z.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector of the new submatrix
							}
							vector<vector<double>> zz;
							for (int subi = 0; subi < r2 - 1; subi++) // these two loops take elements from the normal submatrix above
							{										  // and assigning the values to a new submatrix of type: double
								vector<double> ff;					  // so that we can work with it
								for (int subj = 0; subj < r2 - 1; subj++)
								{
									valuee = z[subi][subj];
									ff.push_back(valuee); // this loop is for pushing elements in a 1D vector
								}
								zz.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
							}
							lol = determinant(zz, r2 - 1); // we get the determinant of submatrix
							y.push_back(lol);			   // and push it back in a 1D vector of a new matrix
						}
						adj_B.push_back(y); // pushing back the 1D vector into a 2D vector
					}
					// adjoint of matrix B (with signs)
					for (long long i = 0; i < r2; i++)
					{
						vector<long long> ff;
						for (long long j = 0; j < r2; j++)
						{
							sign = i + j;	   // sign variable
							if (sign % 2 == 0) // then we check the signs of the matrix to get the adjoint
								value = adj_B[j][i];
							else
								value = -adj_B[j][i];
							ff.push_back(value); // this loop is for pushing elements in a 1D vector
						}
						mat_m2lob.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
					}
					double inversedet = (double)1 / determinant(matdouble2, r2); // here is a double called inversedet which gets 1/determinant of B
					// inverse of B=1/determinant * adjoint
					for (long long i = 0; i < r2; i++)
					{
						vector<double> ff;
						for (long long j = 0; j < r2; j++)
						{
							asd = inversedet * mat_m2lob[i][j]; // here we divide the matrix above by the determinant of the real B matrix
							ff.push_back(asd);					// this loop is for pushing elements in a 1D vector
						}
						inversemat.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
					}
					// testing if the inverse matrix was correct or not
					// cout the inverse matrix called ((inversemat))
					/*for (long long i = 0; i < r2; i++)
					{
						for (long long j = 0; j < c2; j++)
						{
							cout << inversemat[i][j] << " ";
						}
						cout << endl;
					}*/
				}
				// now multiplication
				for (long long i = 0; i < r1; i++)
				{
					vector<double> ff;
					for (long long j = 0; j < c2; j++)
					{
						for (long long k = 0; k < c1; k++)
						{													// after some experiements found that...
							product2[k] = matrixA[i][k] * inversemat[k][j]; // we multiply elements of a row in A with column in B
							productSum2 += product2[k];						// then adding them
						}
						ff.push_back(round(productSum2)); // this loop is for pushing elements in a 1D vector
						productSum2 = 0;				  // resetting productSum to zero to calculate for the next iterate
					}
					divisionMatrix.push_back(ff); // this loop is for pushing a 1D vector into a 2D vector
				}
				// cout result of multiplication
				for (long long i = 0; i < r1; i++)
				{
					for (long long j = 0; j < c2; j++)
					{
						cout << (long long)divisionMatrix[i][j] << " "; // nothing to explain just a space and a new line
					}
					cout << endl;
				}
			}
		}
	}
}