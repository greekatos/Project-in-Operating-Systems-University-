#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h> 

sem_t *shmaforos1, *shmaforos2, *shmaforos3, *shmaforos4;


int main()
{

                shmaforos1 = sem_open ("shmafor1", O_CREAT | O_EXCL, 0644,0);

 

                shmaforos2 = sem_open ("shmafor2", O_CREAT | O_EXCL, 0644,0); 

 

                shmaforos3 = sem_open ("shmafor3", O_CREAT | O_EXCL, 0644,0);

 

                shmaforos4 = sem_open ("shmafor4", O_CREAT | O_EXCL, 0644,0); 

 

                if (fork() > 0)
                {

                                puts("Process P1 starts\n");

                                system("pwd");

                                sem_post(shmaforos1);

                                wait(NULL);

                }

 

                else
                {

                                puts ("Process P2 starts \n");
                                system("pwd");

                                sem_post(shmaforos2); 

                                exit(0);

                }



                if (fork() > 0)
                {

                                sem_wait (shmaforos1);

                                sem_wait (shmaforos2);

                                puts("Process P3 starts \n");

                                system("pwd");

                                sem_post (shmaforos3);

                                sem_post (shmaforos4);

                                wait(NULL);

                }

                else
                {

                                sem_wait (shmaforos3);

                                puts ("Process P4 starts \n");

                                system("pwd");

                                exit(0);

                }


                if (fork()>0)
                {

                                sem_wait (shmaforos4);

                                puts ("Process P5 starts \n");


                                system("pwd");

                                wait(NULL);

 

                                sem_unlink("shmafor1"); 

                                sem_close(shmaforos1);  

 

                                sem_unlink("shmafor2");   

                                sem_close(shmaforos2); 

 

                                sem_unlink("shmafor3"); 

                                sem_close(shmaforos3);

 

                                sem_unlink("shmafor4"); 

                                sem_close(shmaforos4);

                }

}

 


