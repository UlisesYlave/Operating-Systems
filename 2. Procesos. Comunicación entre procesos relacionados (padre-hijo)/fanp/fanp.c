#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
  int i, status;
  pid_t child, pid_padre;

  pid_padre=getpid();
  for(i=1;i<4;++i)
    if (( child=fork()) <=0) break;
    else fprintf(stderr,"Este es el ciclo Nro %d y se esta creando el pr>  if (i == 4){
    char comando[100];
    sprintf(comando,"pstree -a -p %d > fanp.txt",pid_padre);
    system(comando);
  }
  if (pid_padre==getpid()) for(i=1;i<4;++i) wait(&status);
  fprintf(stderr,"Este el proceso %d con padre %d\n",getpid(),getppid());  return 0;
}