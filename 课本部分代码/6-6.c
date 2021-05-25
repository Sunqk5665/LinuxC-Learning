#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

int quitflag=0;

int main(){
void sig_int(int);
sigset_t newmask,oldmask,zeromask;
if(signal(SIGINT,&sig_int)==-1){
	printf("Couldn't register signal hander for SIGINT!\n");
	exit(1);
	
}
if(signal(SIGQUIT,&sig_int)==-1){
	printf("Couldn't register signal hander for SIGQUIT!\n");
	exit(2);
}
sigemptyset(&zeromask);
sigemptyset(&newmask);
sigaddset(&newmask,SIGQUIT);
if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0){
	printf("SIG_BLOCK error!\n");
	exit(3);
}
while(quitflag==0){
	sigsuspend(&zeromask);
}
printf("process wake up.\n");
quitflag=0;
if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0){
	exit(0);
}
}

void sig_int(int signum){
	if(signum==SIGINT)
		printf("\n interrupt \n");
	else if(signum==SIGQUIT){
		printf("catch SIGQUIT \n");
		quitflag=1;
	}
return;
}
