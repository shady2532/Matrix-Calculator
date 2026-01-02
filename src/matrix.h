#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Matrix
{
    vector<T> data;
    size_t rows, cols; // property / field

    // cache for determinant calculation
    mutable bool isDetCached = false;
    mutable typename std::conditional<std::is_floating_point<T>::value, T, double>::type cachedDetValue;

    //	determinant using gaussian elemenation rule
    /*
        tried to use the common method of calculating determinants but didn't work as I used vectors,
        that method was the recursion method which got time limited for matrices bigger than 8x8
        so I started thinking of one more way to solve it using the matrices with less recursion or with no recursion at all :)
    */
    auto determinant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    {
        using ReturnType = typename std::conditional<std::is_floating_point<T>::value, T, double>::type;

        Matrix<ReturnType> temp(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                temp(i, j) = static_cast<ReturnType>((*this)(i, j));

        ReturnType det = 1;

        for (size_t i = 0; i < rows; i++)
        {
            size_t pivotRow = i;

            // finding the pivot row
            for (size_t j = i + 1; j < rows; j++)
            {
                if (abs(temp(j, i)) > abs(temp(pivotRow, i)))
                    pivotRow = j;
            }

            // swapping the rows if needed
            if (pivotRow != i)
            {
                for (size_t k = 0; k < cols; k++)
                    swap(temp(i, k), temp(pivotRow, k));
                det = -det;
            }

            // if we found that s[i][i] equals zero we return a zero determinant
            if (abs(temp(i, i)) < std::numeric_limits<ReturnType>::epsilon() * 100)
                return 0.0;

            // elimination process
            for (size_t j = i + 1; j < rows; j++)
            {
                ReturnType factor = temp(j, i) / temp(i, i);
                for (size_t k = i; k < cols; k++)
                    temp(j, k) -= factor * temp(i, k);
            }
            det *= temp(i, i); // then we take s[i][i] and multiply it to our value stored in det
        }
        if (det == -0) // some glitches :"(
            det = 0;
        return det; // returning the value of det
    }

public:
    // Default constructor
    Matrix() : rows(0), cols(0), isDetCached(false), cachedDetValue(0) {}

    // Parameterized constructor
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c), isDetCached(false), cachedDetValue(0) {}

    // Destructor
    ~Matrix() noexcept = default;

    // Copy constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), data(other.data), isDetCached(other.isDetCached), cachedDetValue(other.cachedDetValue) {}

    // Move constructor
    Matrix(Matrix &&other) noexcept : rows(other.rows), cols(other.cols), data(std::move(other.data)), isDetCached(other.isDetCached), cachedDetValue(other.cachedDetValue)
    {
        other.rows = 0;
        other.cols = 0;
        other.isDetCached = false;
    }

    T &operator()(size_t i, size_t j) // m(1,2)
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        isDetCached = false; // invalidate cache on modification
        return data[i * cols + j];
    }

    const T &operator()(size_t i, size_t j) const
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i * cols + j];
    }

    size_t getRows() const { return rows; } // method / function

    size_t getCols() const { return cols; }

    void resize(size_t new_rows, size_t new_cols, T default_value = T())
    {
        rows = new_rows;
        cols = new_cols;
        data = vector<T>(new_rows * new_cols, default_value);
        isDetCached = false; // invalidate cache on resize
    }

    friend istream &operator>>(istream &is, Matrix &m)
    {
        for (size_t i = 0; i < m.rows * m.cols; i++)
            is >> m.data[i];
        m.isDetCached = false; // invalidate cache on input
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
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible matrix dimensions");
        for (size_t i = 0; i < rows * cols; i++)
            data[i] += other.data[i];
        isDetCached = false; // invalidate cache on modification
        return *this;
    }

    Matrix &operator-=(const Matrix &other)
    {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible matrix dimensions");
        for (size_t i = 0; i < rows * cols; i++)
            data[i] -= other.data[i];
        isDetCached = false; // invalidate cache on modification
        return *this;
    }

    // copy assignment: makes a copy of other to this
    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
            isDetCached = other.isDetCached;
            cachedDetValue = other.cachedDetValue;
        }
        return *this;
    }

    // move assignment: no copy is made, resources are moved from other to this
    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this != &other)
        {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
            isDetCached = other.isDetCached;
            cachedDetValue = other.cachedDetValue;
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

    // cached determinant retrieval
    auto getDeterminant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    {
        if (!isDetCached)
        {
            cachedDetValue = determinant();
            isDetCached = true;
        }
        return cachedDetValue;
    }

    // invalidate cached determinant
    void invalidateDeterminantCache()
    {
        isDetCached = false;
    }
};