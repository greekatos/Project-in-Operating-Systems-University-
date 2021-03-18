#include <stdio.h>
#include <stdlib.h>

int main()
{
	int pid1;
	int pid2;
	
	pid1 = fork();
	
	if (pid1 < 0)
		printf("Could not create any child\n");
	else
		if (pid1>0)
		{
			printf("1.My PID is %d \n", getpid());
			printf("1. My Parent's PID is %d \n", getppid());
		}
		else
			if (pid1==0)
			{
				printf("2.My PID is %d \n", getpid());
				printf("2.My Parent's PID is %d \n", getppid());
			}
			pid2 = fork();
			
			if (pid2 < 0)
				printf("Could not create any child\n");
			else
				if ((pid1 < 0) && (pid2 < 0))
					kill(pid1,9);
					else 
						if (pid2>0)
						{
							printf("3.My PID is %d \n", getpid());
							printf("3.My Parent's PID is %d \n", getppid());
						}
						else
							if (pid2==0)
							{
								printf("4.My PID is %d \n", getpid());
								printf("4.My Parent's PID is %d \n", getppid());
							}
		
	sleep(20);
	
	return (0);
}

