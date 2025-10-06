#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 40
void hijo(int, int*);

int main(int narg,char*argv[]){
  int i,j,n,fd[2],pids[N],total;
  char cmd[15];

  if (narg != 2){
    printf("Se debe ingresar: ./arbolpodado <numero_procesos>");
    exit(1);
  }

  pipe(fd);
  n=atoi(argv[1]);
  for(i=0;i<n;i++){
    if (!fork()) hijo(i,fd);
  }
  char comando[20];
  snprintf(comando,sizeof(comando),"pstree -p %d",getpid());
  total=(1+n)*n/2;
  for(j=0;j<total;j++) read(fd[0],&pids[j],sizeof(int));
  system(comando);
  for(j=0;j<total;j++) kill(pids[j],SIGTERM);
  exit(0);
}

void hijo(int i, int *fd){
  int j,mypid;
  for(j=0;j<i;j++){
    if (fork()>0) break;
  }
  mypid=getpid();
  write(fd[1],&mypid,sizeof(int));
  sleep(1);
}