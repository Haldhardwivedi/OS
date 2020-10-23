#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <string.h>

#define BUFFER_SIZE 100
#define read_end 0
#define write_end 1


char reversed(char *str)
{
	char newstr[BUFFER_SIZE];
	int i,j=0;
	for(i=strlen(str)-1;i>=0;i--)
	{
		newstr[j++]=str[i];
	}
	for(i=0;i<j;i++)
	{
		str[i]=newstr[i];
	}
}


 int main(int argc, char const *argv[])
{
	char write_msg[BUFFER_SIZE];
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
		printf("enter the string to get reversed and palindrome check \n");
		gets(write_msg);
		close(fd1[read_end]);
		close(fd2[write_end]);
		//writing to pipe 1
		write(fd1[write_end],write_msg,strlen(write_msg)+1);
		close(fd1[write_end]);
		read(fd2[read_end],read_msg,BUFFER_SIZE);
		close(fd2[read_end]);
		printf("reversed string is %s\n",read_msg);
		if(strcmp(read_msg,write_msg)==0)
			printf("given string is palindrome\n");
	}
	else
	{
		close(fd1[write_end]);
		close(fd2[read_end]);
		//writing to pipe 1
		read(fd1[read_end],read_msg,BUFFER_SIZE);
		close(fd1[read_end]);
		reversed(read_msg);
		write(fd2[write_end],read_msg,strlen(read_msg)+1);
		close(fd2[write_end]);
	}
	return 0;
}