#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if( argc != 2){
     printf("Incorrect number of arguments.");
     exit(1);
  }
  char * arg = argv[1];
  sleep(atoi(arg));
  
  exit(0);
}

