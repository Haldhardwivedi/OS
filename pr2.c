#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <string.h>

#define BUFFER_SIZE 100
#define read_end 0
#define write_end 1

 int main(int argc, char const *argv[])
{
	char write_msg[BUFFER_SIZE];
	char str1[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];
	int fd1[2];
	int fd2[2];
	pid_t pid;
	if(pipe(fd1)==-1)
	{
		printf("Pipe failed\n");
		return(1);
	}
	if(pipe(fd2)==-1)
	{
		printf("Pipe failed\n");
		return(1);
	}
	pid=fork();
	if(pid<0)
	{
		printf("fork failed\n");
		return(1);
	}
	if(pid>0)
	{
		printf("enter the string 1 \n");
		gets(write_msg);
		close(fd1[write_end]);
		close(fd2[read_end]);
		//reading  to pipe 1
		read(fd1[read_end],read_msg,BUFFER_SIZE);
		close(fd1[read_end]);
		char str[BUFFER_SIZE*2];
		int i;
		for(i=0;i<strlen(write_msg);i++)
			str[i]=write_msg[i];
		int j=i;
		for(i=0;i<strlen(read_msg);i++)
			str[j++]=read_msg[i];
		write(fd2[write_end],str,strlen(str)+1);
		close(fd2[write_end]);
	}
	else
	{
		printf("enter the string 2\n");
		gets(write_msg);
		close(fd1[read_end]);
		close(fd2[write_end]);
		//writing to pipe 1
		write(fd1[write_end],write_msg,strlen(write_msg)+1);
		close(fd1[write_end]);
		char str[BUFFER_SIZE*2];
		read(fd2[read_end],str,BUFFER_SIZE*2);
		printf("concated string is %s\n",str);
		close(fd2[read_end]);
	}
	return 0;
}
