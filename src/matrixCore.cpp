#include "matrix.h"
using namespace std;

// Default constructor
template <typename T>
Matrix<T>::Matrix() : rows(0),
                      cols(0),
                      isDetCached(false),
                      cachedDetValue(0) {}
// Parameterized constructor
template <typename T>
Matrix<T>::Matrix(size_t r, size_t c) : rows(r),
                                        cols(c),
                                        data(r * c),
                                        isDetCached(false),
                                        cachedDetValue(0) {}
// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix &other) : rows(other.rows),
                                         cols(other.cols),
                                         data(other.data),
                                         isDetCached(other.isDetCached),
                                         cachedDetValue(other.cachedDetValue) {}
// Move constructor
template <typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept : rows(other.rows),
                                             cols(other.cols),
                                             data(std::move(other.data)),
                                             isDetCached(other.isDetCached),
                                             cachedDetValue(other.cachedDetValue)
{
    other.rows = 0;
    other.cols = 0;
    other.isDetCached = false;
}
// 2D Initializer list constructor
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> initList) : rows(initList.size()),
                                                                              cols(initList.size() > 0 ? initList.begin()->size() : 0),
                                                                              isDetCached(false)
{
    data.resize(rows * cols);
    size_t r = 0;
    for (const auto &rowList : initList)
    {
        size_t c = 0;
        for (const auto &value : rowList)
        {
            data[r * cols + c] = value;
            c++;
        }
        r++;
    }
}
template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, std::initializer_list<T> initList) : rows(r),
                                                                           cols(c),
                                                                           data(r * c),
                                                                           isDetCached(false)
{
    if (initList.size() != rows * cols)
        throw std::invalid_argument("Initializer list size must match rows * cols");
    std::copy(initList.begin(), initList.end(), data.begin());
}
// Destructor
template <typename T>
Matrix<T>::~Matrix() noexcept = default;
// Copy assignment
template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
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
// Move assignment
template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept
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
// Element access
template <typename T>
T &Matrix<T>::operator()(size_t i, size_t j) // m(1,2)
{
    if (i >= rows || j >= cols)
        throw out_of_range("Matrix index out of bounds");
    isDetCached = false; // invalidate cache on modification
    return data[i * cols + j];
}
// Const element access
template <typename T>
const T &Matrix<T>::operator()(size_t i, size_t j) const
{
    if (i >= rows || j >= cols)
        throw out_of_range("Matrix index out of bounds");
    return data[i * cols + j];
}
// Resize method
template <typename T>
void Matrix<T>::resize(size_t new_rows, size_t new_cols, T default_value)
{
    rows = new_rows;
    cols = new_cols;
    data = vector<T>(new_rows * new_cols, default_value);
    isDetCached = false; // invalidate cache on resize
}
