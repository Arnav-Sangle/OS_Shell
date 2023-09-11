#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<sys/types.h>

struct Process {
	int pn;
	int at;
	int bt;
	int ct;
	int tt;
	int wt;
};

void swap(struct Process pTable[], int i, int j);
void show_ipTable(struct Process pTable[], int n);
void show_opTable(struct Process pTable[], int n);
void fcfs_Algo(struct Process pTable[], int n);

void main() {
	int n;

	printf("Enter no. of processes: ");
	scanf("%d", &n);

	struct Process pTable[n];
	//pTable = (struct Process *)malloc(n*sizeof(struct Process*));

	
	printf("\nEnter process details-\n\n");
	for(int i=0; i<n; i++) {
		printf("P%d\n", i+1);
		pTable[i].pn = i+1;

		printf("\tEnter Arrival time: ");
		scanf("%d", &pTable[i].at);
		
		printf("\tEnter Burst time: ");
		scanf("%d", &pTable[i].bt);

		printf("\n");
	}
	
	show_ipTable(pTable, n);
	fcfs_Algo(pTable, n);

}




void show_ipTable(struct Process pTable[], int n) {	
	printf("Process Table-\n");
	printf("P.No.\tAT\tBT\n");
	for(int i=0; i<n; i++) {
		printf("%d\t%d\t%d\n", pTable[i].pn, pTable[i].at, pTable[i].bt);	
	}
}


void show_opTable(struct Process pTable[], int n) {	
	printf("Process Table-\n");
	printf("P.No.\tTT\tWT\n");
	for(int i=0; i<n; i++) {
		printf("%d\t%d\t%d\n", pTable[i].pn, pTable[i].tt, pTable[i].wt);	
	}
}


void swap(struct Process pTable[], int i, int j) {
	int temp;

	temp = pTable[i].pn;
	pTable[i].pn = pTable[j].pn;
	pTable[j].pn = temp;

	temp = pTable[i].at;
	pTable[i].at = pTable[j].at;
	pTable[j].at = temp;
	
	temp = pTable[i].bt;
	pTable[i].bt = pTable[j].bt;
	pTable[j].bt = temp;
}


void fcfs_Algo(struct Process pTable[], int n) {
	//sort as per Arrival Time
	for(int i=0; i<n; i++) {
	  	for(int j=i+1; j<n; j++) {
			if(pTable[i].at > pTable[j].at) {
				swap(pTable, i, j);
			}
		}
	}
	printf("\n");
	show_ipTable(pTable, n);
	printf("\n");

	//calculate completion time
	int curr = pTable[0].at;
	int i=0;	
	for(int i=0; i<n; i++) {
		if(curr >= pTable[i].at) {	
			pTable[i].ct = curr + pTable[i].bt; 	
			curr = pTable[i].ct;
		}
		else {
			curr = curr+1;
			i = i - 1;
		}
	}
	
	//show gantz chart
	for(int i=0; i<n; i++) {
		printf("%d ", pTable[i].ct);
	}

	//calculate turn-around time
	float avgTT=0;
	for(int i=0; i<n; i++) {
		pTable[i].tt = pTable[i].ct - pTable[i].at;
		avgTT = avgTT + pTable[i].tt;
	}
	avgTT = avgTT/n;

	//calculate waiting time
	float avgWT=0;
	for(int i=0; i<n; i++) {
		pTable[i].wt = pTable[i].tt - pTable[i].bt; 
	}
	avgWT = avgWT/n;

	//show Output table	
	printf("\n");
	show_opTable(pTable, n);
	printf("\n");

	//result
	printf("Avg TT = %.2f\n", avgTT);
	printf("Avg WT = %.2f\n", avgWT);
}
