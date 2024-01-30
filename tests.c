#include "tests.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef int matrix[MATRIX_ROWS][MATRIX_COLS];

static void _ijk(const matrix a, const matrix b, matrix result)
{
    int i, j, k, sum;
    for (i = 0; i < MATRIX_ROWS; i++)
    {
        for (j = 0; j < MATRIX_COLS; j++)
        {
            sum = 0;
            for (k = 0; k < MATRIX_COLS; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
}

static void _kij(const matrix a, const matrix b, matrix result)
{
    int i, j, k, r;
    for (k = 0; k < MATRIX_COLS; k++)
    {
        for (i = 0; i < MATRIX_ROWS; i++)
        {
            r = a[i][k];
            for (j = 0; j < MATRIX_COLS; j++)
            {
                result[i][j] += r * b[k][j];
            }
        }
    }
}

static void _jki(const matrix a, const matrix b, matrix result)
{
    int i, j, k, r;
    for (j = 0; j < MATRIX_ROWS; j++)
    {
        for (k = 0; k < MATRIX_COLS; k++)
        {
            r = b[k][j];
            for (i = 0; i < MATRIX_COLS; i++)
            {
                result[i][j] += a[i][k] * r;
            }
        }
    }
}

typedef void (*runtime_func_t)(const matrix b, const matrix a, matrix result);

static void _measure_runtime(runtime_func_t func, const matrix a, const matrix b, matrix result, const char *tag)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    func(a, b, result);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("%s: %f seconds\n", tag, time_taken);
}

static void _fill_matrix_rand(matrix m)
{
    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        for (int j = 0; j < MATRIX_COLS; j++)
        {
            m[i][j] = rand() % 10;
        }
    }
}

void test1()
{
    matrix a;
    matrix b;
    matrix result;
    _fill_matrix_rand(a);
    _fill_matrix_rand(b);

    _measure_runtime(_ijk, a, b, result, "ijk");
}

void test2()
{
    matrix a;
    matrix b;
    matrix result;
    _fill_matrix_rand(a);
    _fill_matrix_rand(b);

    _measure_runtime(_kij, a, b, result, "kij");
}

void test3()
{
    matrix a;
    matrix b;
    matrix result;
    _fill_matrix_rand(a);
    _fill_matrix_rand(b);

    _measure_runtime(_jki, a, b, result, "jki");
}
