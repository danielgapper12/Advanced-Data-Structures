
/* Example source code generated for Cpt S 411: Intro to Parallel Computing
* Author: Ananth Kalyanaraman
* Institution: Washington State University
* Disclaimer: Use at your own risk!
* */
/* This is a simple for loop parallelizer using OpenMP multithreading.
*
*/

//gcc -o loop -fopenmp main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> // need to include this header for OpenMP library calls
#include <math.h>
#include <assert.h>
#define SOMEPRIME 7919

int main(int argc, char *argv[]) // argc = argument count, argv = argument vector
{
  long long int i, loops;
  // loop {number of iterations} [number of threads]
  // argv[0]: loop; argv[1]=#iterations, argv[2]=#threads
  // argc = 3
  if(argc<2) 
  {
    printf("Usage: loop {number of iterations} [number of threads]\n");
    exit(1);
  }
  loops = atoll(argv[1]);
  printf("Debug: number of iterations = %lld (%d)\n",loops, sizeof(long long int));
  // default number of threads = 1
  int p=1;
  // assign p to the requested number of threads by the user
  if(argc==3) 
  {
    p = atoi(argv[2]);
    assert(p>=1);
    printf("Debug: number of requested threads = %d\n",p);
  }
  // OpenMP call: sets the number of threads to p
  omp_set_num_threads(p);

  // You are now entering a parallel region....
  #pragma omp parallel
  {
    // This assert line ensures that we got p threads from the OpenMP runtime system as requested
    assert(p==omp_get_num_threads());
    //printf("Debug: number of threads set = %d\
    //n",omp_get_num_threads());
    // This line gets my thread id and assign it to the variable rank
    // Note: each thread will get a different unique rank from [0 to p-1]
    int rank = omp_get_thread_num();
    printf("Rank=%d: my world has %d threads\n",rank,p);
  } // end of my omp parallel region

  // for loop computation
  int a=2;
  // start the timer
  double time = omp_get_wtime();
  #pragma omp parallel for schedule(static) private(a) //creates N threads to run the next enclosed block
    for(i = 0; i < loops; i++) //or line in parallel
    {
        // perform some arbitrary computation
        int b = (a+i) % SOMEPRIME;
    }
  // end of the second parallel region for FOR LOOP
  // end the timer and clock the elapsed time
  time = omp_get_wtime() - time;
  printf("\n %f seconds \n ", time);
  return 0;
}
