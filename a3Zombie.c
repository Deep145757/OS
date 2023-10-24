#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void arrayStore(char* arr[],int* i_arr, int n)
{
	for(int i=0;i<n;i++)
	{
		i_arr[i] = atoi(arr[i+1]);
	}
}

void arraySort(int* arr, int n, int falg)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(falg == -1)
			{
				if(arr[j]<arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
			else if(falg == 1)
			{
				if(arr[j]>arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
}

void arrayDisplay(int* arr, int n)
{
	printf("Displaying Array.... \n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n\n");
}

void main(int argc, char* argv[])
{
	int arr[argc-1];
	int len = argc - 1;
	arrayStore(argv,arr,len);	
	
	pid_t pid, tpid, status;
	pid = fork();
	if(pid != 0)
	{
		sleep(1); //Zombie State
		system("ps");
		printf("\nParent Process with ID = %d \n",getpid());
		arraySort(arr,len,1);
		arrayDisplay(arr,len);		
	}
	else if(pid == 0)
	{
		system("ps");
		printf("\nChild Process with ID = %d\n",getpid());
		printf("Child's Parent ID = %d\n",getppid());
		arraySort(arr,len,-1);
		arrayDisplay(arr,len);
	}
}

