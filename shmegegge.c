#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(){

  key_t key = ftok("shmegegge.c", 'R');
  int shmid = shmget(key, 200, 0644 | IPC_CREAT);
  char* data = shmat(shmid, (void*)0, 0);

  if (strlen(data)){
    printf("Contents:%s\n",data);
  }else{
    printf("Just Created Shared Mem\n");
  }

  printf("Change Contents? (y/<ANY OTHER KEY>)\n");
  char * input = malloc(sizeof(char)*200);
  fgets(input,sizeof(char)*200,stdin);
  strtok(input,"\n");
  
  if(!strcmp(input,"y")){
    printf("Enter new string:\n");
    fgets(data,sizeof(char)*200,stdin);
    strtok(data,"\n");
    printf("New Data: %s\n",data);
  }else{
    printf("Did not change: %s\n",data);
  }

  printf("Delete Contents? (y/<ANY OTHER KEY>)\n");
  fgets(input,sizeof(char)*200,stdin);
  strtok(input,"\n");
  
  if(!strcmp(input,"y")){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Deleted\n");
  }else{
    printf("Did not Delete: %s\n",data);
  }

  free(input);

  return 0;
}
