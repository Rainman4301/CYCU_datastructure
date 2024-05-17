#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

typedef struct {
    int key;
    /* other data */
} element;

element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;




void queue_full(int *rear) {
    *rear = (*rear + MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE;
    printf("f:%d, r:%d\n", front, *rear);
    fprintf(stderr, "error: queue is full\n");
}


/* add an item to the queue */
void addq(int front, int *rear, element item) {
    *rear = (*rear + 1) % MAX_QUEUE_SIZE;
    if  (front == *rear) {
        queue_full(rear); /* reset rear and print error */
        return;
    }
    queue[*rear] = item;
}

/* remove front element from the queue and put it in item */
element deleteq (int *front, int rear) {
    element item;
    item.key = -1;
    if (*front == rear){
        return item;
    }
    *front = (*front + 1) % MAX_QUEUE_SIZE;
    return queue[*front];
}


void print_queue(int front, int rear) {
    int i = (front + 1)%MAX_QUEUE_SIZE;
    
    
    while (i != (rear+1)%MAX_QUEUE_SIZE) {
        printf("%-3d", queue[i].key);
        if(i == MAX_QUEUE_SIZE - 1){
            i=0;
            continue;
        }
        i++;
    }
    printf("\n");
    printf("Front: %d  rear: %d\n\n",front,rear);
}

int main() {
    int i;
    element ele;

    for (i = 0; i < 13; i++) {
        ele.key = i ;
        addq(front, &rear, ele);
        printf("adqueue:%3d | ", ele.key);
        print_queue(front, rear);
    }

    for (i = 0; i < 12; i++) {
        ele = deleteq(&front, rear);
        printf("dequeue:%3d | ", ele.key);
        print_queue(front, rear);
    }
    
    
    for (i = 0; i < 7; i++) {
        ele.key = i ;
        addq(front, &rear, ele);
        printf("adqueue:%3d | ", ele.key);
        print_queue(front, rear);
    }
    
    
    for (i = 0; i < 5; i++) {
        ele = deleteq(&front, rear);
        printf("dequeue:%3d | ", ele.key);
        print_queue(front, rear);
    }
    
    
    
//    printf("Front: %d  rear: %d\n",front,rear);
    return 0;
}
