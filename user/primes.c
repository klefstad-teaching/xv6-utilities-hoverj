#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void callFunction(int p);

void
printPrime(int n){
  printf("prime %d\n", n);
}


void
ifFork(int *p, int p1){
  close(p[1]);
  close(p1);
  callFunction(p[0]);
  close(p[0]);
 
}

void
elseFork(int *p, int p1){
  close(p[1]);
  close(p[0]);
  close(p1);
  wait(0);
}

void
callFunction(int p){
  
  int pipeConnect[2];
  int varRead = -1;

  int numToPrint;
  read(p, &numToPrint, 4);
  printPrime(numToPrint);
  
  pipe(pipeConnect);
  for(;;){
    int n = read(p, &varRead, 4); //read into tempVar
    if( n <= 0) //if 0 or less then the read is done
      break;
    if(varRead % numToPrint != 0){ //compare the number read with the number being read to print
      write(pipeConnect[1], &varRead, 4);
    }//end of if

  }//end of while
  if(varRead == -1){
    close(pipeConnect[1]);
    close(pipeConnect[0]);
    close(p);
    return;
    //if temp var is -1 close all pipes and return
  }//end of tempVar

  int pid = fork();
  if(pid == 0){
    ifFork(pipeConnect, p);
	  // close(pipeConnect[1]);
   // close(p);
   // callFunction(pipeConnect[0]);//recursivley call on the function
   // close(pipeConnect[0]);

  }//end of pid if
  else{
   elseFork(pipeConnect, p);
   // wait(0);
  }

}

int main(int argc, char *argv[]){
  int p[2];
  pipe(p);
  for(int i = 2; i <= 35; ++i){
    int whatToWrite = i;
    write(p[1], &whatToWrite, 4); 
  }//end of for loop
  close(p[1]);//close the writing pipe
  callFunction(p[0]);
  close(p[0]);//close the reading pipe
  exit(0);
}//end of main
