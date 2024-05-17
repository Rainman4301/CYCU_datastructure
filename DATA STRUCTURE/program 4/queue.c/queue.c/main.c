#include <stdio.h>
#include <stdlib.h>


#define IS_EMPTY(ptr) (!(ptr))
#define IS_FULL(ptr) (!(ptr))




typedef struct element{
    int key;
}element;




typedef struct queue* queue_pointer;
typedef struct queue{
    element num;
    queue_pointer link;
}queue;

queue_pointer front = NULL, rear = NULL;



element deleteq(queue_pointer *front);
void free_queue(queue_pointer *queue)
{
    while(*queue){
        deleteq(queue);
    }
}





element deleteq(queue_pointer *front)
{
    queue_pointer temp;                                 ///here   does  {deleteq function of (temp)}   comflict  with { there  addq function  (temp)}
    temp = *front;
    element deleteitem;
    
    if(IS_EMPTY(*front)){
        fprintf(stderr,"The queue is empty");
        exit(1);
    }
    deleteitem = temp -> num;
    *front = temp -> link;
    free(temp);
    
    return deleteitem;
    
}




void print_queue(queue_pointer ptr)
{
    printf("The queue contains :");
    for(;ptr;ptr=ptr->link){
        printf("%4d", ptr->num);
    }
    printf("\n");
}



void addq(queue_pointer *front, queue_pointer *rear, element item)
{
    queue_pointer temp;
    temp = (queue_pointer)malloc(sizeof(queue));
    
    if(IS_FULL(temp)){
        fprintf(stderr,"The memory is full");               /// because here is (addq) function so it will display FULL if there is no space saved
        exit(1);
    }
    
    temp -> num = item;
    temp -> link = NULL;                    /// 迴圈每次建立的 temp 是不同空間的車廂
    
    if(*front){
        (*rear) -> link = temp;
    }
    else{                                   /// *front 指向第一次創立的 temp 空間  *rear 指向隨後創立的 temp 空間
        *front = temp;
    }
        *rear = temp;
    
}




int main ()
{
    int i;
    element item;
    
    for(i=0;i<10;i++){
        item.key =i;
        addq(&front,&rear,item);
        print_queue(front);        /// why using front parameter
        printf("Front: %d rear: %d\n",front->num,rear->num);
    }
    
    for(i=0; i<5;i++){
        item = deleteq(&front);
        print_queue(front);
        printf("Front: %d rear: %d\n",front->num,rear->num);
    }
    
    free_queue(&front);
    return 0;
    
}
