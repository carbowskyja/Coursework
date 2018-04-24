//
// Created by Anna on 4/10/2018.
//

#ifndef HOUSEHOLDER_MATRIX_H
#define HOUSEHOLDER_MATRIX_H

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

typedef std::vector<std::vector<double>> Matrix;

void print(const Matrix& matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            std::cout << std::to_string(matrix[i][j]) << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void transpose(Matrix& m)
{
    int n = m.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
            std::swap(m[i][j], m[j][i]);
    }
}

Matrix multiply(const Matrix& a, const Matrix& b)
{
    Matrix c;
    int n = a.size();

    for (int i = 0; i < n; ++i)
    {
        std::vector<double> s;

        for (int j = 0; j < n; ++j)
        {
            double sum = 0;

            for (int k = 0; k < n; ++k)
                sum += a[i][k] * b[k][j];

            s.push_back(sum);// complete row
        }

        c.push_back(s);
    }
    return c;
}

void multiply_by(std::vector<double>& v, double i)
{
    double n = v.size();
    for (int j = 0; j < n; ++j)
        v[j] *= i;
}

double scalar(const std::vector<double>& a, const std::vector<double>& b)
{
    int n = a.size();
    double res = 0;
    for (int i = 0; i < n; ++i)
        res += a[i] * b[i];

    return res;
}

double norm(const std::vector<double>& v)
{
    return sqrt(scalar(v, v));
}

bool is_diagonal(const Matrix& matrix)
{
    int n = matrix.size();

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if ((round(matrix[i][j]) * 100000) / 100000 != 0)
                return false;
        }
        std::cout << "\n";
    }
    return true;
}

void print_eigenvalues(const Matrix& matrix, std::string outfile)
{
    std::ofstream output;
    output.open(outfile);

    int n = matrix.size();
    for (int i = 0; i < n; ++i)
        output << matrix[i][i] << " ";
    output << "\n";

    output.close();
}

#endif //HOUSEHOLDER_MATRIX_H
