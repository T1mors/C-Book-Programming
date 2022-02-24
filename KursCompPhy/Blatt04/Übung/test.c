/*******************************************************************/
/*** Solves the N-queen problem and prints all solutions         ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Backtracking                                       ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

int boundaries(int n, int x, int y, int dx, int dy)
{
    if ((x+dx >= 0) && (x+dx < n) && (y+dy >= 0) && (y+dy < n))
        {
            return (1);
        }
    else
    {
        return (0);
    }
}


/******************************* queen() ***************************/
/** Places a queen in different rows of column                    **/
/** 'n' of checker board of size 'size'x'size'                    **/
/** Calls itself recursively to search for                        **/
/** solutions. If solution found, it is printed.                  **/
/**                                                               **/
/** PARAMETERS: (*)= return-paramter                              **/
/**          c: current column                                    **/
/**          N: size of board                                     **/
/**        pos: positions of queens in different columns          **/
/**        row: is there a queen in row y?                        **/
/**    diag_up: is there a queen in up diagonal ?                 **/
/**  diag-down: is there a queen in down diagonal ?               **/
/**                                                               **/
/** RETURNS:                                                      **/
/**    nothing                                                    **/
/*******************************************************************/
void knight(int n, int step, int x, int y,
            int **visit, int *dx, int *dy, int *counts)
{
  int i, j;   /* loop counters */
  if (step == n * n) /* solution found ? */
  {
    /*for (i=0; i < n; i++){
        for (j=0; j < n; j++)
        {
            printf("%d\t", visit[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    */
    *counts += 1;

    return;
  }

  for (i = 0; i < 8; i++) /* place queen in all rows of column c */
  {    
      if (!boundaries(n, x, y, dx[i], dy[i]))
      {
          continue;
      }
      if (!visit[x+dx[i]][y+dy[i]])
        {
        
        visit[x+dx[i]][y+dy[i]] = ++step;
        x += dx[i];
        y += dy[i];
        knight(n, step, x, y, visit, dx, dy, counts);
        step--;
        visit[x][y] = 0;
        x -= dx[i];
        y -= dy[i];
        }
  }
  x = 0;
  y = 0;
}

int main(int argc, char *argv[])
{
  int N;          /* size of checker board = parameter */
  int x;       /* position of a queen in the column */
  int y;       /* row[y] = is there a queen in row y ? */
  int step = 1;   /* d[x-y+(N-1)] = a queen in diagonal x-y=const ? */
  int **visit; /* d[x+y] = is a queen in diagonal x+y=const ? */
  int i, j;
  int counts = 0;

  N = atoi(argv[1]);
  x = atoi(argv[2]);
  y = atoi(argv[3]);

  visit = (int **) malloc(N*sizeof(int *));
  for (i=0; i < N; i++)
  {
      visit[i] = (int *) malloc(N*sizeof(int *));
  }
 
  for (i=0; i < N; i++)
  {
      for (j=0; j < N; j++){
          visit[i][j] = 0;
      }
  }

   /* size = command line argument */


  int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
  int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
  
  visit[x][y] = 1;

  knight(N, step, x, y, visit, dx, dy, &counts); /* do work */
  printf("counts: %d\n", counts);
  free(visit);
  return (0);
}
