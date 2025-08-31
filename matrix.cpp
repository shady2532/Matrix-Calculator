#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class Matrix
{
    vector<vector<T>> data;
    int rows, cols;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<T>(cols)) {}

    Matrix() : rows(0), cols(0) {}

    T &operator()(int i, int j)
    {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i][j];
    }

    const T &operator()(int i, int j) const
    {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw out_of_range("Matrix index out of bounds");
        return data[i][j];
    }

    int getRows() const { return rows; }

    int getCols() const { return cols; }

    void resize(int new_rows, int new_cols, T default_value = T())
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

