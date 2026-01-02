#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

double determinant(vector<vector<double>> s)
{
    double det = 1;
    size_t n = s.size();
    for (size_t i = 0; i < n; i++)
    {
        size_t pivotRow = i;
        // finding the pivot row
        for (size_t j = i + 1; j < n; j++)
        {
            if (abs(s[j][i]) > abs(s[i][i]))
                pivotRow = j;
        }
        // swapping the rows if needed
        if (pivotRow != i)
        {
            swap(s[i], s[pivotRow]);
            det = -det;
        }
        // if we found that s[i][i] equals zero we return a zero determinant
        if (abs(s[i][i]) < 1e-10)
            return 0.0;
        // elimination process
        for (size_t j = i + 1; j < n; j++)
        {
            double factor = s[j][i] / s[i][i];
            for (size_t x = i; x < n; x++)
                s[j][x] -= factor * s[i][x];
        }
        det *= s[i][i]; // then we take s[i][i] and multiply it to our value stored in det
    }
    if (det == -0) // some glitches :"(
        det = 0;
    return (long long)round(det); // returning the value of det after rounding it and casting it into (long long)
}

int main()
{
    std::vector<std::vector<double>> matrix = {
        {1}};

    double det = determinant(matrix);
    cout << std::fixed;
    cout << det << "\n"; // Expected output: 0

    return 0;
}