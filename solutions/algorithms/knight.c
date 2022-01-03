/*******************************************************************/
/*** Calculates for an nxn chess board a tour of a knight, which ***/
/*** visits each square exactly once                             ***/
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


/******************* move_knight() *************************/
/** Calculates recursively via backtracking a tour for    **/
/** the knight, such that all squares with visit[x][y]=0  **/
/** are visited once.                                     **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**         n: size of board                              **/        
/**      step: how many sites already visited?            **/
/**       x,y: current position of knight                 **/
/**     visit: states whether and when square was visited **/
/**     dx,dy: possible move directions                   **/
/** Returns:                                              **/
/**        (nothing)                                      **/
/***********************************************************/
void move_knight(int n, int step, int x, int y, 
                 short int **visit, int *dx, int *dy)
{
  int t, i, j;                             /* loop counters */
  int x2, y2;                              /* new positions */
    

  if(step== n*n)                                    /* done */
  { 
    for(i=0; i<n; i++)                        /* print tour */
    {
      for(j=0; j<n; j++)
	printf("%3d ", visit[i][j]);
      printf("\n");
    }
    exit(0);
  }
  for(t=0; t<8; t++)       /* try all 8 possible directions */
  {
    x2 = x+ dx[t]; y2 = y + dy[t];
    if( (0<=x2)&&(x2 <n)&&(0<=y2)&&(y2<n)&&(!visit[x2][y2]))
    {
      visit[x2][y2] = step+1;                /* move knight */
      move_knight(n, step+1, x2, y2, visit, dx, dy);
      visit[x2][y2] = 0;
    }
  }
}

/**************************************************************/
/**                m a i n    p r o g r a m                  **/
/**************************************************************/
int main(int argc, char **argv)
{
  int n;                                         /* size of the board */
  int dx[8], dy[8];           /* relative distances of possible moves */
  short int **visit;                         /* stores tour of knight */
  int i, j;                                          /* loop counters */

  n = atoi(argv[1]);                                  /* read in size */
  visit = (short int **) malloc(n*sizeof(short int *));
  for(i=0; i<n; i++)                              /* initialize board */
  {
    visit[i] = (short int *) malloc(n*sizeof(short int));
    for(j=0; j<n; j++)
      visit[i][j] = 0;
  }


  dx[0] = -2; dy[0] = 1;                          /* initialize jumps */
  dx[1] = -1; dy[1] = 2;
  dx[2] =  1; dy[2] = 2;
  dx[3] =  2; dy[3] = 1;
  dx[4] =  2; dy[4] = -1;
  dx[5] =  1; dy[5] = -2;
  dx[6] = -1; dy[6] = -2;
  dx[7] = -2; dy[7] = -1;


  visit[0][0]=1;                 /* start knight at upper left corner */
  move_knight(n, 1, 0, 0, visit, dx, dy);

  for(i=0; i<n; i++)
    free(visit[i]);
  free(visit);

  return(0);
}
