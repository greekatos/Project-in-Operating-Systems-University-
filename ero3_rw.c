#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t readmut,writemut;
int store = 0,rcount = 0;

FILE *fptr;

void *reader(void *arg)
{
	sleep(3);

	sem_wait(&readmut);

	rcount = rcount + 1;

	if(rcount==1)
		sem_wait(&writemut);

	sem_post(&readmut);

	fptr = fopen("common.txt","r");

	if(fptr == NULL)
	{
	      printf("Error in Read!");   
	      exit(1); 
	}    
  	fscanf(fptr,"%d",&store);

	printf("\nReader read value %d from file. \n",store);
	  
	fclose(fptr);
	
	sem_wait(&readmut);

	rcount = rcount - 1;

	if(rcount==0)
		sem_post(&writemut);

	sem_post(&readmut);
}

	
void *writer(void *arg)
{
	sem_wait(&writemut);

	store++;

	fptr = fopen("common.txt","w");

	if(fptr == NULL)
	{
	      printf("Error in Write r!");   
	      exit(1); 
	}    
   
	fprintf(fptr,"%d",store);

  	fclose(fptr);

	printf("Data writen by the writer is %d\n",store);

	sleep(1);

	sem_post(&writemut);
}

	
int main()
{
	int i; 

	pthread_t readthreads[5],writethreads[1];

	sem_init(&readmut,0,1);

	sem_init(&writemut,0,1);

	
	for(i=0;i<5;i++)
		pthread_create(&readthreads[i],NULL,reader,(void *)i);

	pthread_create(&writethreads[0],NULL,writer,(void *)i);


	for(i=0;i<5;i++)
		pthread_join(readthreads[i],NULL);

	pthread_join(writethreads[0],NULL);

	return 0;

}


