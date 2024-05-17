#include <stdio.h>
#include <stdlib.h>


#define IS_FULL(ptr) (!(ptr))


typedef struct list_node* list_pointer;
typedef struct list_node{
    int data;
    list_pointer link;
}list_node;






void free_list(list_pointer *list)
{
    list_pointer p,q;
    
    if(list){
        p = (*list) -> link;
        while (p != *list){
            q = p;
            p = p-> link;
            free(q);
        }
        free(*list);
        *list = NULL ;
    }
}





void print_list(list_pointer ptr)
{
    list_pointer temp;
    if(ptr){
        temp = ptr;
        
        do{
            printf("%4d", temp -> data);
            temp = temp -> link;
        }while(temp != ptr);
        
        printf("\n");
    }
}






int length(list_pointer ptr)
{
    list_pointer temp;
    int count = 0;
    
    if(ptr){
        temp = ptr;
        do{
            count ++;
            temp = temp -> link;
        }while(temp != ptr);
        
    }
    return count;
}




void insert_front(list_pointer *ptr, list_pointer node)     
{
    if(!(*ptr)){
        *ptr = node;
        node -> link =node;
    }
    else{
        node -> link = (*ptr) -> link;
        (*ptr) -> link =node;
    }
}



 

list_pointer new_node(void)
{
    list_pointer temp = (list_pointer)malloc(sizeof(list_node));
    
    if(IS_FULL(temp)){
        fprintf(stderr, "The memory have been full");
        exit(1);
    }
    
    temp -> data = 0;
    temp -> link = NULL;
    
    return temp;
}





int main()
{
    int i;
    list_pointer a = NULL, p = NULL;
    
    p = new_node();
    p -> data = 10;
    
    insert_front(&a,p);
    
    for( i=5; i>=2; i-- ){
        p = new_node();
        p -> data = i*10;
        insert_front(&a, p);
    }
    

//    printf("a: %d\n", a->data);
    
    printf("a length (%d): ", length(a));
    
    print_list(a);
    
    free_list(&a);
    
    return 0;
}
