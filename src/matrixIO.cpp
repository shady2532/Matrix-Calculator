template<typename T>
std::istream &operator>>(std::istream &is, Matrix<T> &m)
{
    for (auto &elem : m.data)
        is >> elem;
    m.isDetCached = false; // invalidate cache on input
    return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m)
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