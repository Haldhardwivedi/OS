#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <string.h>

#define BUFFER_SIZE 100
#define read_end 0
#define write_end 1


void substring(char str[], int n) 
{
    for (int len = 1; len <= n; len++) 
    {    
        for (int i = 0; i <= n - len; i++) 
        {
            int j = i + len - 1;            
            for (int k = i; k <= j; k++) 
                printf("%c",str[k]);
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
	char write_msg[BUFFER_SIZE];
	char str1[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];
	int fd1[2];
	pid_t pid;
	if(pipe(fd1)==-1)
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
		printf("enter the string  \n");
		gets(write_msg);
		close(fd1[read_end]);
		//writing to pipe 1
		write(fd1[write_end],write_msg,strlen(write_msg)+1);
		close(fd1[write_end]);
	}
	else
	{
		close(fd1[write_end]);
		//reading  to pipe 1
		read(fd1[read_end],read_msg,BUFFER_SIZE);
		close(fd1[read_end]);
		//generates all the substring of the given string 
		substring(read_msg,strlen(read_msg));
	}
	return 0;
}