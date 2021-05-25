#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h> 

#define BUFSIZE 89
int main()
{
int fd_open,fd_write,fd_read,fd_close,fd_size;
char iobuffer[BUFSIZE]="write to the file!";
char readbuffer[20];
fd_open = open("/home/snowbird/items/test/test01.c",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
if(fd_open==-1)
	{
		printf("File open error!\n");
	}
else
	{
		printf("File open successful!\n");
	}
fd_write = write(fd_open,iobuffer,BUFSIZE);
if(fd_write==-1)
	{
		printf("File write error!\n");
	}
else
	{
		printf("File write successful!\n");
	}
lseek(fd_open ,0,SEEK_SET);
fd_read = read(fd_open,readbuffer,sizeof(readbuffer));
printf("The read data is : %s\n",readbuffer);

fd_size=lseek(fd_open,0,SEEK_END);
printf("File size is %d\n",fd_size);

return 0;
}