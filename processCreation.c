/*
Press v (lowercase) to enter visual mode. 
This will start selecting from where your cursor is.

Press V (uppercase) to enter visual line mode. 
This will select the entire line.

Press CTRL+V to enter visual block mode.

Move your cursor to the end of where you want to copy or cut.
Press y to copy. 
Press d to cut 

Move the cursor to where you want to paste your selection.
Press P (uppercase) to paste before your cursor. 
Press p (lowercase) to paste after your cursor.
*/

/*
 * ctrl+h backspace
 * ctrl+j next line
*/


#include<stdio.h>
#include<stdlib.h>	//malloc
#include<ctype.h>	
#include<unistd.h>	//getpid()=get curr process pid, getppid()=get curr processs's Parent pid 
#include<sys/types.h> 	//for pid_t, declare process_id type variable
#include<sys/wait.h>	//to call wait() function

void asc(int*, int); 	//ascending
void dsc(int*, int);	//descending

int main() {
	//int a=0, b; is possible
	int *a, n, i;	//a* array pointer
	pid_t pid;	//process id variable -> pid
		
	printf("\nEnter the no of array elements: ");
	scanf("%d", &n);
	a = (int*)malloc(n*sizeof(int));	//assigning (int)memory to array pointer
	
	printf("\nEnter the array elements: ");
	for(int i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}

	//fork() creates new child process, concurrently runs the same process written under it again 
	//if fork() called n times,	process runs 2^n times
	// -ve:		fail	
	// 0: 		success return to Pchild
	// +ve:		return to Pparent, contain pid of newly created Pchild	
	pid = fork();
	
	if(pid < 0) {
		perror("Fork error");	//prints custom msg before actual error msg
	}
	else if(pid == 0) {
		printf("\nChild process id: %ld", (long)getpid()); 
	}
	else {
		printf("\nParent process id: %ld", (long)getpid()); //if child not created get pid of parent
	}


	switch(pid) {
		case -1:
			printf("\nFork Error\n");
			exit(-1);

		case 0:
			printf("\nChild executes...\n");
			//system("ps -elf");	//ps -elf = show all process with complete info
			asc(a,n);	//arrange array in ascending order
			exit(pid);

		default:
			wait(NULL);	//toggle for Zombie process (child not removed from processTable after execution)
					//wait() execute all child process, removes Zombie
			printf("\nParent executes...\n");
			dsc(a,n); 	//arrange array in descending order
			exit(pid);
			//system("ps -elf");
			// https://www.xitalogy.com/linux-unix/2020/02/22/ps-elf-filter-results-effectively-and-see-if-a-linux-process-is-running.html
			
	}

}

void asc(int *a, int n) {
	int i, j, temp;
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {		//OR for j=0 j<n-i-1
			if(a[i]>a[j]) {
				temp = a[i];	//temp = a[j]
				a[i] = a[j];	//a[j] = a[j+1]	
				a[j] = temp;	//a[j] = temp
			}
	
		}
	}

	printf("\nArray in ascending order is: \n");
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}

	printf("\n\n\n");
}


void dsc(int *a, int n) {
        int i, j, temp;
        for(i=0; i<n; i++) {
                for(j=i+1; j<n; j++) {          //OR for j=0 j<n-i-1
                        if(a[i]<a[j]) {
                                temp = a[i];    //temp = a[j]
                                a[i] = a[j];    //a[j] = a[j+1]
                                a[j] = temp;	//a[j] = temp
                     	}
                }
        }

        printf("\nArray in descending order is: \n");
        for(i=0; i<n; i++) {
                printf("%d ", a[i]);
        }

        printf("\n\n\n");
}
