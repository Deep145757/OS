#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    key_t key = ftok("shmfile.txt",'A');
    int shmid = shmget(key,1024,0777|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    char str1;
  
    printf("Enter data : ");
    scanf("%s",str);
	
    printf("Data written in memory: %s\n",str);
    system("ipcs -m");
    shmdt(str);
	system("ipcs -m");
    return 0;
}
