template <typename T>
template <typename U>
Matrix<U> Matrix<T>::getInverse() const
{
    return this->inverse<U>();
}

template <typename T>
template <typename U>
Matrix<U> Matrix<T>::inverse() const
{
    using ReturnType = typename std::conditional<std::is_floating_point<T>::value, T, U>::type;

    // check if inverse is already cached
    if (cachedInverse && *cachedInverse)
        return *static_cast<Matrix<U>*>(cachedInverse.value().get());

    size_t n = rows;

    Matrix<U> temp(n, 2 * n);
    Matrix<U> result(n, n);

    // Augmenting the matrix with the identity matrix
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            temp(i, j) = (*this)(i, j);
        temp(i, i + n) = 1;
    }

    // Applying Gauss-Jordan elimination
    for (size_t i = 0; i < n; i++)
    {
        size_t pivotRow = i;

        // finding the pivot row
        for (size_t j = i + 1; j < n; j++)
            if (std::abs(temp(j, i)) > std::abs(temp(pivotRow, i)))
                pivotRow = j;

        // swapping the rows if needed
        if (pivotRow != i)
            for (size_t k = 0; k < 2 * n; k++)
                std::swap(temp(i, k), temp(pivotRow, k));

        // normalize the pivot row
        U pivotValue = temp(i, i);
        for (size_t j = 0; j < 2 * n; j++)
            temp(i, j) /= pivotValue;

        // elimination process
        for (size_t j = 0; j < n; j++)
        {
            if (j != i)
            {
                U factor = temp(j, i) / temp(i, i);
                for (size_t k = i; k < 2 * n; k++)
                    temp(j, k) -= factor * temp(i, k);
            }
        }
    }
    // extracting Resultant Inverse Matrix
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            result(i, j) = temp(i, j + n);

    cachedInverse = std::make_unique<Matrix<U>>(result);
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::invert()
{
    *this = this->inverse<T>();
    invalidateDeterminantCache();
    invalidateInverseCache();
    return *this;
}

template <typename T>
void Matrix<T>::invalidateInverseCache()
{
    cachedInverse.reset();
}
