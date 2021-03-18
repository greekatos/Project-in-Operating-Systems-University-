#include <stdio.h>

#include <stdlib.h>

 
int main()

{
	int i,pid=fork(); //here we create first child process

	if(pid!=0)//this is true only for the initial parent process
        {
		printf("Process id %d,\t\tIts parent id %d,\tIts Child id %d\n", getpid(),getppid(),pid);//we print process id, its parent id and its child id in order to ensure that each child generates a new one

               	wait(0);//each parent process waits the termination of its child before it terminates itself
        }

	for(i=2; i<=10; i++) //this for i sbeing executed 9 times in order to create 9 children
        {
		if(pid==0) //this if is true in each children
		{
			pid=fork(); //each children generates a new one

                        if(pid!=0)//this is true for each nes parent process
			{
				printf("Process id %d,\t\tIts parent id %d,\tIts Child id %d\n", getpid(),getppid(),pid);//we print process id, its parent id and its child id in order to ensure that each child generates a new one

			       	wait(0); //each parent process waits the termination of its child before it terminates itself
			}
                               
                }

	}

	return 0;
}

