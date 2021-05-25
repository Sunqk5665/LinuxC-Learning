#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void pr_mask(int signum){
	sigset_t sigset;
	if(sigprocmask(0,NULL,&sigset)<0){
		printf("sigprocmask error");
		exit(0);
	}
	if(sigismember(&sigset,SIGINT))
		printf("SIGINT \n");
	if(sigismember(&sigset,SIGTERM)){
		printf("SIGTERM \n");
		exit(0);
	}
}

int main(){
char buffer1[100],buffer2[100];
int i;
if(signal(SIGINT,&pr_mask)==-1){
	printf("Couldn't register signal hander for SIGINT!\n");
	exit(1);
}
if(signal(SIGTERM,&pr_mask)==-1){
	printf("Cound't register signal hander for SIGTERM! \n");
	exit(1);
}
printf("Pid of This Process:%d \n",getpid());

for(;;){
	printf("Please input:\n");
	fgets(buffer1,sizeof(buffer1),stdin);
	for(i=0;i<100;i++){
		if(buffer1[i]>=97&&buffer1[i]<=122)
			buffer2[i]=buffer1[i]-32;
		else
			buffer2[i]=buffer1[i];
	}
	printf("Your input is:%s\n",buffer2);
}
exit(0);
}
