#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int isPrime(int i){ 
  for(int x = 2; x < i; x++){
	if(i%x == 0){
	  return 0;
	}
  }//end of for loop
  return 1;

}


int main(int argc, char *argv[]){

  int *p = (int*)malloc(2*sizeof(int));
  int *buffer = (int*)malloc(2*sizeof(int));
  pipe(p);

  for(int x = 2; x <= 35; x++){
 	int* intP = &x; 
    if(isPrime(x) == 1){
      if(fork() == 0){
        read(p[0], buffer, 1);
        printf("prime %d\n", buffer);

        write(p[1], intP, 1);
        close(p[1]);	
      }//end of fork if
    else{
     write(p[1], intP, 1);
     close(p[1]);
     wait(0);

     read(p[0],buffer, 1);
     printf("prime %d\n", buffer);
     close(p[0]);
   
    }//end of else
    }//end of if
  }//end of for loop

  exit(0);
}//end of main
