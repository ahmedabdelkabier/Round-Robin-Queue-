#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *name ;
    int starting_time ;
    int remaining_time;

} process;

typedef struct node
{
    process data;
    struct node * next;

} node;

typedef struct
{
    node *front;
    node *rear;

} queue;

node*newNode(process val){
    node*n=malloc(sizeof(node));
    n->data=val;
    n->next=NULL;
    return n;
}

queue* init()
{
    queue *q=malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isEmpty(queue *q)
{
    if (q->front==NULL)
    {
        return 1 ;
    }
    return 0 ;
}

process dequeue(queue*q)
{
    process a ;
    if(q->front==NULL)
    {
        printf("the queue is empty!!");
        return a ;
    }
    else
    {
        a=q->front->data;
        q->front=q->front->next;
        return a ;
    }
}

void enqueue(queue*q,process val){
    node*n=newNode(val);
    if(q->front==NULL)
    {
        q->front=q->rear=n;
    }
    else{
        q->rear->next=n;
        q->rear=n;
    }
}

void destroy (queue * q)
{
    free(q);
}

void RoundRobin(char* filename){
    int i=0;
    char c;
    char *z;
    int time;
    process arr[100];
    FILE*f=fopen(filename,"r");
    int counter=0;

  while (c != EOF)
    {
        c = fgetc(f);
        if ( c == '\n')
            counter++;
    }

    fseek(f,0,0);

      z=malloc(100);
    fgets(z,100,f);
    int len=strlen(z);
    while(z[len] != '=')
    {
        len--;
    }

    time=atoi(&z[len+1]);
    while(fgets(z,100,f)!=NULL)
    {
        char*token=strtok(z," ");
        process process;
        process.name=_strdup(token);
        token=strtok(NULL," ");
        process.starting_time=atoi(token);
        token=strtok(NULL," ");
        process.remaining_time=atoi(token);
        arr[i]=process;
        i++;
    }
    queue*q=init();

    for(int j=0;j<time;j++)
    {
        for(int k=0;k<counter;k++)
        {//printf("test");
            if(arr[k].starting_time==j)
                enqueue(q,arr[k]);
        }
        if(isEmpty(q))
            printf("idle (%d-->%d)\n",j,j+1);
        else
        {
            //printf("testtest");
            process tem=dequeue(q);
            if(tem.remaining_time==1)
            {
                printf("%s(%d-->%d) aborted %s\n",tem.name,j,j+1,tem.name);
                free(tem.name);
            }
            else{
                //printf("testtesttest4");
                printf("%s(%d-->%d)\n",tem.name,j,j+1);
                tem.remaining_time--;enqueue(q,tem);
                }
        }
    }
}

int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
