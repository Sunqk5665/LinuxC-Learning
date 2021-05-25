#include<stdio.h>
#include<stddef.h>
#include<unistd.h>
#include<pthread.h>

#define FALSE 0
#define TRUE 1

void readfun();
void writefun();

char buffer[256];
int buffer_has_item =0;
int retflag=FALSE;
pthread_mutex_t mutex;

int main(){
pthread_t reader;
pthread_mutex_init(&mutex,NULL);
pthread_create(&reader,NULL,(void *)&readfun,NULL);
writefun();

}

void readfun(){
while(1){
	if(retflag)
		return;
	pthread_mutex_lock(&mutex);
	if(buffer_has_item==1){
		printf("%s",buffer);
		buffer_has_item=0;
	}
	pthread_mutex_unlock(&mutex);
	}
}


void writefun(){
int i=0;
while(1){
	if(i==10){
		retflag=TRUE;
		return;	
	}
	pthread_mutex_lock(&mutex);
	if(buffer_has_item==0){
		sprintf(buffer,"This is %d\n",i++);
		buffer_has_item=1;
	}
	pthread_mutex_unlock(&mutex);
}
}


