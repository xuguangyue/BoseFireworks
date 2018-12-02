#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

double randn (double mu, double sigma){
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;

  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }

  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);

  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;

  call = !call;

  return (mu + sigma * (double) X1);
}

int main(){
  double mu = 0.;
  double sigma = 1.;
  long Nx = 100000;
  long cnti;
  FILE *file;

  double *x;

  x = (double *) malloc((size_t) (Nx * sizeof(double)));

  srand((unsigned int)time(NULL));

  for (cnti = 0; cnti < Nx; cnti ++){
    x[cnti] = randn(mu,sigma);
  }

  file = fopen("rr.txt", "w");
  for (cnti = 0; cnti < Nx; cnti ++){
    fprintf(file, "%8le\n", x[cnti]);
  }

  return 0;
}
