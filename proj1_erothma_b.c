#include <stdio.h>

#include <stdlib.h>

 
int main()
{
	int i,prid;

	for (i=1; i<=10;  i++)
        {
		prid=fork(); //create a child process that runs concurrently with parent process

                if(prid==0) //this condition is true only for child process
		{
			printf("%d Child with id %d from Parent %d\n",i,getpid(),getppid());//Child process prints its ID and its parent id
			exit(0); //child process terminates in order to create all processes from parent
                }

         }

         for(i=1; i<=10; i++)//Parent process waits first for the termination of its children and after that terminates itself
              wait(0);

	return 0;

}
