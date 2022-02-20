#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************* depose() *****************/
/** Put one particle in one randomly chosen  **/
/** column of a one-dimensional surface      **/
/** uses periodic boundary conditions        **/
/** PARAMETERS: (*)= return-paramter         **/
/**       size: of system                    **/
/** (*) height: 1d surface                   **/
/**  num_steps: num of deposed particles     **/
/** RETURNS:                                 **/
/**    nothing                               **/
/**********************************************/
void depose(int size, int *height, int num_steps)
{
  int column, left, right, t;
  for (t = 0; t < num_steps; t++)
  {
    column = (int)(size * drand48()); /* choose column */
    height[column]++;
    if (column == 0) /* at left boundary ? */
      left = size - 1;
    else
      left = column - 1;
    if (column == (size - 1)) /* at right boundary ? */
      right = 0;
    else
      right = column + 1;
    if (height[left] > height[column]) /* stic particle to left ? */
      height[column] = height[left];
    if (height[right] > height[column]) /* stic particle to right ? */
      height[column] = height[right];
  }
}

typedef struct
{
  double mean;
  double roughness;
} m_r_structure;

m_r_structure analysis(int *height, int size)
{
  double h_mean = 0;
  double h_mean_2 = 0;
  double W;

  for (int i = 0; i < size; i++)
  {
    h_mean += height[i];
    h_mean_2 += height[i] * height[i];
  }
  h_mean = h_mean / size;
  h_mean_2 = h_mean_2 / size;

  W = sqrt(h_mean_2 - h_mean * h_mean);

  m_r_structure mean_roughness;
  mean_roughness.mean = h_mean;
  mean_roughness.roughness = W;

  return mean_roughness;
}

int main(int argc, char **argv)
{
  int *height;
  int argz = 1; /* for treating arguments */
  double *m, *m2, *w, *w2;
  int t, step, run, size = 10;
  int num_iterations = 100; /* num of swees per run */
  int num_runs = 1000;      /* number of independent runs */
  m_r_structure mean_roughness;

  size = atoi(argv[argz++]); /* read arguments */
  num_iterations = atoi(argv[argz++]);
  num_runs = atoi(argv[argz++]);

  height = (int *)malloc(size * sizeof(int)); /* allocate system */
  m = (double *)malloc(num_iterations * sizeof(double));
  w = (double *)malloc(num_iterations * sizeof(double));
  m2 = (double *)malloc(num_iterations * sizeof(double));
  w2 = (double *)malloc(num_iterations * sizeof(double));
  for (t = 0; t < num_iterations; t++)
  {
    m[t] = 0;
    m2[t] = 0;
    w[t] = 0;
    w2[t] = 0;
  }

  for (run = 0; run < num_runs; run++) /* make 'num_runs' independent runs */
  {
    for (t = 0; t < size; t++) /* initialise surface */
      height[t] = 0;

    for (step = 0; step < num_iterations; step++) /* do sweeps */
    {
      depose(size, height, size);
      /*printf("%d %f\n", step, roughness(size, height));*/

      /******** INSERT THE CALL TO FUNCTION analysis() here *******/

      mean_roughness = analysis(height, size);

      m[step] += mean_roughness.mean /****** ADD MEAN ******/;
      m2[step] += mean_roughness.mean * mean_roughness.mean /****** ADD MEAN*MEAN ******/;
      w[step] += mean_roughness.roughness /****** ADD ROUGHNESS ******/;
      w2[step] += mean_roughness.roughness * mean_roughness.roughness /****** ADD ROUGHROUGHNESS*ROUGHNESS ******/;
    }
  }

  printf("# t mean (error)  roughn.  (error)  size\n");
  for (step = 0; step < num_iterations; step++) /* print results */
    printf("   %d %f %f %f %f %d\n", step, m[step] / num_runs,
           sqrt((m2[step] / num_runs - m[step] * m[step] / (num_runs * num_runs)) /
                (num_runs - 1)),
           w[step] / num_runs,
           sqrt((w2[step] / num_runs - w[step] * w[step] / (num_runs * num_runs)) /
                (num_runs - 1)),
           size);

  free(m);
  free(w);
  free(m2);
  free(w2);

  return (0);
}
