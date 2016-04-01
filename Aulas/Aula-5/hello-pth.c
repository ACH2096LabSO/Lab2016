/*****************************************************************************
* FILE: hello-pth.c
* DESCRIPTION:
*   This program illustrates the use of Pthreads. 
*   
* SOURCE: Gisele Craveiro
* LAST REVISED:  06/02/2002
******************************************************************************/

#include <pthread.h>
#include "errors.h"


#define MAXTHRDS 5
#define MULTIPROCESSADOR 0
/*pthread_t callThd[MAXTHRDS];*/

void *hello_world (void *arg)
{
  int *id;
  id = (int *) arg;
  printf("\t \t Hello World - Executor %d\n", id);
  return NULL;
}


int main (int argc, char* argv[])
{
   int i, rc;
   int myid, numprocs; 
   int numthrds;
   int status;
   pthread_attr_t attr;
   pthread_t hello_id[MAXTHRDS];
   


     numthrds = MAXTHRDS;
 
     for (i=0; i<numthrds; i++){
      status = pthread_create (&hello_id[i], NULL, hello_world, (void *)i+1);
      if (status != 0)
        err_abort (status, "Create thread");
     status = pthread_join (hello_id[i], NULL);
      if (status != 0)
        err_abort (status, "Join thread");
     }
   exit(0);
}   
