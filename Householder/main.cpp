#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "householder.h"

using namespace std;

vector<vector<double>> generate_matrix(string infile)
{
    vector<vector<double>> matrix;
    ifstream input;
    input.open(infile);

    string line;
    while (getline(input, line))
    {
        vector<double> row;
        istringstream s(line);
        double n;
        while (s >> n)
            row.push_back(n);

        matrix.push_back(row);
    }

    input.close();
    return matrix;
}

int main()
{
    string efile = "F:\\data_NeurolingLab\\norm+patients_32&32\\4D and data\\eigenvalues_custom_", mfile = "F:\\data_NeurolingLab\\norm+patients_32&32\\4D and data\\matrix_";
    for (int i = 1; i < 65; ++i)
    {
        vector<vector<double>> matrix = generate_matrix(mfile + to_string(i) + ".txt");
//    matrix.push_back(vector<double>({1, -1, 0}));
//    matrix.push_back(vector<double>({-1, 0, 1}));
//    matrix.push_back(vector<double>({0, 1, 1}));
        // this isn't working so try to deal with that

        while (!is_diagonal(matrix))
        {
            //print(matrix);
            // to make rows columns because it's easier to work with rows
            transpose(matrix);
            vector<vector<double>> q = household(matrix);
            transpose(matrix);

            matrix = multiply(matrix, q);
        }

        print_eigenvalues(matrix, efile + to_string(i) + ".txt");
    }


    return 0;
}