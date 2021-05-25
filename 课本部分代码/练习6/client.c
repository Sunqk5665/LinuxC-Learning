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
int main()
{
	int cho;
	FILE *fp_p,*fp_1,*fp_2;
	pid_t pid;
	int pid_w,pid_r;
	int pid_1,pid_2,pid_p;
	char buf_r[BUFSIZ],buf_w[BUFSIZ];
	struct client sxp[]={{1,"abc"},{2,"abc"}};
	printf("请输入要执行的客户端号\n");
	scanf("%d",&cho);
	if(cho==1)
	{
		//执行客户端1 
		c1();

}
	if(cho==2)
	{
		//执行客户端2 
		c2();
}
	return 0;
}
void c1()
{
	int cho;
	FILE *fp_p,*fp_1,*fp_2;
	pid_t pid;
	int pid_w,pid_r;
	int pid_1,pid_2,pid_p;
	char buf_r[BUFSIZ],buf_w[BUFSIZ];
	struct client sxp[]={{1,"abc"},{2,"abc"}};
	if(access(FIFO_1,0) < 0){
        pid_r = mkfifo(FIFO_1,0700);
        if(pid_r<0){
            printf("客户端创建管道失败");
            exit(1);
        }
        printf("私有管道%s创建成功\n",FIFO_1);
    }//写管道创建
   	fp_1 = open(FIFO_1,O_RDWR);
    if(fp_1 < 0){
		printf("打开私有1管道失败");
	}
	printf("*****已打开私有管道1的读端*****\n");//打开私有管道1的读端

    if(access(FIFO_P,0) < 0){
        pid_w = mkfifo(FIFO_P,0700);
        if(pid_w < 0){
            printf("client1创建公共管道失败:");
            exit(2);
        }
        printf("client%s创建公共管道成功\n",FIFO_P);
    }//读管道创建
    fp_p = open(FIFO_P,O_RDWR);
    if(fp_p < 0){
		printf("打开公共管道失败");
	}
	printf("*****已打公共管道的写端*****\n");//打开写管道

	pid=fork();
	if(pid<0){
		printf("子进程创建失败\n");
	}else if(pid==0){
		while(1){
			if(read(fp_1,buf_r,BUFSIZ)==-1){
     			printf("client1读取消息失败");
            }else{
           		if(strlen(buf_r)>0){
               		printf("client1读取信息:%s\n",buf_r);
                    if (strcmp("EOF",buf_r)==0){
                        printf("client1丢失，停止读取\n");
                        break;
                    }
                }else{
                    printf("client1无可读消息\n");
                }    
            }
     	}//while循环
		exit(0);
	}else{
		while(1){
	    	printf("请写入发送给server的信息：");
            scanf("%s",buf_w);
            strcpy(sxp[0].buf,buf_w);
            if(strcmp(buf_w,"client2")==0){
	    		c2();//变换客户端 
				exit(0);
			}
			if(write(fp_p,&sxp[0],sizeof(struct client))==-1){
             	printf("client1发送消息失败");
            }else{
             	printf("client1发送消息:%s\n",buf_w);
                if(strcmp("EOF",buf_w) == 0){       
                    break;
                }
            }
      	}//while循环
	exit(0);
	}
}

void c2()
{
	int cho;
	FILE *fp_p,*fp_1,*fp_2;
	pid_t pid;
	int pid_w,pid_r;
	int pid_1,pid_2,pid_p;
	char buf_r[BUFSIZ],buf_w[BUFSIZ];
	struct client sxp[]={{1,"abc"},{2,"abc"}};
	
	if(access(FIFO_1,0) < 0){
        pid_r = mkfifo(FIFO_2,0700);
        if(pid_r<0){
           	printf("客户端创建管道失败");
            exit(1);
   		}
         printf("私有管道%s创建成功\n",FIFO_2);
    }//写管道创建
    fp_2 = open(FIFO_2,O_RDWR);
    if(fp_2 < 0){
		printf("打开私有管道2失败");
	}
	printf("*****已打开私有管道2的读端*****\n");//打开读管道
    if(access(FIFO_P,0) < 0){
        pid_w = mkfifo(FIFO_P,0700);
        if(pid_w < 0){
            printf("client2创建公共管道失败:");
            exit(2);
        }
        printf("client%s创建公共成功\n",FIFO_P);
    }//读管道创建
    fp_p = open(FIFO_P,O_RDWR);
    if(fp_p < 0){
		printf("打开公共管道失败");
	}
	printf("*****已打开公共管道的写端*****\n");//打开写管道
	pid=fork();
	if(pid<0){
		printf("子进程创建失败\n");
	}else if(pid==0){
		while(1){
			if(read(fp_2,buf_r,BUFSIZ)==-1){
     			printf("client2读取消息失败");
            }else{
           		if(strlen(buf_r)>0){
               		printf("client2读取信息:%s\n",buf_r);
                    if (strcmp("EOF",buf_r)==0){
                        printf("client2丢失，停止读取\n");
                        break;
                    }
                }else{
                    printf("client2无可读消息\n");
                }    
            }
     	}//while循环
		exit(0);
	}else{
		while(1){
	    	printf("请写入发送给server的信息：");
            scanf("%s",buf_w);
            strcpy(sxp[1].buf,buf_w);
            if(strcmp(buf_w,"client1")==0){
	    		c1();//变换客户端 
				exit(0);
			}
			if(write(fp_p,&sxp[1],sizeof(struct client))==-1){
             	printf("client2发送消息失败");
            }else{
             	printf("client2发送消息:%s\n",sxp[1].buf);
                if(strcmp("EOF",buf_w) == 0){       
                    break;
                }
            }
      	}//while循环
	exit(0);
	}
}

