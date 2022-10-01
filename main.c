/*C Program to Implement First Come First Serve (FCFS) CPU Scheduling Algorithm (Non Preemptive Algorithm)*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//structure for CPU process
typedef struct
{
    int process_ID, arrival_Time, cpuBurst_Time;
    int turnAround_time, wating_Time, response_Time;
    int starting_Time, completion_Time;
}process_info;

//QSORT of arrival time (to check which process came 1st)
int compareAt(const void*a,const void*b)
{
    const process_info*x=a;
    const process_info*y=b;
    if(x->arrival_Time < y->arrival_Time)
    {
        return -1;
    }
    else if(x->arrival_Time >= y->arrival_Time)
    {
        return 1;
    }
    return 0;
}

//finding starting time of the process
int max(int a, int b)
{
    return a>b?a:b;
}


//QSORT for process ID (for getting values in order after printing output)
int comparePID(const void*a,const void*b)
{
    const process_info*x=a;
    const process_info*y=b;
    return x->process_ID - y->process_ID;
}

int main()
{
    process_info ps[MAX];
    int n;
    printf("Enter Total number of CPU process : ");
    scanf("%d",&n);
    float sum_Wtime = 0, sum_TATime= 0, sum_RTime = 0;
    int cpu_Idle_Time = 0;
    int lenght_Cycle;
    float cpu_Utilization_time=0;

    for(int i=0; i<n; i++)
    {
        printf("Enter Arrival time of Process %d   : ",i+1);
        scanf("%d",&ps[i].arrival_Time);
        ps[i].process_ID = i+1;
    }

    for(int i=0; i<n; i++)
    {
        printf("Enter CPU Burst Time of Process %d : ",i+1);
        scanf("%d",&ps[i].cpuBurst_Time);
    }

    qsort(ps,n,sizeof(process_info),compareAt);

    //calculation
    for(int i=0; i<n; i++)
    {
        ps[i].starting_Time = (i==0) ? ps[i].arrival_Time : max(ps[i].arrival_Time,ps[i-1].completion_Time);
        ps[i].completion_Time = ps[i].starting_Time + ps[i].cpuBurst_Time;
        ps[i].turnAround_time = ps[i].completion_Time - ps[i].arrival_Time;
        ps[i].wating_Time = ps[i].turnAround_time - ps[i].cpuBurst_Time;
        ps[i].response_Time = (i==0) ? 0 : ps[i-1].completion_Time - ps[i].arrival_Time;

        sum_TATime += ps[i].turnAround_time;
        sum_Wtime += ps[i].wating_Time;
        sum_RTime += ps[i].response_Time;
        cpu_Idle_Time += (i==0) ? 0 : ps[i].starting_Time - ps[i-1].completion_Time;
    }

    lenght_Cycle = ps[n-1].completion_Time - ps[0].arrival_Time;

    printf("\nGantt Chart\n");

    for(int i=0; i<n; i++)
    {
        printf("-------");
    }

    printf("\n");

    for(int i=0; i<n; i++)
    {
        printf("|  P%d  ",ps[i].process_ID);
    }
    printf("|\n");

     for(int i=0; i<n; i++)
    {
        printf("-------");
    }

    printf("\n");
    printf("%d      ",ps[0].arrival_Time);
        for(int i=0; i<n; i++)
    {
        printf("%d     ",ps[i].completion_Time);
    }

    printf("\n\n");

    qsort(ps,n,sizeof(process_info),comparePID);

    printf("\nProcess No\tArrival Time\tCPU Burst Time\tCompletion Time\tTurn Around Time  Waiting Time\tResponse Time\n");

    for(int i=0; i<n; i++)
    {
        printf("    %d\t\t    %d\t\t    %d\t\t    %d\t\t    %d\t\t      %d\t\t    %d\n",ps[i].process_ID,ps[i].arrival_Time,ps[i].cpuBurst_Time,ps[i].completion_Time,ps[i].turnAround_time,ps[i].wating_Time,ps[i].response_Time);
    }

     cpu_Utilization_time = (float)(lenght_Cycle - cpu_Idle_Time)/lenght_Cycle;

     printf("\nAverage Turn Around Time       = %f",sum_TATime/n);
     printf("\nAverage waiting Time           = %f",sum_Wtime/n);
     printf("\nAverage Response Time          = %f",sum_Wtime/n);
     printf("\nThroughput                     = %f",(float)n/lenght_Cycle);
     printf("\nCPU percent Utilization Time   = %f\n",cpu_Utilization_time*100);

     return 0;
}
