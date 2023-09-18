#include<stdio.h>
#include<stdlib.h>

//Preemptive SJF -
typedef struct ProcessTable {
	int pn;
	int at;
	int bt;
	int btc;	
//	int pr;
	int ct;
	int tt;
	int wt;
} ProcessTable;

void swap(ProcessTable job1[], int i, int j);
void show_ipTable(ProcessTable job1[], int n);
void show_opTable(ProcessTable job1[], int n);
void atSort(ProcessTable job1[], int n);
void btSort(ProcessTable job1[], int n);
void sjf_algo(ProcessTable job1[], int n);

int main() {
	int n;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	
	ProcessTable job1[n];
	
	/*
	int qt;
	printf("Enter Quantum time: ");
	scanf("%d", &qt);
	*/
	
	printf("Enter process details-\n");
	for(int i=0; i<n; i++) {
		printf("\nP%d\n", i+1);
		job1[i].pn = i+1;

		printf("\tEnter Arrival time: ");
		scanf("%d", &job1[i].at);
		
		printf("\tEnter Burst time: ");
		scanf("%d", &job1[i].bt);
		job1[i].btc = job1[i].bt;

		printf("\n");
	}

	show_ipTable(job1, n);

	sjf_algo(job1, n);	
}



void show_ipTable(ProcessTable job1[], int n) {	
	printf("Process Table-\n");
	printf("P.No.\tAT\tBT\n");
	for(int i=0; i<n; i++) {
		printf("%d\t%d\t%d\n", job1[i].pn, job1[i].at, job1[i].bt);	
	}
}


void show_opTable(ProcessTable job1[], int n) {	
	printf("Process Table-\n");
	printf("P.No.\tTT\tWT\n");
	for(int i=0; i<n; i++) {
		printf("%d\t%d\t%d\n", job1[i].pn, job1[i].tt, job1[i].wt);	
	}
}


void swap(ProcessTable job1[], int i, int j) {
	int temp;

	temp = job1[i].pn;
	job1[i].pn = job1[j].pn;
	job1[j].pn = temp;

	temp = job1[i].at;
	job1[i].at = job1[j].at;
	job1[j].at = temp;

	temp = job1[i].bt;
	job1[i].bt = job1[j].bt;
	job1[j].bt = temp;
}


void atSort(ProcessTable job1[], int n) {
	for(int i=0; i<n; i++) {
	  	for(int j=i+1; j<n; j++) {
			if(job1[i].at > job1[j].at) {
				swap(job1, i, j);
			}
		}
	}
}


void btSort(ProcessTable job1[], int n) {
	for(int i=0; i<n; i++) {
	  	for(int j=i+1; j<n; j++) {
			if(job1[i].bt > job1[j].bt) {
				swap(job1, i, j);
			}
		}
	}
}


//Preemptive
void sjf_algo(ProcessTable job1[], int n) {
	
	atSort(job1, n);

/*	
	ProcessTable jobCpy[n];	
	for(int i=0; i<n; i++) {
		jobCpy[i].at = job1[i].at;
		jobCpy[i].bt = job1[i].bt;
	}
*/

	/*
	printf("\n");
	show_ipTable(job1, n);
	printf("\n");
	*/

	//calculate completion time
	int arrived[n];
	int last_at = job1[n-1].at;
	int curr = job1[0].at;
	
	int c=0; int k=0;
	int min=0;
	
	while(curr < last_at) {
		for(int i=0; i<c+1; i++) {
			if(curr > job1[i].at) {
				c++;
				if(job1[min].bt >= job1[i].bt) {
					//k = min;
					min = i;
				}
			}
		}
		
		for(int j=0; j<c+1; j++) {
			if(job1[min].bt > 0) {
				job1[j].bt = job1[j].bt - 1;
				curr = curr + 1;
				break;
			}
			else {
				job1[j].ct = curr;
			}		
		}
		
	}
	
	printf("curr = %d\n", curr);
	//btSort(job1, n);
	for(int i=0; i<n; i++) {
		if(curr >= job1[i].at) {	
			job1[i].ct = curr + job1[i].bt; 	
			curr = job1[i].ct;
		}
		else {
			curr = job1[i].at;
			job1[i].ct = curr + job1[i].bt; 	
			curr = job1[i].ct;
		}

	}

/*
	//show gantz chart
	printf("Gantz Chart:\n");
	for(int i=0; i<n; i++) {
		printf("\tP%d\t", job1[i].pn);
	}
	printf("\n");
	printf("%d\t", job1[0].at);
	for(int i=0; i<n; i++) {
		printf("\t%d\t", job1[i].ct);
	}
	printf("\n");	
*/

	//calculate turn-around time
	float avgTT=0;
	for(int i=0; i<n; i++) {
		job1[i].tt = job1[i].ct - job1[i].at;
		avgTT = avgTT + job1[i].tt;
	}
	avgTT = avgTT/n;

	//calculate waiting time
	float avgWT=0;
	for(int i=0; i<n; i++) {
		job1[i].wt = job1[i].tt - job1[i].btc; 
		avgWT = avgWT + job1[i].wt; 
	}
	avgWT = avgWT/n;

	//show Output table	
	for(int i=0; i<n; i++) {	//sort as per process No.
	  	for(int j=i+1; j<n; j++) {
			if(job1[i].pn > job1[j].pn) {
				swap(job1, i, j);
			}
		}
	}
	printf("\n");
	show_opTable(job1, n);
	printf("\n");

	//result
	printf("Avg TT = %.2f\n", avgTT);
	printf("Avg WT = %.2f\n", avgWT);
}

