#include<stdio.h>
#include<sys/types.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void asc(int* , int);
void dsc(int*, int);

int main() {
	int *a, n, i;
	pid_t pid;

	printf("\nEnter the no of array elements: ");
	scanf("%d", &n);
	a = (int*)malloc(n*sizeof(int));
	
	printf("\nEnter the array elements: ");
	for(int i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}

	pid = fork();
	if(pid < 0) {
		perror("Fork error");	// perror --> error msg during process
	}
	else if(pid == 0) {
		printf("Child process id: %ld", (long)getpid());
	}
	else {
		printf("Parent process id: %ld", (long)getpid());
	}


	switch(pid) {
	
		case -1:
			printf("\nFork Error\n");
			exit(-1);

		case 0:
			printf("Child executes...\n");

			//system("ps -elf");
			asc(a,n);
			exit(pid);
		
		default:
		       wait(NULL);    //toggle for zombie process
			printf("\nParent executes...");
	 		dsc(a, n);
			system("ps -elf");
			exit(pid);
			//system("ps -elf");		
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

	printf("\n");
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

        printf("\n");
}
