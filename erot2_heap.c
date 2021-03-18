#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>

sem_t *mutex;

void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    
    if (l < n && arr[l] > arr[largest]) 
	largest = l; 
  
    
    if (r < n && arr[r] > arr[largest]) 
	largest = r; 
  
    
    if (largest != i) 
    {
	int temp=arr[i];
	arr[i]=arr[largest];
	arr[largest]=temp;
  
	
	heapify(arr, n, largest); 
    } 
} 
  

void heapSort(int arr[], int n) 
{ 
	int i;
	
	for (i = n / 2 - 1; i >= 0; i--) //Κατασκευή Min heap 
		heapify(arr, n, i); 
	
  	// One by one extract an element from heap 
	for (i=n-1; i>=0; i--) 
	{
		//απομακρύνουμε τη μικρότερη τιμή από τη ρίζα του σωρού αι τη βλάζουμε στο τέλος του πίνακα 
		int temp=arr[0];
		arr[0]=arr[i];
		arr[i]=temp;
	  
		
		heapify(arr, i, 0); /*μετατρέπουμε το δεντρο πάλι σε σωρό*/
	}
} 

int main()
{
    	int i, j;
	mutex= sem_open("mut", O_CREAT | O_EXCL, 0644, 0);
 	
 	sem_init(&mutex,0,1) ;  

	int shm = shmget(42, 100 * sizeof (int), IPC_CREAT | 0666); //Δημιουργία shared memory key 42 για καταχώριση 100 ακέραιων

	if (shm < 0)
	{
		perror ("Error in creation of shared memory");
		return 1;
	}
	
	int *sharheap = shmat(shm,NULL,0);/*Βάζω το δείκτη sharheap να δείχνει στη 1η θέση της κοινής μνήμης που αντιπροωπεύεται από την shm */

	if (sharheap < (int *) NULL)
	{
		perror ("Error in shmat in shared memory");
		return 1;
	}

	for (i = 0; i < 100; ++i) /* Create children and make them work */
		if (fork()==0) /*Αν είμαστε σε κάποιο παιδί*/
		{
			sem_wait(&mutex); /*down mutex*/
			
			srand(getpid());/*αρχικοποιούμε τη γεννήτρια παραγωγής τυχαίων αριθμών με το id της τρέχουσας διεργασίας ώστε να παραχθούν διαφορετικές random τιμές*/
			
			sharheap[i]=rand()%getpid();/*εδώ γίνεται η παραγωγή της τυχαίας τιμής και η καταχώριση της στον πίνακα sharheap*/
			
			usleep(getpid());

			heapSort(sharheap,100);
			
			sem_post(&mutex) ;/*up mutex*/

			return 0;
		}

    	
   	for (i = 0; i< 100; ++i) /*H parent process περιμένει τον τερματισμό των 100 παιδιών της */
		wait (&i);
 
	puts("\nFinal SOrted Heap");
    	for (i = 0; i < 100; ++i)
	 	printf("%d\t", sharheap[i]);

    
	shmdt (sharheap); /*διαγραφή της shared memory*/
	shmctl (shm, IPC_RMID, NULL);


    	return 0;
}

 


