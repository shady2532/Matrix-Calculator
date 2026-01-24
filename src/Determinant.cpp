/*
    determinant using gaussian elimination rule:
    tried to use the common method of calculating determinants but didn't work as I used vectors,
    that method was the recursion method which got time limited for matrices bigger than 8x8
    so I started thinking of one more way to solve it using the matrices with less recursion or with no recursion at all :)
*/
template <typename T>
auto Matrix<T>::determinant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type
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
            if (std::abs(temp(j, i)) > std::abs(temp(pivotRow, i)))
                pivotRow = j;
        }

        // swapping the rows if needed
        if (pivotRow != i)
        {
            for (size_t k = 0; k < cols; k++)
                std::swap(temp(i, k), temp(pivotRow, k));
            det = -det;
        }

        // if we found that s[i][i] equals zero we return a zero determinant
        if (std::abs(temp(i, i)) < std::numeric_limits<ReturnType>::epsilon() * std::max(static_cast<ReturnType>(1), std::abs(det)))
            return 0.0;

        // elimination process
        for (size_t j = i + 1; j < rows; j++)
        {
            ReturnType factor = temp(j, i) / temp(i, i);
            for (size_t k = i; k < cols; k++)
                temp(j, k) -= factor * temp(i, k);
        }
        det *= temp(i, i);
    }
// some glitches :"(
    det = (det == -0) ? 0 : det;
    
    if (std::abs(det) < 0.001) {  // ✓ Explicitly use std::abs
        std::cout << std::scientific << std::setprecision(4);
    } else {
        std::cout << std::fixed << std::setprecision(4);
    }

    return det;                 // returning the value of det
}
// cached determinant retrieval
template <typename T>
auto Matrix<T>::getDeterminant() const -> typename std::conditional<std::is_floating_point<T>::value, T, double>::type
{
    if (!isDetCached)
    {
        cachedDetValue = determinant();
        isDetCached = true;
    }
    return cachedDetValue;
}
// invalidate cached determinant
template <typename T>
void Matrix<T>::invalidateDeterminantCache()
{
    isDetCached = false;
}