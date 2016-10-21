#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"


Matrix zeros(unsigned int row, unsigned int col)
{
    Matrix mat;

    mat.array = (double**)malloc(sizeof(double*)*row);
    if(mat.array == NULL)
        exit(202020);
    for(unsigned int i = 0; i < row; i++)
    {
        mat.array[i] = (double*)calloc(sizeof(double), col);
        if(mat.array[i] == NULL)
            exit(202020);
    }
    mat.shape[0] = row;
    mat.shape[1] = col;
    return mat;
}


Matrix eye(unsigned int n)
{   
    Matrix mat = zeros(n, n);

    for(unsigned int i = 0; i < n; i++)
        for(unsigned int j = 0; j < n; j++)
            if(i == j)
                mat.array[i][j] = 1;
    return mat;
}


Matrix random(unsigned int row, unsigned int col)
{
    Matrix mat = zeros(row, col);

    srand(time(NULL));
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        for(unsigned int j = 0; j < mat.shape[1]; j++)
            mat.array[i][j] = (double)rand()/RAND_MAX;
    return mat;
}


void mprint(Matrix mat)
{   
    for(unsigned int i = 0; i < mat.shape[0]; i++)
    {
        printf("[");
        for(unsigned int j = 0; j < mat.shape[1]; j++)
        {
            printf("%lf ", mat.array[i][j]);
            if(j + 1 == mat.shape[1])
                printf("\b]\n");
        }
    }
    printf("\n");
}


Matrix madd(Matrix a, Matrix b)
{
    if(a.shape[0] != b.shape[0] || a.shape[1] != b.shape[1])
    {
        printf("cannot add two given matrixes.");
        exit(303030);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < a.shape[1]; j++)
            c.array[i][j] = a.array[i][j] + b.array[i][j];
    return c;
}


Matrix msub(Matrix a, Matrix b)
{
    if(a.shape[0] != b.shape[0] || a.shape[1] != b.shape[1])
    {
        printf("cannot sub two given matrixes.");
        exit(303030);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < a.shape[1]; j++)
            c.array[i][j] = a.array[i][j] - b.array[i][j];
    return c;
}

double _mul(double* a, double* b, unsigned int length)
{
    double ret = 0;

    for(unsigned int i = 0; i < length; i++)
        ret += a[i]*b[i];
    return ret;
}

Matrix mmul(Matrix a, Matrix b)
{
    if(a.shape[1] != b.shape[0])
    {
        printf("cannot mul two given matrixes.");
        exit(303030);
    }

    Matrix c = zeros(a.shape[0], b.shape[1]);
    Matrix _b = transpose(b);
    
    for(unsigned int i = 0; i < a.shape[0]; i++)
        for(unsigned int j = 0; j < _b.shape[0]; j++)
            c.array[i][j] = _mul(a.array[i], _b.array[j], a.shape[1]);
    return c;
}


Matrix nmul(Matrix mat, double k)
{
    Matrix ret = zeros(mat.shape[0], mat.shape[1]);
    for(unsigned int i = 0; i < mat.shape[0]; i++)
        for(unsigned int j = 0; j < mat.shape[1]; j++)
            ret.array[i][j] = mat.array[i][j]*k;
    return ret;
}


Matrix transpose(Matrix mat)
{
    Matrix ret = zeros(mat.shape[1], mat.shape[0]);

    for(unsigned int j = 0; j < mat.shape[1]; j++)
        for(unsigned int i = 0; i < mat.shape[0]; i++)
            ret.array[j][i] = mat.array[i][j];
    return ret;
}
