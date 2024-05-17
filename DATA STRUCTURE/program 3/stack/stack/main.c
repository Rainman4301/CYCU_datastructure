#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


typedef struct element{
    int key;
} element ;

element stack[MAX_SIZE];
int top= -1 ;                                      ///指向






void stack_full(void)
{
    fprintf(stderr, "error: stack is full\n");
}





void add(int *top, element item)
{
    if (*top >= MAX_SIZE-1)
        return stack_full();
    (*top)++;
    stack[*top].key = item.key;
}




void print_stack(int top)
{
    int i;
    for(i=0;i<=top;i++){
        printf("%-3d",stack[i].key);           ///stack[].key   &  ele.key 的差別
    }
    printf("\n");
}


element stack_empty(void)
{
    fprintf(stderr,"error: stack is empty");
    element ele ={ -1 };                    ///
    return ele;
}



element delete(int *top)
{
    if(*top == -1)
        return stack_empty();
    return stack[(*top)--];  //==9; 9=9-1==8;
}








int main(void)
{
    int i;
    element ele;        //為了接 新增or刪減值
    for(i=0;i<10;i++){
        ele.key = i;
        add(&top,ele);
        printf("push:%3d | ",ele.key);
        print_stack(top);
    }
    
    for(i=0 ; i<9; i++){
        ele = delete(&top);
        printf("pop :%3d | ",ele.key);
        print_stack(top);
    }
    return 0;
}
