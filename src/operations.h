#pragma once
#include <iostream>
#include "command.h"

// Binary Operations
template <typename T>
class AddCommand : public BinaryCommand<T>
{
public:
    using BinaryCommand<T>::BinaryCommand;
    void execute() override
    {
        this->result = this->A + this->B;
    }
};

template <typename T>
class SubtractCommand : public BinaryCommand<T>
{
public:
    using BinaryCommand<T>::BinaryCommand;
    void execute() override
    {
        this->result = this->A - this->B;
    }
};

template <typename T>
class MultiplyCommand : public BinaryCommand<T>
{
public:
    using BinaryCommand<T>::BinaryCommand;
    void execute() override
    {
        this->result = this->A * this->B;
    }
};

// Scalar Operations
template <typename T>
class DeterminantCommand : public ScalarCommand<T>
{
public:
    using ScalarCommand<T>::ScalarCommand;
    void execute() override
    {
        this->result = this->A.determinant();
    }
};