#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(ptr) (!(ptr))
#define IS_FULL(ptr) (!(ptr))

typedef struct {
    int key;
    /* other data */
} element;

typedef struct queue *queue_pointer;
typedef struct queue {
    element item;
    queue_pointer link;
} queue;

queue_pointer front = NULL, rear = NULL;

/* add an element to the rear of the queue */
void addq(queue_pointer *front, queue_pointer *rear, element item) {
    queue_pointer temp = (queue_pointer)malloc(sizeof(queue));
    if (IS_FULL (temp)) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->item = item;
    temp->link = NULL;
    if (*front) (*rear)->link = temp;
    else *front = temp;
    *rear = temp;
}

/* delete an element from the queue */
element deleteq(queue_pointer *front) {
    queue_pointer temp = *front;
    element item;
    if (IS_EMPTY(*front)) {
        fprintf (stderr, "The queue is empty\n");
        exit(1);
    }
    item = temp->item;
    *front = temp->link;
    free(temp);
    return item;
}

void print_queue(queue_pointer ptr) {
    printf("The queue contains: ");
    for (; ptr; ptr = ptr->link)
        printf("%4d", ptr->item.key);
    printf("\n");
}

void free_queue(queue_pointer *queue) {
    while (*queue) {
        deleteq(queue);
    }
}

int main() {
    int i;
    element item;

    for (i = 0; i < 10; i++) {
        item.key = i ;
        addq(&front, &rear, item);
        print_queue(front);
    }

    for (i = 0; i < 5; i++) {
        item = deleteq(&front);
        print_queue(front);
    }

    free_queue(&front);
    return 0;
}

