#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
callFunction(int p){
  int numToPrint;
  read(p, &numToPrint, 4);
  printf("prime %d\n", numToPrint);
  
  int p1[2];
  pipe(p1);
  int tempVar = -1; //assign tempVar with some value

  while(1){
    int n = read(p, &tempVar, 4); //read into tempVar
    if( n <= 0) //if 0 or less then the read is done
      break;
    if(tempVar % numToPrint != 0){ //compare the number read with the number being read to print
      write(p1[1], &tempVar, 4);
    }//end of if

  }//end of while
  if(tempVar == -1){
    close(p1[1]);
    close(p1[0]);
    close(p);
    return;
    //if temp var is -1 close all pipes and return
  }//end of tempVar

  int pid = fork();
  if(pid == 0){
    close(p1[1]);
    close(p);
    callFunction(p1[0]);//recursivley call on the function
    close(p1[0]);

  }//end of pid if
  else{
    close(p1[1]);
    close(p1[0]);
    close(p);
    wait(0);
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
