#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <math.h>

int isPrime(int i){
  int upperbound = (int)sqrt(i);  
  for(int x = 2; x <= upperbound; x++){
	if(i%x == 0){
	  return 0;
	}
  }//end of for loop
  return 1;

}


int main(int argc, char *argv[]){

  int *p = (int*)malloc(2*sizeof(int));
  
  for(int x = 2; x <= 35; x++){
  
    if(isPrime(x) == 1){
      //The numer is prime do something here
    }//end of if
  }//end of for loop

  exit(0);
}//end of main
