#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int semaphore_P(int);
int semaphore_V(int sem_id);

int main(int argc,char* argv[])
{
	int sem_id;
	int i,creat = 0;
	int pause_time;
	char *cp;
	
	if(argc<=1)
	{
		printf("usage:%s parameter1 parameter2 ...\n",argv[0]);
		exit(1);
	}
	srand((unsigned int)getpid());
	if((sem_id=semget((key_t)1234,1,IPC_CREAT|0660))==-1)
	{
		printf("semget failed!\n");
		exit(2);
	}
	if(strcmp(argv[1],"1"))
	{
		semctl(sem_id,0,SETVAL,1);
		creat = 1;
		sleep(2);
	}
	for(i=0;i<argc;i++)
	{
		cp = argv[i];
		if(!semaphore_P(sem_id))
			exit(3);
		printf("Process %d:",getpid());
		fflush(stdout);
		while(*cp)
		{
			printf("%c",*cp);
			fflush(stdout);
			pause_time = rand()%2;
			sleep(pause_time);
			cp++;
		}
		printf("\n");
		if(!semaphore_V(sem_id))
			exit(4);
		pause_time = rand()%2;
		sleep(pause_time);
	}
	printf("\n %d -finished\n",getpid());
	if(creat==1)
	{	
		sleep(10);
		semctl(sem_id,0,IPC_RMID,0);
	}
	return 0;
}

int semaphore_P(int sem_id)
{
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;
	
	if(semop(sem_id,&sb,1)==-1)
	{
		printf("semaphore_P failed.\n");
		return 0;
	}
	return 1;
}

int semaphore_V(int sem_id)
{
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sb,1)==-1)
	{
		printf("semophore_V failed.\n");
		return 0;
	}
	return 1;
}

