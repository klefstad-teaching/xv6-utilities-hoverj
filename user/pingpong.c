#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
  int* p = (int*)malloc(2 * sizeof(int));
  char* temp = (char*)malloc(5 * sizeof(char));
  pipe(p);

  if(fork() == 0){//child
    read(p[0], temp, 5);
    printf("%d: received %s\n", getpid(), temp);

    write(p[1], "pong", 5);
    close(p[1]);

  }else{//parent
   write(p[1], "ping", 5);
   close(p[1]);
   wait(0);

   read(p[0], temp, 5);
   printf("%d: received %s\n", getpid(), temp);
   close(p[0]);
  }

  exit(0);
}//end of main
