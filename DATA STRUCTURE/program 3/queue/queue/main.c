#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int key;
} element;

element queue[MAX];
int rear=-1;
int front=-1;








element queue_empty(void);
element deleteq(int *front, int rear)
{
    if(*front == rear){
        return queue_empty();
    }
    return queue[++(*front)];
}



element queue_empty()
{
    fprintf(stderr,"queue is empty\n");
    element ele ={ -3 };                    ///????
    return ele;                            ///????
}










void print_queue(int front, int rear)
{
    int i;
    for(i=front + 1;i<=rear;i++){
        printf("%3d", queue[i].key);
    }
    printf("\n");
}




void queue_full(void);
void addq(int *rear,element item)
{
    if(*rear == MAX - 1){
        queue_full();
        return;  //退出程式
    }
    queue[++(*rear)] = item;
//    或著這樣也可
//    queue[++(*rear)].key = item.key;
}

void queue_full(){
    fprintf(stderr,"error queue is full");
}





int main()
{
    int i;
    element ele;
    
    
    
    for (i=0;i <= 10;i++){
        ele.key=i;
        addq(&rear,ele);
        printf("ad queue:%3d | ", ele.key);
        print_queue(front,rear);
    }
    
    
    for(i = 0; i <= 15;i++){
        ele = deleteq(&front,rear);
        printf("de queue:%3d | ", ele.key);
        print_queue(front ,rear);
    }
    return  0;
    
}
