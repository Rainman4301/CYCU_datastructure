#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(ptr)  (!(ptr))
#define IS_FULL(ptr)  (!(ptr))


typedef struct element{             ///WHY 這裡要多創一個結構
    int key;
} element;
    


typedef struct stack* stack_pointer;
typedef struct stack{
    element item;
    stack_pointer link;
}stack;

stack_pointer top = NULL;   ///!!!  stack_pointer 創一全域 TOP 指向NULL





element delete(stack_pointer *top)
{
    stack_pointer temp = *top;
    element buf;
    if (IS_EMPTY(temp)){
        fprintf(stderr,"The stack is empty\n");
        exit(1);
    }
    
    buf = temp -> item;
    *top = temp -> link;
    free(temp);
    return buf;
}





void print_stack(stack_pointer ptr){            /// here PTR 是指表 TOP變數
    printf("The stack contain: ");
    for(;ptr;ptr = ptr -> link){
        printf("%4d", ptr -> item.key);
    }
    printf("\n");
}






void add(stack_pointer *top, element item )    ///這裡的 item 就是 item.key 存入的 i 值
{
    stack_pointer temp;
    temp = (stack_pointer)malloc(sizeof(stack));
    
    if(IS_FULL(temp)){
        fprintf(stderr,"The memory is full\n");
        exit(1);
    }
    
    temp -> item = item;
    temp -> link = *top;            ///是因為全域那邊 stack_pointer top = NULL。
    *top = temp;
}





int main()
{
    int i;
    element item;
    
    
    for(i=0; i < 10; i++){
        item.key = i;
        add(&top,item);
        print_stack(top);
    }
    
    
    for(i=0;i< 5; i++){
        item = delete(&top);
        print_stack(top);
    }
}
