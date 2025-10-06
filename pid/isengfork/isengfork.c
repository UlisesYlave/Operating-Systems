#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
  int ii=0;
  if (fork() == 0) ii++;
  if (ii == 1 ){
    if (fork()==0) ii++;
    if (ii == 2){
      if (fork()==0) ii++;
      if (ii == 3){
        sleep(5);
        printf("Result = %3.3d \n",ii);
        exit(0);
      }
      sleep(5);
      printf("Result = %3.3d \n",ii);
      waitpid(getppid(),NULL,0);
      exit(0);
    }
    sleep(5);
    printf("Result = %3.3d \n",ii);
    waitpid(getppid(getppid()),NULL,0);
    exit(0);
  }
  if (fork() == 0) ii++;
  if (ii == 1){
    if (fork()==0) ii++;
    if (ii == 2){
      sleep(5);
      printf("Result = %3.3d \n",ii);
      exit(0);
    }
    sleep(5);
    printf("Result = %3.3d \n",ii);
    waitpid(getppid(),NULL,0);
    exit(0);
  }
  if (fork() == 0) ii++;
  if (ii == 1){
    sleep(5);
    printf("Result = %3.3d \n",ii);
    exit(0);
  }
  printf("Result = %3.3d \n",ii);

  char command[100];
  snprintf(command, sizeof(command), "pstree -p %d > isengfork.txt", (int)getpid());
  system(command);
  waitpid(getppid(getppid(getppid())),NULL,0);
  waitpid(getppid(getppid()),NULL,0);
  waitpid(getppid(),NULL,0);
  return 0;
}