#include <stdio.h>
#include <string.h>


#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100


typedef enum precedence {
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
}precedence;

                //(  )  +   -  *   /  %  operand
static int isp[] = {0,19,12,12,13,13,13,0};         ////後(內)
static int icp[] = {20,19,12,12,13,13,13,0};        ////前(外)

precedence stack[MAX_STACK_SIZE];               ///為了存符號
char expr[MAX_EXPR_SIZE];                     ///為了scanf那邊存入輸入進去的資料



void stack_full(void)
{
    fprintf(stderr,"error stack is full\n");
}





void add(int *top, int item)                ///為何 precedence 的TOKEN 在此是用 INT ???
{
    if(*top >= MAX_STACK_SIZE-1)
        return stack_full();
    
    (*top)++;
    stack[*top] = item;
}






precedence stack_empty(void)                ///???why precedence
{
    fprintf(stderr, "error: stack is empty\n");
    
    return -1;
}



precedence delete(int *top)
{
    if(*top == -1)
        return stack_empty();
    
    return stack[(*top)--];
}




void print_token(precedence token)
{
    switch(token){
        case lparen : printf("("); break;
        case rparen : printf(")"); break;
        case plus  : printf("+"); break;
        case minus : printf("-"); break;
        case times : printf("*"); break;
        case divide : printf("/"); break;
        case mod   : printf("%%"); break;    ///一個％在Ｃ有意義的 so 要打兩個％％
        default    : break;
    }
}





precedence get_token(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch(*symbol){
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand;
    }
}






void postfix(void)
{
    char symbol;
    int n=0;
    precedence token;       ///為了接收 enum 裡面的數值
    int top=0;
    
    stack[0] = eos;         /// 放符號指標從 1開始存 0是空值（代表結束）
    
    for(token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)){
        
        
        if(token == operand){
            printf("%c",symbol);
        }
        else if(token == rparen){           ///如果是 ）往後找到 （ 為止在把它刪除
            while(stack[top] != lparen){
                print_token(delete(&top));
            }
            delete(&top);    ///discard the left parenthesis
        }
        else{
            while(isp[stack[top]] >= icp[token]){           // 這就是enum用法 ex: token==operand(8)==icp[8]==0
                print_token(delete(&top));
            }
            add(&top, token);
        }
    }
    
    while((token = delete(&top)) != eos){
        print_token(token);
    }
    printf("\n");
    
}







int main()
{
    while(scanf("%s",expr) != EOF){
        postfix();
    }
    
    return 0;
}
