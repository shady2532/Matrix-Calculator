#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <optional>
#include <memory>
#include <iomanip>
template <typename T>
class Matrix
{
    std::vector<T> data;
    size_t rows, cols;

    // cache for determinant calculation
    mutable bool isDetCached = false;
    mutable typename std::conditional<std::is_floating_point<T>::value, T, double>::type cachedDetValue;

    // cache for inverse calculation
    mutable std::optional<std::unique_ptr<Matrix<typename std::conditional<std::is_floating_point<T>::value, T, double>::type>>> cachedInverse;

    // determinant function using gaussian elimination
    auto determinant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type;

    // inverse Calculation
    template <typename U>
    Matrix<U> inverse() const;

public:
    // Matrix Core Methods
    Matrix();
    Matrix(size_t r, size_t c);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix(std::initializer_list<std::initializer_list<T>> initList);
    Matrix(size_t r, size_t c, std::initializer_list<T> initList);
    ~Matrix() noexcept;
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;
    T &operator()(size_t i, size_t j);
    const T &operator()(size_t i, size_t j) const;
    void resize(size_t new_rows, size_t new_cols, T default_value = T());

    // getters
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // determinant
    auto getDeterminant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type;
    void invalidateDeterminantCache();

    // inverse
    template <typename U = double>
    Matrix<U> getInverse() const;
    Matrix<T> &invert();
    void invalidateInverseCache();

    // operator overloads
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &a, const Matrix<U> &b);
    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &a, const Matrix<U> &b);
    template <typename U>
    friend Matrix<U> operator*(const Matrix<U> &a, const Matrix<U> &b);
    template <typename U, typename V>
    friend Matrix<decltype(U() * V())> operator*(const Matrix<U> &a, const Matrix<V> &b);
    // stream operators
    template <typename U>
    friend std::istream &operator>>(std::istream &is, Matrix<U> &m);
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);
};

#include "Determinant.cpp"
#include "MatrixCore.cpp"
#include "MatrixIO.cpp"
#include "MatrixOperators.cpp"
#include "Inverse.cpp"