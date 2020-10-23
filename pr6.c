#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h> 
#include <string.h>
#include <pthread.h>

int n;

void *runner(void *arrs)
{
	int *a=(int *)arrs;
	printf("Ascending order\n");
	int i,swap,j;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(a[i]>a[j])
			{
				swap=a[i];
				a[i]=a[j];
				a[j]=swap;
			}
		}
	}
	for(i=0;i<n;i++)
		printf("%d  ",a[i]);
	printf("\n");
	pthread_exit(0);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	printf("enter the size of array\n");
	scanf("%d",&n);
	printf("enter the array elements\n");
	int *arr = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{	
		scanf("%d",&arr[i]);
	}
	pthread_attr_init(&attr);
	pthread_create(&tid,NULL,runner,(void *)arr);
	pthread_join(tid,NULL);
	printf("Descending\n");
	int i,swap,j;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(arr[i]<arr[j])
			{
				swap=arr[i];
				arr[i]=arr[j];
				arr[j]=swap;
			}
		}
	}
	for(i=0;i<n;i++)
		printf("%d  ",arr[i]);
	printf("\n");
	free(arr);
	return 0;
}