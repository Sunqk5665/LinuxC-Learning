#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>

int main(int argc,char*argv[]){
	if(argc!=2){
	printf("give me a pathname\n");
	return 1;
}
	int s = mkdir(argv[1],S_IRWXU|S_IRWXG|S_IRWXO);
	if(s<0){
	printf("mkdir failed\n");
	return 2;
}
	else{
	printf("mkdir successed\n");
}
	int w = chdir(argv[1]);
	if(w<0){
	printf("chdir failed\n");
	return 3;
}
	else{
	printf("chdir successed\n");	
}
	char *path = "text1";
	creat(path,S_IRWXU|S_IRWXG|S_IRWXO);
	int q = chdir("..");
	if(q<0){
	printf("chdir failed\n");
	return 6;
}else{
	printf("chdir successed again\n");
}
	DIR*dp;
	if((dp = opendir(argv[1]))==NULL){
	printf("opendir failed\n");
	return 4;
}	else{
	printf("opendir successed\n");
}
	struct dirent *print;
	if((print=readdir(dp))==0){
	printf("readdir failed\n");
	return 5;
}
else{
	printf("readdir successed\n");
}
printf("%s\n",print->d_name);
printf("%ld\n",print->d_ino);
closedir(dp);
return 0;
}
