template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.rows != b.rows || a.cols != b.cols)
        throw std::invalid_argument("Incompatible matrix dimensions");
    Matrix<T> result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows * a.cols; i++)
        result.data[i] = a.data[i] + b.data[i];
    return result;
}

template <typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.rows != b.rows || a.cols != b.cols)
        throw std::invalid_argument("Incompatible matrix dimensions");
    Matrix<T> result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows * a.cols; i++)
        result.data[i] = a.data[i] - b.data[i];
    return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.cols != b.rows)
        throw std::invalid_argument("Incompatible matrix dimensions");
    Matrix<T> result(a.rows, b.cols);
    for (size_t i = 0; i < a.rows; i++)
        for (size_t j = 0; j < b.cols; j++)
            for (size_t k = 0; k < a.cols; k++)
                result(i, j) += a(i, k) * b(k, j);
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Incompatible matrix dimensions");
    for (size_t i = 0; i < rows * cols; i++)
        data[i] += other.data[i];
    isDetCached = false; // invalidate cache on modification
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
{
    if (rows != other.rows || cols != other.cols)
        throw invalid_argument("Incompatible matrix dimensions");
    for (size_t i = 0; i < rows * cols; i++)
        data[i] -= other.data[i];
    isDetCached = false; // invalidate cache on modification
    return *this;
}

template <typename T, typename U>
Matrix<decltype(T() * U())> operator*(const Matrix<T> &a, const Matrix<U> &b)
{
    using ResultType = decltype(T() * U());
    Matrix<ResultType> result(a.getRows(), b.getCols());

    for (size_t i = 0; i < a.getRows(); i++)
    {
        for (size_t j = 0; j < b.getCols(); j++)
        {
            ResultType sum = ResultType();
            for (size_t k = 0; k < a.getCols(); k++)
            {
                sum += static_cast<ResultType>(a(i, k)) * static_cast<ResultType>(b(k, j));
            }
            result(i, j) = sum;
            if (std::abs(result(i, j)) < 1e-10)
                result(i, j) = 0;
        }
    }

    return result;
}
