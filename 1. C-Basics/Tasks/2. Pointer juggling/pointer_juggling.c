#include <stdio.h>

int main(int argc, char **argv[])
{
    double value = 3;
    double *p1 = &value;
    double *p2 = p1;
    printf("This is value directly %lf\n", value);
    printf("This is value over p1 %lf\n", *p1);
    printf("This is value over p2 %lf\n", *p2);

    // Or first definition of variables and then assignment

    int val;
    int *p1_int;
    int **p2_int; // Pointer to pointer

    val = 3;
    p1_int = &val;
    p2_int = &p1_int;

    printf("This is val directly %d\n", val);
    printf("This is val over p1 %d\n", *p1_int);
    printf("This is val over p2 %d\n", **p2_int); // Here we need double asteriks
}