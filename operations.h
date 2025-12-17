#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "matrix.h"
using namespace std;

template <typename T>
class command
{
public:
	virtual void execute() = 0;
	virtual ~command() {}
};

template <typename T>
class commandAdd : public command<T>
{
	Matrix<T> A;
	Matrix<T> B;
	Matrix<T> result;

public:
	commandAdd(Matrix<T> &a, Matrix<T> &b, Matrix<T> &res) : A(a), B(b), result(res) {}

	void execute() override
		result = A + B;
};

template <typename T>
class commandSubtract : public command<T>
{
	Matrix<T> A;
	Matrix<T> B;
	Matrix<T> result;

public:
	void subtractCommand(Matrix<T> &a, Matrix<T> &b, Matrix<T> &res) : A(a), B(b), result(res) {}

	void execute() override
	{
		result = A - B;
	}
};

template <typename T>
class determinant : public command<T>
{
	Matrix<T> A;
	Matrix<T> result;

public:
	void determinantCommand(Matrix<T> &a, Matrix<T> &res) : A(a), result(res) {}

	void execute() override
	{
		result = A.determinant();
	}
};

//	determinant using gaussian elemenation rule
/*
	tried to use the common method of calculating determinants but didn't work as I used vectors,
	that method was the recursion method which got time limited for matrices bigger than 8x8
	so I started thinking of one more way to solve it using the matrices with less recursion or with no recursion at all :)
*/
long long determinant(vector<vector<double>> &s, int n)
{
	double det = 1;
	for (int i = 0; i < n - 1; i++)
	{
		double sba7oo;
		int index = i;					 // abs(-2) = 2
		double mxvalueee = abs(s[i][i]); // we assign mxvalueee with the first value of the matrix till it finds bigger one
		for (int j = i + 1; j < n; j++)	 // then we start comparing it with other values of the same column
		{
			sba7oo = abs(s[j][i]);	// values of elements of same column named sba7oo
			if (sba7oo > mxvalueee) // then we compare which is bigger
			{						// if our mxvalueee is bigger than sba7oo we continue
				mxvalueee = sba7oo; // else we assign the value of sba7oo to mxvalueee
				index = j;			// as well as the index of the the biggest number
			}
		}
		if (index != i) // here if we notice a change in the first row and index
		{
			for (int g = 0; g < n; g++)
			{
				swap(s[i][g], s[index][g]); // we start swapping the elements of the rows
			} // then we take a -1 as a common factor of our determinant
			det = -det; //(rules for solving the determinant using gaussian elemination)
		}
		double elly_hytderb = s[i][i]; // first s[i][i] we took abs of it here we won't, coz we were just comparing values not signs
		if (abs(elly_hytderb) <= 0)
			return 0.0; // if we found that s[i][i] equals zero we return a zero
		for (int j = i + 1; j < n; j++)
		{ // now next one is kinda tricky. we get another variable (m4_3aref) and get the division of s[j][i]/s[i][i]
			double m4_3aref = s[j][i] / elly_hytderb;
			for (int x = i; x < n; x++)
			{ // then we multiply it with the elements of the (i)th row then subtract it from the (j)th row
				s[j][x] -= m4_3aref * s[i][x];
			}
		} // we reply then step till we get zeros in the first column except for the in the first row
		det *= elly_hytderb; // then we take s[i][i] and multiply it to our value stored in det
	}
	det *= s[n - 1][n - 1]; // this one for the last element as we won't do the operation above on it
	if (det == -0)			// some glitches :"(
		det = 0;
	return (long long)round(det); // returning the value of det after rounding it and casting it into (long long)
}