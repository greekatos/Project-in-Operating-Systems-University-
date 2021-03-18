#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <semaphore.h>

#include <fcntl.h>

typedef sem_t Semaphore;

Semaphore *shmafor1, *shmafor2, *shmafor3, *shmafor4, *shmafor5, *shmafor6, *shmafor7;


int main()
{

	shmafor1 = sem_open ("shmafor1", O_CREAT | O_EXCL, 0644, 0);

	shmafor2 = sem_open ("shmafor2", O_CREAT | O_EXCL, 0644, 0);

	shmafor3 = sem_open ("shmafor3", O_CREAT | O_EXCL, 0644, 0);

	shmafor4 = sem_open ("shmafor4", O_CREAT | O_EXCL, 0644, 0);

	shmafor5 = sem_open ("shmafor5", O_CREAT | O_EXCL, 0644, 0);

	shmafor6 = sem_open ("shmafor6", O_CREAT | O_EXCL, 0644, 0);

	shmafor7 = sem_open ("shmafor7", O_CREAT | O_EXCL, 0644, 0);


	if (fork() > 0)
	{

		puts("Process d1 starts\n");

		system("pwd");

		sem_post (shmafor1);

		sem_post (shmafor2);

		wait(NULL);

	}

	else
	{

		sem_wait (shmafor1);

		puts("Process d2 starts \n");

		system("date");

		sem_post (shmafor3);

		sem_post (shmafor4);

		exit(0);

	}

	 

	if (fork() > 0)
	{
		sem_wait (shmafor2);

		puts("Process d3 starts \n");

		system("ps");

		sem_post (shmafor5);

		sem_post (shmafor6);

		puts ("Process d4 starts \n");

		system("ls");

		sem_post (shmafor7);

		exit(0);

	}

	 

	if (fork()>0)
	{

		sem_wait (shmafor4);

		sem_wait (shmafor5);

		puts ("Process d5 starts \n");

		system("date");

		wait(NULL);

		 

		sem_unlink("shmafor1");

		sem_close(shmafor1);

		 

		sem_unlink("shmafor2");

		sem_close(shmafor2);

		 

		sem_unlink("shmafor3");

		sem_close(shmafor3);

		 

		sem_unlink("shmafor4");

		sem_close(shmafor4);

		 

		sem_unlink("shmafor5");

		sem_close(shmafor5);

		 

		sem_unlink("shmafor6");

		sem_close(shmafor6);

		 

		sem_unlink("shmafor7");

		sem_close(shmafor7);

	}

	else
	{

		sem_wait (shmafor7);

		sem_wait (shmafor6);

		puts ("Process d6 starts \n");

		system("who");

		exit(0);

	}

}

 


