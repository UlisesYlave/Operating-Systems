#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

double final=1;

void creararbol(int);

int main(int narg, char *argv[]){
  int n;
  n=atoi(argv[1]);
  for(int i=0;i<n-1;i++)final*=2;
  creararbol(1);
  return 0;
}

void creararbol(int x){
  char cadena[60];
  sprintf(cadena,"Soy el proceso %d con pid %d y ppid %d\n",x,getpid(),getppid());
  write(1,cadena,strlen(cadena));
  if (x>=final){
    sleep(5);
    exit(0);
    return;
  }
  if (!fork()) { creararbol(2*x); sleep(5); waitpid(getpid(),NULL,0); exit(0); }
  if (!fork()) { creararbol(2*x+1);sleep(5); waitpid(getpid(),NULL,0); exit(0);}
  if (x==1){
    char command[100];
    snprintf(command, sizeof(command), "pstree -p %d > binarytree.txt", (int)getpid());
    system(command);
  }
}