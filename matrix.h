#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Matrix
{
    vector<T> data;
    size_t rows, cols;

public:
    // Default constructor
    Matrix() : rows(0), cols(0) {}

    // Parameterized constructor
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c) {}

    // Destructor
    ~Matrix() noexcept = default;

    // Copy constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), data(other.data) {}

    // Move constructor
    Matrix(Matrix &&other) noexcept : rows(other.rows), cols(other.cols), data(std::move(other.data))
    {
        other.rows = 0;
        other.cols = 0;
    }

    T &operator()(size_t i, size_t j) // m(1,2)
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i * cols + j];
    }

    const T &operator()(size_t i, size_t j) const
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i * cols + j];
    }

    size_t getRows() const { return rows; }

    size_t getCols() const { return cols; }

    void resize(size_t new_rows, size_t new_cols, T default_value = T())
    {
        rows = new_rows;
        cols = new_cols;
        data = vector<T>(new_rows * new_cols, default_value);
    }

    friend istream &operator>>(istream &is, Matrix &m)
    {
        for (size_t i = 0; i < m.rows * m.cols; i++)
            is >> m.data[i];
        return is;
    }

    friend ostream &operator<<(ostream &os, const Matrix &m)
    {
        for (size_t i = 0; i < m.rows * m.cols; i++)
        {
            os << m.data[i];
            if ((i + 1) % m.cols == 0)
                os << endl;
            else
                os << " ";
        }
        return os;
    }

    /*void fill()
    {
        for (auto &elem : row)
            cin >> elem;
    }*/

    /*void print() const
    {
        for (size_t i = 0; i < rows * cols; i++)
        {
            cout << data[i];
            if ((i + 1) % cols == 0)
                cout << endl;
            else
                cout << " ";
        }
    }*/

    Matrix &operator+=(const Matrix &other)
    {
        if (cols != other.rows)
            throw invalid_argument("Incompatible matrix dimensions");
        for (size_t i = 0; i < rows * cols; i++)
            data[i] += other.data[i];
        return *this;
    }

    Matrix &operator-=(const Matrix &other)
    {
        if (cols != other.rows)
            throw invalid_argument("Incompatible matrix dimensions");
        for (size_t i = 0; i < rows * cols; i++)
            data[i] -= other.data[i];
        return *this;
    }

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }

    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this != &other)
        {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    Matrix operator+(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible matrix dimensions");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible matrix dimensions");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; i++)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (cols != other.rows)
            throw invalid_argument("Incompatible matrix dimensions");
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < other.cols; j++)
                for (size_t k = 0; k < cols; k++)
                    result(i, j) += data[i * cols + k] * other(k, j);
        return result;
    }

    //	determinant using gaussian elemenation rule
    /*
        tried to use the common method of calculating determinants but didn't work as I used vectors,
        that method was the recursion method which got time limited for matrices bigger than 8x8
        so I started thinking of one more way to solve it using the matrices with less recursion or with no recursion at all :)
    */
    T determinant(vector<vector<double>> &s, int n)
    {
        double det = 1;
        for (int i = 0; i < n - 1; i++)
        {
            double sba7oo;
            int index = i;                   // abs(-2) = 2
            double mxvalueee = abs(s[i][i]); // we assign mxvalueee with the first value of the matrix till it finds bigger one
            for (int j = i + 1; j < n; j++)  // then we start comparing it with other values of the same column
            {
                sba7oo = abs(s[j][i]);  // values of elements of same column named sba7oo
                if (sba7oo > mxvalueee) // then we compare which is bigger
                {                       // if our mxvalueee is bigger than sba7oo we continue
                    mxvalueee = sba7oo; // else we assign the value of sba7oo to mxvalueee
                    index = j;          // as well as the index of the the biggest number
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
        if (det == -0)          // some glitches :"(
            det = 0;
        return (T)round(det); // returning the value of det after rounding it and casting it into (long long)
    }
};