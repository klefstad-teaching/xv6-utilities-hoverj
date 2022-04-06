#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

//using fmtname from ls.h
char* 
my_fileStrip(char *path){
  static char buf[DIRSIZ+1];
  char* p;

  for(p=path+strlen(path); p>= path && *p != '/'; p--)
	  ;
  p++;
  
  memmove(buf, p, strlen(p)); //move the memory from p into buf
  return buf;
}

//rewriting ls to include the file comparison
void 
my_find(char *path, char *fileCompare){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }//end of if

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
 }//end of if

  printf("%s\n", my_fileStrip(path));
  if(strcmp(my_fileStrip(path), fileCompare) == 0){
    printf("%s\n",path);
  }
  switch(st.type){
  case T_FILE:
	 // printf("%s %d %d %l\n", my_fileStrip(path), st.type, st.ino, st.size);
	  break;

  case T_DIR:
	  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
	   // printf("ls: path is too long");
	    break;
	  }
	  strcpy(buf, path);
	  p = buf + strlen(buf);
	  *p++ = '/';
	  while(read(fd, &de, sizeof(de)) == sizeof(de)){
	    if(de.inum == 0)
		    continue;

	    if(strcmp(de.name,".") == 0|| strcmp(de.name, "..") == 0)//skip over the . and .. directores
	      continue;
	    
	    memmove(p, de.name, DIRSIZ);
	    p[DIRSIZ] = 0;

	   if(stat(buf, &st) < 0){
		  // printf("ls: cannot stat %s\n", buf);
		   continue;
	   }
	   my_find(buf, fileCompare);

	    
	  }
	  break;

  }//end of switch statement
  close(fd);

}//end of ls rewrite


int main(int argc, char *argv[]){
  
  if(argc < 3){
    printf("Incorrect input received");
    exit(0);
  }
  char* startingPath = argv[1];
  char* searchString = argv[2];
  my_find(startingPath, searchString);
  exit(0);
}
