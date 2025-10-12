#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
  pid_t child;
  if (( child=fork())){
    fprintf(stderr,"\nFork() devolvió %d por tanto soy el padre con ID = %d", child,getpid());
    waitpid(child,NULL,WUNTRACED);
  }else {
    fprintf(stderr,"\nFork() devolvió %d por tanto soy el hijo con ID = %d\n", child,getpid());
    char comando[100];
    sprintf(comando, "pstree -a -p %d > aprocesos.txt", getppid());
    system(comando);
  }
  return 0;
}