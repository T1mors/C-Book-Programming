#include <stdlib.h>
// Rows and columns of matrix
// https://stackoverflow.com/questions/34134074/c-size-of-two-dimensional-array
// Macro for number of rows LEN(matrix) and columns LEN(matrix[0])
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

int main(int argc, char **arg)
{
    printf("Useful Code Summary\n");

    // *** MATRIX ***

    // * Number of rows and columns
    // Number of rows and columns
    int rows = sizeof(matrix) / sizeof(matrix[0]);
    int columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    // or

    int LEN_rows = LEN(matrix);
    int LEN_columns = LEN(matrix[0]);

    //* Print Matrix for pointer to pointer type double**
    // https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/2d_array_practice.c
    // https://stackoverflow.com/questions/2828648/how-to-pass-a-multidimensional-array-to-a-function-in-c-and-c
    void print_matrix(int rows, int columns, double **matrix)
    {
        int i, j;
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < columns; j++)
            {
                printf("[%d][%d] = %f\n", i, j, matrix[i][j]);
            }
        }
    }
    //! Example
    double **matrix;
    rows = 4;
    columns = 4;
    matrix = (double **)malloc(rows * sizeof(double *));
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    print_matrix(rows, columns, matrix);

    //* Print Matrix for array type [][] variable number of rows and columns
    void print_matrix_array(int rows, int columns, double *matrix)
    {
        int i, j;
        for (i = 0; i < rows; i++)
        {
            double *row_start = &matrix[i * columns];
            for (j = 0; j < columns; j++)
            {
                // You can also just use this
                // (&matrix[i*columns])[j]
                printf("[%d][%d] = %f\n", i, j, row_start[j]);
            }
        }
    }
    //! Example
    double matrix[4][4] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4}};
    // (double *) matrix or &matrix[0][0]
    print_matrix_array(4, 4, (double *)matrix);

    // * Multiply Matrices
    // https://www.geeksforgeeks.org/c-program-to-multiply-two-matrices/

    void multiply(int mat1[][N], int mat2[][N], int res[][N])
    {
        int i, j, k;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                res[i][j] = 0;
                for (k = 0; k < N; k++)
                    res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}