#include <stdio.h>
#include <stdlib.h>
// Macro for number of rows LEN(matrix) and columns LEN(matrix[0])
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

void print_matrix(int rows, int columns, double **matrix);
void print_matrix_array(int rows, int columns, double *matrix);
double **matrix_change_rows(double *matrix, int rows_mat, int columns_mat, int rows, int columns);

int main(int argc, char **arg)
{
    // Neighboring rows of an nxn matrix (n is even) are interchanged through a matrix
    // multiplication by perm

    // *** Whole Computation within the code ***
    // arrays {} are always stacked underneath each other, so be careful which numbers you use in [][]
    double matrix[4][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}};
    int i, j, k;

    // Number of rows and columns
    int rows_mat = sizeof(matrix) / sizeof(matrix[0]);
    int columns_mat = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    // How does the computation work?
    printf("sizeof(matrix): %ld, sizeof(matrix[0]): %ld\n", sizeof(matrix), sizeof(matrix[0]));

    printf("Number of rows: %d and columns: %d\n", rows_mat, columns_mat);
    printf("With Macro: rows: %d and columns: %d\n", LEN(matrix), LEN(matrix[0]));

    // Check if rows == columns and number of rows is even
    if (rows_mat % 2 != 0)
    {
        printf("Error: Number of rows must match the number of columns and number of rows must be even\n");
        printf("Given: Rows: %d, Columns: %d\n", rows_mat, columns_mat);
        return 1;
    }

    // Create permutation and result matrix
    // We have result = test X matrix --> n x m = n x n * n x m
    // permutation matrix must always by n x n

    double **perm;
    double **result;
    perm = (double **)malloc(rows_mat * sizeof(double *));
    result = (double **)malloc(rows_mat * sizeof(double *));
    for (i = 0; i < rows_mat; i++)
    {
        perm[i] = (double *)malloc(rows_mat * sizeof(double));
        result[i] = (double *)malloc(columns_mat * sizeof(double));
    }

    // Of LEFT matrix
    int rows = rows_mat;
    int columns = rows_mat;
    // Create permutation matrix
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            perm[i][j] = 0;
        }
        // This creates the entries to change two neighboring rows.
        // An even row (i=0,2,4,...) goes to an uneven place and the over way around.
        if (i % 2 == 0)
        {
            perm[i][i + 1] = 1;
        }
        else
        {
            perm[i][i - 1] = 1;
        }
    }

    // Matrix multiplication
    // Go through each row of left matrix
    for (i = 0; i < rows; i++)
    {
        // Go through each entry in this row
        for (k = 0; k < columns; k++)
        {
            // For each entry in row (thus column index) we need to go down column
            // of the right matrix. This is done by the [j][k] call
            for (j = 0; j < columns; j++)
            {
                result[i][k] += perm[i][j] * matrix[j][k];
                // printf("perm[i][j] = %f, matrix[j][k] = %f\n", perm[i][j], matrix[j][k]);
            }
            // printf("%f\n", result[i][k]);
        }
    }
    // double **perm2 = (double **)malloc(rows * sizeof(double *));
    // printf("\nPut this one line above and it works but it does not work here. Strange:\n"); // Malloc() Corrupted top size

    // Print out matrices
    printf("Matrix before:\n");
    // (double *) matrix or &matrix[0][0]
    print_matrix_array(rows_mat, columns_mat, (double *)matrix);

    printf("\nPerm matrix:\n");
    print_matrix(rows, rows, perm);

    printf("\nResult matrix:\n");
    print_matrix(rows_mat, columns_mat, result);

    // *** Whole computation in another function ***
    result = matrix_change_rows(&matrix[0][0], rows_mat, columns_mat, rows, columns);
    printf("Matrix before:\n");
    print_matrix_array(rows, columns, &matrix[0][0]);

    printf("\nResult matrix:\n");
    print_matrix(rows_mat, columns_mat, result);

    // *** Use other multiply function ***
    // Problematic because one is dynamic allocated (perm) and the other as array (matrix)
    // void multiply(int mat1[4][4], int mat2[4][4], int res[4][4], int N)
    // But in Principle the exact same as my function
    // {
    //     int i, j, k;
    //     for (i = 0; i < N; i++)
    //     {
    //         for (j = 0; j < N; j++)
    //         {
    //             res[i][j] = 0;
    //             for (k = 0; k < N; k++)
    //                 res[i][j] += mat1[i][k] * mat2[k][j];
    //         }
    //     }
    // }
    // double result2[rows][columns];
    // multiply(matrix, perm, result2, rows);

    for (i = 0; i < rows; i++)
    {
        free(perm[i]);
        free(result[i]);
    }
    return 0;
}

//* Print Matrix for pointer to pointer type double**
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

//* Whole computation with a function. Usage of pointers.
double **matrix_change_rows(double *matrix, int rows_mat, int columns_mat, int rows, int columns)
{
    printf("\nNumber of rows_mat: %d and columns_mat: %d\n", rows_mat, columns_mat);
    printf("Number of rows: %d and columns: %d\n", rows, columns);

    int i, j, k;
    static double **result;
    double **perm;

    // No Idea why this results in a problem with memory allocation

    perm = (double **)malloc(rows * sizeof(double *));
    result = (double **)malloc(rows_mat * sizeof(double *));
    for (i = 0; i < rows; i++)
    {
        perm[i] = (double *)malloc(columns * sizeof(double));
        result[i] = (double *)malloc(columns_mat * sizeof(double));
    }

    // Create permutation matrix
    printf("Create Permutation matrix\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            perm[i][j] = 0;
        }
        // This creates the entries to change two neighboring rows.
        // An even row (i=0,2,4,...) goes to an uneven place and the over way around.
        if (i % 2 == 0)
        {
            perm[i][i + 1] = 1;
        }
        else
        {
            perm[i][i - 1] = 1;
        }
    }

    // Matrix multiplication
    for (i = 0; i < rows; i++)
    {
        for (k = 0; k < columns; k++)
        {
            double *row_start = &matrix[i * columns];

            for (j = 0; j < columns; j++)
            {
                // (&matrix[j])[k] is NOT correct here
                result[i][k] += perm[i][j] * row_start[k];
            }
        }
    }

    return result;
}