#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define P 10000

void foo();

int main() 
{
	time_t start, end;

        int i=0, start_value=0,pid;

        pid_t idp;

	start=time(0);//we store current time before the creation of processes in variable start 

	printf("Arxiki timi deuteroleptwn %ld \n",start);//we use %ld format in order to print and reperesent time

	while(i<P) //while loop for P processes
	{
		pid=fork(); //we create a child process

		if(pid==0) //the if condition is true only for the child process
                {
               	 	foo(); //each child process executes function foo()

			exit(0); //after that each chid terminates
                }

		i++;
	}

 

	for(i=1;i<=P; i++) //parent process wait for its children to terminate
		waitpid(idp,&start_value,WNOWAIT);

 
	end= time(0);//we store current time after the creation of processes in end variable 

	printf("Teliki timi deuteroleptwn = %ld\n", end);

	printf("Diarkeia ektelesis =%ld sec \n",end-start);//we compute and print the total execution time of the P processes

	float mo=(float)(end-start)/100; //we compute the average execution time of the P processes

	printf("Mesi diarkeia =%f\n",mo); //we print the average execution time of the P processes

	return 0;
}

 
void foo()
{
	int x=0;

	x=x+10;
}


 


