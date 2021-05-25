#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define FIFO_1 "FIFOPrivate1"
#define FIFO_2 "FIFOPrivate2"
#define FIFO_P "FIFOPublic"

struct client{
	int num;
	char buf[BUFSIZ];
};	
void c1();
void c2();
void choose();
int main()
{
	FILE *fp_1,*fp_2,*fp_p;
	pid_t pid;
	int pid_1,pid_2,pid_p;
	char buf_w[BUFSIZ],buf_r[BUFSIZ];
	int cho;
	struct client sxp[]={{1,"abc"},{2,"abc"}};
	pid=fork();
	if(pid<0){
		printf("子进程创建失败\n");
	}else if(pid==0){
		printf("请输入0启动程序\n");
		scanf("%d",&cho);
		if(cho==0){
			printf("打开客户端1时输入client1可打开客户端1!\n打开客户端2时输入client2可打开客户端2!\n输入menu可选择客户端！\n");
			choose();
		}

	}else{
   		if(access(FIFO_1,0) < 0){
        	pid_p = mkfifo(FIFO_P,0700);
        	if(pid_p<0){
            	printf("客户端创建读管道失败");
            	exit(1);
        	}
        	printf("管道%s创建成功\n",FIFO_P);
    	}//读管道创建
    	fp_p = open(FIFO_P,O_RDWR);
    	if(fp_p < 0){
			printf("打开公共管道的写端失败");}
			printf("*****已打开公共管道的写端*****\n");//打开读管道
			while(1){
				if(read(fp_p,&sxp,sizeof(struct client)) == -1 ){
					printf("server读取公共端消息失败");
            	}else{
                 	if( sxp[0].num == 1 ){
                    	printf("服务端收到client1的信息:%s\n",sxp[0].buf);
						memset(sxp[0].buf,0,BUFSIZ);
						sxp[0].num=0;
                	}
					if( sxp[0].num == 2 ){
                    	printf("服务端收到client2的信息:%s\n",sxp[0].buf);
						memset(sxp[0].buf,0,BUFSIZ);
						sxp[0].num=0;
                	}
            	}
		
        	}//while循环
		exit(0);
	}
	return 0;
}
void choose()
{
	int cho;
	printf("请输入想要发送的客户端号\n");
	scanf("%d",&cho);
	if(cho==1){
		c1();
	}
	if(cho==2){
		c2();
	}
}
void c1()
{ 
	FILE *fp_1,*fp_2,*fp_p;
	pid_t pid;
	int pid_1,pid_2,pid_p;
	char buf_w[BUFSIZ],buf_r[BUFSIZ];
	int cho;
	if(access(FIFO_1,0) < 0){
		pid_1 = mkfifo(FIFO_1,0700);
        if(pid_1 < 0){
        	printf("server创建私有管道1失败:");
            exit(1);}
        	printf("私有管道%s创建成功\n",FIFO_1);
   		}//写管道创建
		fp_1 = open(FIFO_1,O_RDWR);
		if(fp_1 < 0){
			printf("打开私有管道1的写端失败");}
			printf("*****已打开私有管道1的写端*****\n");//打开写管道
			while(1){
				scanf("%s",buf_w);
				if(strcmp(buf_w,"client2")==0){
					c2();
				}
				if(strcmp(buf_w,"menu")==0){
					choose();
				}
				if(write(fp_1,buf_w,strlen(buf_w)+1)==-1){
					printf("写入client1信息失败!\n");
				}else{
					printf("server发送给client1消息为：%s\n",buf_w);	
				}
			}//while循环
	exit(0);
}
void c2()
{
	FILE *fp_1,*fp_2,*fp_p;
	pid_t pid;
	int pid_1,pid_2,pid_p;
	char buf_w[BUFSIZ],buf_r[BUFSIZ];
	int cho;
	if(access(FIFO_2,0) < 0){
		pid_2 = mkfifo(FIFO_2,0700);
        if(pid_2 < 0){
            printf("server创建私有管道2失败:");
            exit(1);}
        	printf("私有管道%s创建成功\n",FIFO_2);
   		}//写管道创建
		fp_2 = open(FIFO_2,O_RDWR);
		if(fp_2 < 0){
			printf("打开私有管道2的写端失败");}
			printf("*****打开私有管道2的写端*****\n");//打开写管道
			while(1){
				scanf("%s",buf_w);
				if(strcmp(buf_w,"client1")==0){
					c1();
				}
				if(strcmp(buf_w,"menu")==0){
					choose();
				}
				if(write(fp_2,buf_w,strlen(buf_w)+1)==-1){
					printf("写入client2信息失败!\n");
				}else{
					printf("server发送给client2消息为：%s\n",buf_w);
			
				}
			}//while循环
	exit(0);
}
