//
// Created by Anna on 4/10/2018.
//

#ifndef HOUSEHOLDER_HOUSEHOLDER_H
#define HOUSEHOLDER_HOUSEHOLDER_H

#include "matrix.h"

typedef std::vector<std::vector<double>> Matrix;

Matrix generateQ(const std::vector<double>& v, double y)
{
    Matrix q;
    int n = v.size();

    for (int i = 0; i < n; ++i)
    {
        std::vector<double> s;
        for (int j = 0; j < n; ++j)
            s.push_back(0);

        q.push_back(s);
    }

    for (int i = 0; i < n; ++i)
        q[i][i] = 1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            q[i][j] -= v[i] * v[j] / y;
    }

    return q;
}

void calculate_reflection(const std::vector<double>& column, int i, double& y, std::vector<double>& v)
{
    int n = column.size();
    std::vector<double> s;
    y = 0.5;

    for (int j = 0; j < n; ++j)
        v[j] = 0;

    v[i] = 1;

    for (int k = i; k < n; ++k)
        s.push_back(column[k]);

    if (scalar(s, s) != 0)
    {
        double c = 1 / norm(s);
        multiply_by(s, c);
        for (int j = i + 1; j < n; ++j)
            v[j] = s[j - i];

        if (s[0] != 0)
            v[i] = (s[0] / fabs(s[0])) * (1 + fabs(s[0]));

        y = fabs(v[i]);
    }
}

// returns Q, X -> R
Matrix household(Matrix& x)
{
    int n = x.size();
    double y;
    std::vector<double> v(n);

    // Q = E
    Matrix q;
    for (int i = 0; i < n; ++i)
    {
        std::vector<double> s;
        for (int j = 0; j < n; ++j)
            s.push_back(0);

        q.push_back(s);
    }

    for (int l = 0; l < n; ++l)
        q[l][l] = 1;

    // calculate each step
    for (int i = 0; i < n - 1; ++i)
    {
        calculate_reflection(x[i], i, y, v);
        for (int j = i; j < n; ++j)
        {
            std::vector<double> mod = v;
            multiply_by(mod, scalar(x[j], v) / y);
            for (int k = 0; k < n; ++k)
            {
                x[j][k] -= mod[k];
            }
        }
        // calculate Q
        Matrix qi = generateQ(v, y);
        q = multiply(q, qi);
    }
    return q;
}


#endif //HOUSEHOLDER_HOUSEHOLDER_H
