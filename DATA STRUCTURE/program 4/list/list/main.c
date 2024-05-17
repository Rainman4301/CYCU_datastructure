#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(ptr)  (!(ptr))   

typedef struct list_node* list_pointer;         ///指標list_pointer-> 指向list_node
typedef struct list_node{
    int data;
    list_pointer link;                          ///指標  link -> 指向 list_pointer              link  ->  list_pointer  ->  li
}list_node;



void delete(list_pointer *ptr, list_pointer trail, list_pointer node);
void free_list(list_pointer *list)
{
    while(*list){
        delete(list, NULL, *list);
    }
}





void delete(list_pointer *ptr, list_pointer trail, list_pointer node)       ///這裡的。*ptr , trail , node 位置關西不懂？？？
{
    if(trail)
        trail -> link = node -> link;
    
    else
        *ptr = (*ptr) -> link;
    
    free(node);
}






void insert(list_pointer *ptr, list_pointer node)           ///here *ptr  原本list 指標指向（first） ,  這裡的 node 是 list       [為什麼要分 ＊ptr  &  ptr]
{
    list_pointer temp;
    temp = (list_pointer)malloc(sizeof(list_node));
    
    if(IS_FULL(temp)){
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    temp -> data = 50;
    
    if(*ptr){
        temp -> link = node -> link;                 /// here (node) means (first -> second)         temp(50)->second(20)
        node -> link = temp;                       ///   node(first)    ->  temp(10)->second(50)
    }
    else{                               ///it mean that there is nothing in struct (防呆)
        temp -> link = NULL;
        *ptr = temp;
    }
}





void printlist(list_pointer ptr)
{
    printf("The list contains: ");
    
    for(;ptr; ptr = ptr -> link){                   ///here  initial value is (first)
        printf("%4d", ptr -> data);
    }
    printf("\n");
}





list_pointer create2(void)
{
    list_pointer first, second;
    first = (list_pointer)malloc(sizeof(list_node));
    second= (list_pointer)malloc(sizeof(list_node));
    
    first -> data = 10;
    first -> link = second;
    
    second -> data = 20;
    second -> link = NULL;
    
    
    return first;
}






int main()
{
    list_pointer list = create2();
    printlist(list);
    
    ///  INSERT after(first)10     50    front(second)20 ????
    
    insert(&list , list);
    printlist(list);
    
    
    /// delete 20
    
    
    list_pointer p = NULL, q = list;            ///
    while(q){
        if(q -> data == 20) break;
        p = q;
        q = q -> link;
    }
    
    delete(&list, p, q);
    printlist(list);
    
    
    ///FREE the memory
    
    free_list(&list);
    
    return 0;
    
    
}
