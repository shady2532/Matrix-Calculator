#pragma once
#include <iostream>
#include <vector>
#include <cmath>
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
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, vector<T>(c)) {}

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

    T &operator()(size_t i, size_t j)  //m(1,2)
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
};