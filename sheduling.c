#include<stdio.h>
#define SIZE 20

int queue[SIZE];

int front=0,rear=-1;

int X[2];

typedef struct process {
	int bt,no,at,ct,tat,wt,rbt,p;
}pro;

pro p[10],temp;
int temp1[10];

void fcfs(void);
void sjf(void);
void rr(void);
void pri(void);
int init();
void enqueue(int);
int dequeue(void);
int* initRR(void);

void sort(int n){
	int i ,j;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(p[j].at>p[j+1].at){
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
		temp1[i] = p[i].bt;
	}
	temp1[n-1] = p[n-1].bt;

}


void ct(int n){
	int i;
	p[0].ct = p[0].at + p[0].bt;
	for(i=1;i<n;i++){
			if(p[i].at>p[i-1].ct)
				p[i].ct = p[i].at + p[i].bt;
			else
				p[i].ct = p[i-1].ct + p[i].bt;
	}
}


 void tat(int n){
	int i;
	for(i=0;i<n;i++){
        	p[i].tat = p[i].ct - p[i].at;
        }
}

void tatPri(int n){
	int i;
	for(i=0;i<n;i++){
        	p[i].tat = p[i-1].tat + p[i].bt;
        }
}

void wt(int n){
	int i;
        for(i=0;i<n;i++){ 
                p[i].wt = p[i].tat - p[i].bt;
        }
}


void display(int n){
	
	printf("process|Burst time|Arrival time|Waiting time|Turnaround time\n");
	int i;
	for(i=0;i<n;i++){
		printf("%d | %d | %d | %d | %d \n",p[i].no,p[i].bt,p[i].at,p[i].wt,p[i].tat);
	}
}

void displayPri(int n){
	
	printf("process|Burst time|Arrival time|Priority|Waiting time|Turnaround time\n");
	int i;
	for(i=0;i<n;i++){
		printf("%d | %d | %d | %d | %d | %d \n",p[i].no,temp1[i],p[i].at,p[i].p,p[i].wt,p[i].tat);
	}
}

void fcfs(){
	int n = init();
	sort(n);
	ct(n);
	tat(n);
	wt(n);
	display(n);
}

void sjf(){
	int n = init();
	
	sort(n);

	int i,ready,flag=0;
	p[0].ct = p[0].at + p[0].bt;
	ready = p[0].ct;
	for(i=1;i<n;i++){
		if(p[i].at<=ready){
			int j;
			for(j=i+1;j<n;j++){
				if(p[j].at<=ready && p[j].bt<p[i].bt){
						temp = p[i];
						p[i] = p[j];
						p[j] = temp;
				}
			}
			flag = 1;
		}
		if(flag==1){
			p[i].ct = p[i-1].ct + p[i].bt;
			ready = p[i].ct;
			flag=0;
		}
		else{
			p[i].ct = p[i].at + p[i].bt;
			ready = p[i].ct;
		}
	}
	tat(n);
	wt(n);
	display(n);
}

int init(){
	printf("Enter no of Process: ");
        int n;
        scanf("%d",&n);
        int i;
        for(i=0;i<n;i++){
                printf("Enter the burst time, arival time of process %d: ",i+1);
                scanf("%d %d",&p[i].bt,&p[i].at);
                p[i].no = i + 1;
        }
	return n;
}

int initPri(){
	printf("Enter no of Process: ");
        int n;
        scanf("%d",&n);
        int i;
        for(i=0;i<n;i++){
                printf("Enter the burst time, Priority of process and Arival time %d: ",i+1);
                scanf("%d %d %d",&p[i].bt,&p[i].p,&p[i].at);
                p[i].no = i + 1;
		temp1[i] = p[i].bt;
        }
	return n;
}


int* initRR(){
	printf("Enter no of Process: ");
        int n;
	scanf("%d",&n);
	printf("Enter time quantum: ");
        int t;
        scanf("%d",&t);
        int i;
        for(i=0;i<n;i++){
                printf("Enter the burst time, arival time of process %d: ",i+1);
                scanf("%d %d",&p[i].bt,&p[i].at);
                p[i].no = i + 1;
        }
	X[0] = n;
	X[1] = t;
	return X;
}



void rr(){
	int *x = initRR();
	int n = x[0];
	int t = x[1];
	int y = n;
	int i,j,sum=0,count=0;
	sort(n);
	printf("\n Process No \t\tBurst Time \t\t TAT \t\t Waiting Time");
	for(sum=0,i=0;y!=0;){
		if(temp1[i]<=t && temp1[i]>0){
			sum+=temp1[i];
			temp1[i]=0;
			count = 1;
		}else if(temp1[i]>0){
			temp1[i]-=t;
			sum+=t;
		}
		if(temp1[i]==0 && count==1){
			y--;
			printf("\nProcess No[%d] \t\t %d\t\t\t %d\t\t\t %d",p[i].no,p[i].bt,sum-p[i].at,sum-p[i].at-p[i].bt);
			count=0;
		}
		if(i==n-1){
			i=0;
		}else if(p[i+1].at<=sum){
			i++;
		}else{
			i=0;
		}
	}
}

void pri(){
	int n = initPri();
	sort(n);
	int i ,j,smallest,count=0,time=0,end=0;
	p[9].p=1000;
	for(time=0;count!=n;time++){
		smallest=9;
		for(i=0;i<n;i++){
			if(p[i].at<=time && p[i].p<p[smallest].p && p[i].bt>0){
				smallest=i;
			}	
		}
		p[smallest].bt--;
		if(p[smallest].bt==0){
			count++;
			end=time+1;
			p[smallest].ct=end;
			p[smallest].wt=end-p[smallest].at-temp1[smallest];
			p[smallest].tat=end-p[smallest].at;
		}
	}
	displayPri(n);	

}


void menu(){

	int c;
	do{
	printf("\nChoose any Scheduling algorithm\n1)FCFS\n2)SJF\n3)Round Robin\n4)Priority\n0)End Program :(\nEnter choice: ");
	scanf("%d",&c);
	switch(c){
		case 1: fcfs();break;
		case 2: sjf();break;
		case 3: rr();break;
		case 4: pri();break;
		case 0: break;
		default: "Wrong Input\n"; 
	}
	}while(c!=0);
}


int main(){
	menu();
	
}
