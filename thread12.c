//Parallel Matrix Multiplication

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#define MAX 3

int a[MAX][MAX]={{1,2,3},{4,5,6},{7,8,9}};
int b[MAX][MAX]={{1,2,3},{4,5,6},{7,8,9}};
int c[MAX][MAX]={0};

struct v
{
	int i;		//row
	int j;		//column
};

void * Matrix_mult(void  *arg)
{
	struct v *data=arg;	//the structure that holds our data
	int i= data->i;
	int j= data->j;
	int k;
	for(k=0;k<MAX;k++)
	{
		c[i][j]=c[i][j]+a[i][k]*b[k][j];
	}
}
	
int main(int argc, char *argv[])
{
	int i,j,k;
	pthread_t tid[MAX][MAX];

	// we have to create MAX*MAX worker threads
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			struct v *data=(struct v*)malloc(sizeof(struct v));
			data->i=i;
			data->j=j;
			// now create the thread passing it data as a parameter	
			// set of thread attributes
			pthread_attr_t attr;	
			// get the default attributes
			pthread_attr_init(&attr);	
			//create thread
			
			pthread_create(&(tid[i][j]),&attr,Matrix_mult,data);
			// make sure parent waits for all thread to complete
			pthread_join(tid[i][j],NULL);
			
		}
	}
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
}
