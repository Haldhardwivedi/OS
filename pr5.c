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
		printf("enter the range a and b  \n");
		int a,b,i,num,sum;
		scanf("%d %d",&a,&b);
		close(fd1[read_end]);
		close(fd2[write_end]);
		write(fd1[write_end],&b,sizeof(b));
		//writing to pipe1 and reading to pipe2
		for(i=a;i<=b;i++)
		{
			write(fd1[write_end],&i,sizeof(i));
			read(fd2[read_end],&sum,sizeof(sum));
			if(sum==i)
				printf("%d\n",i);
		}
		close(fd1[write_end]);
		close(fd2[read_end]);
	}
	else
	{
		int a,sum,b;
		close(fd1[write_end]);
		close(fd2[read_end]);
		read(fd1[read_end],&b,sizeof(b));
		//writing to pipe 1
		while(1)
		{
			read(fd1[read_end],&a,sizeof(a));
			if(a==b)
				break;
			int num=a,d;
			sum=0;
			while(num)
			{
				d=num%10;
				sum=sum+d*d*d;
				num=num/10;
			}
			write(fd2[write_end],&sum,sizeof(sum));
		}
		close(fd1[read_end]);
		close(fd2[write_end]);
	}
	return 0;
}