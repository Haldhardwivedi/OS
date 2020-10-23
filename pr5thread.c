#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <string.h>
#include <pthread.h>

void *runner(void *arrs)
{
	int *param=(int *)arrs;
	if(param[0]==param[1])
	{
		printf("%d\n",param[0]);
	}
	pthread_exit(0);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	int a;
	int b;
	printf("enter the range \n");
	scanf("%d %d",&a,&b);
	for(int i=a;i<=b;i++)
	{	
		int *arr = (int*)malloc(2*sizeof(int));
		int num=i,d,sum=0;
		while (num!=0) 
		{
       		d=num%10;
       		sum=sum+d*d*d;
       	 	num=num/10;
    	}
    	arr[0]=i;
    	arr[1]=sum;
		pthread_attr_init(&attr);
		pthread_create(&tid,NULL,runner,(void *)arr);
		pthread_join(tid,NULL);
		free(arr);
	}
	return 0;
}