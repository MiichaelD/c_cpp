#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//http://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-work-in-linux

int main()
{ 
  pid_t  pid;
  pid= fork();
  if (pid< 0) { 
    fprintf(stderr, "Fallo en fork()");
  exit(-1);
  }
  
  else 
    if (pid== 0) { /* proceso hijo */
  		execlp("cat", "cat", "./forkExec.c", NULL);
      	//execlp("/bin/ls", "ls", "-l", NULL);
  		//execlp("/bin/sh", "/bin/sh", "ls", "-l", NULL);
    }
    else { /* proceso padre espera a que el hijo concluya */
      wait(NULL);
      printf ("Proceso hijo concluido\n");
      exit(0);
    }
}