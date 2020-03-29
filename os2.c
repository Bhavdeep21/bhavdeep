#include<stdio.h>
#include<stdlib.h>

struct request
{
    int request_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int last_completion_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
}faculty_queue[100],student_queue[100],query_queue[200];
int cq=0,qno=0,fno=0,sno=0,time_quantum;
void sortStruct(int ty,int at,int bt)
{
    if(ty==1)
    {
        int i=0;
        for(i=0;i<fno;i++)
        {
            if(at<faculty_queue[i].arrival_time)
            {
                for(int j=fno-1;j>=i;j++)
                {
                    faculty_queue[j+1].arrival_time=faculty_queue[j].arrival_time;
                    faculty_queue[j+1].burst_time=faculty_queue[j].burst_time;
                }
                faculty_queue[i].arrival_time=at;
                faculty_queue[i].burst_time=bt;
                faculty_queue[i].remaining_time=bt;
                faculty_queue[i].turnaround_time=0;
                faculty_queue[i].waiting_time=0;
                faculty_queue[i].request_id=1000+fno;
                fno++;
                break;
            }   
        }
        if(i==fno)
        {
            faculty_queue[fno].arrival_time=at;
            faculty_queue[fno].burst_time=bt;
            faculty_queue[fno].remaining_time=bt;
            faculty_queue[fno].turnaround_time=0;
            faculty_queue[fno].waiting_time=0;
            faculty_queue[fno].request_id=1000+fno;
            fno++;
        }
    }
    else if(ty==2)
    {
        int i=0;
        for(i=0;i<sno;i++)
        {
            if(at<student_queue[i].arrival_time)
            {
                for(int j=sno-1;j>=i;j++)
                {
                    student_queue[j+1].arrival_time=student_queue[j].arrival_time;
                    student_queue[j+1].burst_time=student_queue[j].burst_time;
                }
                student_queue[i].arrival_time=at;
                student_queue[i].burst_time=bt;
                student_queue[i].remaining_time=bt;
                student_queue[i].turnaround_time=0;
                student_queue[i].waiting_time=0;
                student_queue[i].request_id=2000+sno;
                sno++;
                break;
            }   
        }
        if(i==sno)
        {
            student_queue[sno].arrival_time=at;
            student_queue[sno].burst_time=bt;
            student_queue[sno].remaining_time=bt;
            student_queue[sno].turnaround_time=0;
            student_queue[sno].waiting_time=0;
            student_queue[sno].request_id=2000+sno;
            sno++;
        }
    }
    else
    {
        printf("thank you");
    }
}
void input()
{
    int n,at,bt,ty=0;
    printf("Welocome\n");
    printf("Enter the Time quanta for each query = ");
    scanf("%d",&time_quantum);
    printf("Enter 1 for faculty 2 for student 0 for exit\n");
    scanf("%d",&ty);
    while(ty!=0)
    {
        printf("Enter time in 2400 hours format. For example - for 10:30 enter 1030\n");
        printf("Enter the arrival time = ");
        scanf("%d",&at);
        if(at<1000 && at>2400)
        {
            printf("Your query is out of the time limit so this query can't be resolved");
            continue;
        }
        else
        {
            at=at-1000;
        }
        printf("Enter the Time needed to solve the query or burst time = ");
        scanf("%d",&bt);
        sortStruct(ty,at,bt);
        printf("Enter 1 for faculty 2 for student 0 for exit\n");
        scanf("%d",&ty);
    }
}

void totalQuery()
{
    int cfno=0,csno=0;
    if(fno!=0 && sno!=0)
    {
        while(cfno<fno && csno<sno)
        {
            if(faculty_queue[cfno].arrival_time==student_queue[csno].arrival_time)
            {
                query_queue[qno]=faculty_queue[cfno];
                qno++;
                query_queue[qno]=student_queue[csno];
                cfno++;
                csno++;
                qno++;
            }
            else if(faculty_queue[cfno].arrival_time>student_queue[csno].arrival_time)
            {
                query_queue[qno]=student_queue[csno];
                csno++;
                qno++;
            }
            else if(faculty_queue[cfno].arrival_time<student_queue[csno].arrival_time)
            {
                query_queue[qno]=faculty_queue[cfno];
                cfno++;
                qno++;
            }
            else;
        }
        if(cfno!=fno && qno!=(fno+sno))
        {
            for(;cfno<fno;cfno++)
            {
                query_queue[qno]=faculty_queue[cfno];
                qno++;
            }
        }
        else if(csno!=sno && qno!=(fno+sno))
        {
            for(;csno<sno;csno++)
            {
                query_queue[qno]=student_queue[csno];
                qno++;
            }
        }
    }
    else if(fno==0 && sno!=0)
    {
        for(int i=0;i<sno;i++)
        {
            query_queue[qno]=student_queue[csno];
            csno++;
            qno++;
        }
    }     
    else if(sno==0 && fno!=0)
    {
        for(int i=0;i<fno;i++)
        {
            query_queue[qno]=faculty_queue[cfno];
            cfno++;
            qno++;
        }
    }
    else
    {
        printf("No queries are there to resolve");
        exit(0);
    }
}
void scheduler()
{
    int counter=0,i=0,time=0;
    while(cq<qno)
    {
            if(query_queue[i].remaining_time <= time_quantum && query_queue[i].remaining_time > 0)
            {
                time = time + query_queue[i].remaining_time;
                query_queue[i].remaining_time = 0;
                query_queue[i].last_completion_time=time;
                counter = 1;
            }
            else if(query_queue[i].remaining_time > 0)
            {
                query_queue[i].remaining_time = query_queue[i].remaining_time - time_quantum;
                time = time + time_quantum;
                query_queue[i].last_completion_time=time;
            }
            if(query_queue[i].remaining_time == 0 && counter == 1)
            {
                cq++;
                query_queue[i].last_completion_time=time;
                query_queue[i].completion_time=time;
                query_queue[i].waiting_time = query_queue[i].waiting_time+ time - query_queue[i].arrival_time - query_queue[i].burst_time;
                query_queue[i].turnaround_time = query_queue[i].turnaround_time + time - query_queue[i].arrival_time;
                counter = 0;
            }
            if(i==qno-1)
            {
                i=0;
            }
            else if(query_queue[i+1].arrival_time <= time)
            {
                int flag=0;
                for(int j=0;j<i+1;j++)
                {
                    if(query_queue[j].last_completion_time<query_queue[i+1].arrival_time && query_queue[j].remaining_time>0)
                    {
                        i=j;
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    i++;
                }
            }
            else if(query_queue[i+1].arrival_time >= time && query_queue[i+1].remaining_time > 0)
            {
                int flag=0;
                for(int j=0;j<i+1;j++)
                {
                    if(query_queue[j].remaining_time > 0)
                    {
                        i=j;
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    time=query_queue[i+1].arrival_time;
                    i++;
                }
            }
            else
            {
                i=0;
            }
    }
    
}

void printer()
{
    printf("\n\n\nSummary of the execution\n\n\n");
    int sum=0,time_spent=0;
    for(int i=0;i<cq;i++)
    {
        printf("Querry Id : %d \nArrival Time : %d \nBurst Time : %d \nCompletion Time : %d \nWaiting Time : %d \nTurnaround Time : %d\n\n",query_queue[i].request_id,query_queue[i].arrival_time+1000,query_queue[i].burst_time,query_queue[i].completion_time+1000,query_queue[i].waiting_time,query_queue[i].turnaround_time);
        sum+=query_queue[i].turnaround_time;
        time_spent+=query_queue[i].burst_time;
    }
    printf("Total number of completed query : %d \nRemaining number of queries are : %d\n\n",cq,qno-cq);
    int avg=sum/cq;
    printf("Total time spent on the query : %d",time_spent);
    printf("\nAverage query time : %d",avg);
    printf("\n\nExecution completed\n");
}
int main()
{
    input();
    totalQuery();
    scheduler();
    printer();
}
