#pragma once
#include "matrix.h"

template <typename T>
class Command
{
public:
	virtual void execute() = 0;
	virtual ~Command() = default;
};

template <typename T>
class BinaryCommand : public Command<T>
{
	const Matrix<T> &A;
	const Matrix<T> &B;
	Matrix<T> &result;

public:
	BinaryCommand(const Matrix<T> &a, const Matrix<T> &b, Matrix<T> &res) : A(a), B(b), result(res) {};
};

template <typename T>
class UnaryCommand : public Command<T>
{
	const Matrix<T> &A;
	Matrix<T> &result;

public:
	UnaryCommand(const Matrix<T> &a, Matrix<T> &res) : A(a), result(res) {};
};

template <typename T>
class ScalarCommand : public Command<T>
{
	const Matrix<T> &A;
	T &result;

public:
	ScalarCommand(const Matrix<T> &a, T &res) : A(a), result(res) {};
};
