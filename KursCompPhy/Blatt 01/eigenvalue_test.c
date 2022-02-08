#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    double seed = 1000;
    int i, j;
    int n = 10; /* matrix has size n x n */
    double matrix[n][n];
    srand48(seed);

    for (i = 0; i < n; i++) /* initialize matrix */
    {
        matrix[i][i] = 1.0;
        for (j = 0; j < i; j++)
        {
            matrix[i][j] = 2 * drand48() - 1;
            matrix[j][i] = matrix[i][j];
    }
    }
    return 0;
}