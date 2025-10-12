#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
  int i, status;
  pid_t child,pid_padre;
  pid_padre=getpid();
  for (i=1;i<4;++i) if  (( child=fork())) break;
  fprintf(stderr,"Esta es la vuelta Nro %d\n",i);
  fprintf(stderr,"Recibí de fork el valor de %d\n",child);
  fprintf(stderr,"Soy el proceso %d con padre %d\n\n",getpid(),getppid()>  if (i==4){
    char comando[100];
    sprintf(comando,"pstree -a -p %d > chainp.txt",pid_padre);
    system(comando);
  }
  wait(&status);
  return 0;
}