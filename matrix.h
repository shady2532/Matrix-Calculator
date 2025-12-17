#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class Matrix
{
    vector<vector<T>> data;
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

    T &operator()(size_t i, size_t j)
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i][j];
    }

    const T &operator()(size_t i, size_t j) const
    {
        if (i >= rows || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i][j];
    }

    size_t getRows() const { return rows; }

    size_t getCols() const { return cols; }

    void resize(size_t new_rows, size_t new_cols, T default_value = T())
    {
        rows = new_rows;
        cols = new_cols;
        data = vector<vector<T>>(new_rows, vector<T>(new_cols, default_value));
    }

    void fill()
    {
        for (auto &row : data)
            for (auto &elem : row)
                cin >> elem;
    }

    void print() const
    {
        for (const auto &row : data)
        {
            for (const auto &elem : row)
                cout << elem << " ";
            cout << endl;
        }
    }
};
