#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(ptr) (!(ptr))


typedef struct list_node* list_pointer;
typedef struct list_node{
    int data;
    list_pointer link;
}list_node;

 


void free_list(list_pointer *a)
{
    list_pointer ptr;
    while(*a){
        ptr = *a;
        (*a) = (*a) -> link;
        free(ptr);
    }
    *a = NULL;
}







list_pointer concatenate(list_pointer alead, list_pointer blead)
{
    list_pointer temp;
    if(!alead){
        return blead;
    }
    else{
        if(blead){
            for(temp = alead; temp -> link;temp=temp->link); //因為中間的條件沒成功所以 temp=temp->link沒成立
            
            printf("Temp: %d\n",temp->data);
            
            temp -> link = blead;
        }
        return alead;
    }
}







void print_list(char *label , list_pointer a)
{
    printf("%s", label);
    
    for( ;a; a = a->link){
        printf("%4d",a -> data);
    }
    printf("\n");
}





list_pointer invert(list_pointer alead)
{
    list_pointer middle, trail;
    middle = NULL;
    while (alead){
        trail = middle ;
        middle = alead;
        alead = alead -> link;
        middle -> link = trail;
    }
    return middle;
}






list_pointer new_node(void)
{
    list_pointer ptr = (list_pointer)malloc(sizeof(list_node));
    ptr -> data = 0;
    ptr -> link = NULL;
    return ptr;
}






int main()
{
    int i;
    list_pointer a = NULL , b = NULL , temp = NULL, newnd;
    
    for(i = 5;i >= 1;i--){                 ///coining a trunk
        newnd = new_node();
        newnd ->data = i*10;
        
        if(a){                              /// use point to assign trunk
            temp -> link = newnd;
        }
        else{
            a = newnd;
        }
        temp = newnd;
    }
    
    print_list("                a:", a);    ///     50  40  30  20  10
    
    
    for(i=6; i<=10;i++){
        newnd = new_node();
        newnd -> data = i*10;
    
        if(b){
            temp -> link = newnd;
        }
        else{
            b = newnd;
        }
        temp = newnd;
    }
    print_list("                b:", b);    /// 60  70  80  90  100
    
    
    
    
    a = invert(a);
    print_list("         invert(a):",a);        ///10   20  30  40  50
    
    a = concatenate(a,b);
    print_list("concatenate(a ,b):", a);        ///10   20  30  40  50  60  70  80  90  100
    
    
    
    free_list(&a);
}
