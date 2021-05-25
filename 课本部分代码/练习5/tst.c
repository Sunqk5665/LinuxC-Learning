#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
pid_t pid;



printf("父进程已经创建！\n");
if((pid=vfork())<0){
	printf("vfork error!!!\n");
	return 1;
}
else if(pid==0){
	printf("进入子进程中......\n");
	sleep(1);
	printf("---已进入子进程---\n");
	printf("子进程:PID=%d\n",getpid());

	execl("./tst01","./tst01",0);

}
	
return 0;
}
