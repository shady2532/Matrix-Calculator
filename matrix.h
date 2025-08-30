#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void resizeMatrix(vector<vector<long long>> &matrix, long long rows, long long cols)
{
    /*matrix.resize(rows);
    for (auto &row : matrix)
        row.resize(cols);*/
    matrix = vector<vector<long long>>(rows, vector<long long>(cols, 0));
}

void fillMatrix(vector<vector<long long>> &matrix)
{
    for (auto &row : matrix)
        for (auto &elem : row)
            cin >> elem;
}