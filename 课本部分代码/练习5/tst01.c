#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


void h_exit(int status)
{
	if(WIFEXITED(status))
		printf("noemal termination,exit status=%d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal terminaton,signal number=%d %s\n",WTERMSIG(status),
	#ifdef WCOREDUMP
		WCOREDUMP(status)?")":"(core file generated)");
	#else
		")");
	#endif
}

int main(){
pid_t pid;
int status;
char ch;
int i;
printf("\n---输入0退出转换---输入1进行转换---\n");
scanf("%d",&i);
if(i==0){
	return 0;
}
else if(i==1){
	printf("请输入一个字符：\n");
	scanf("%c",&ch);
	if (ch >= 'a' && ch <= 'z'){
		ch -= 32;
		printf("%c\n", ch);
	}
	else if (ch >= 'A' && ch <= 'Z'){
		ch += 32;
		printf("%c\n", ch);
	}
	else{
		printf("输入的不是大写或者小写字母\n");
	}
	exit(status);
}
if(wait(&status)!=pid){
	printf("wait error! \n");
	exit(0);
}
h_exit(status);   //print status
return 0;
}
