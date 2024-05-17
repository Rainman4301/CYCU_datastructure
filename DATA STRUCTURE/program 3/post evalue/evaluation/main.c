#include <stdio.h>
#include <string.h>
                                                    ///後序輸入。  計算出結果
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum precedent{                           // enum precedent == precedent
    lparen,
    rparen,
    plus,
    minus,
    time,
    divide,
    mod,
    eos,
    operand
} precedent;



//typedef enum{
//    lparen,
//    rparen,
//    plus,
//    minus,
//    time,
//    divide,
//    mod,
//    eos,
//    operand
//} precedent;





int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];





int stack_empty(void){
    fprintf(stderr, "error stack is empty\n");
    return -1;
}



int delete(int *top){                           ///???
    if (*top == -1){
        return stack_empty();
    }
    return stack[(*top)--];    ///所謂移除資料是什麼
}




void stack_full(void){
    fprintf(stderr,"error: stack is full\n");
}



void add(int *top, int item){
    if (*top >= MAX_STACK_SIZE -1){
        return stack_full();
    }
    (*top)++;
    stack[*top] = item;  ///token 存入 stac這裡是整數值
}







precedent get_token(char *symbol, int *n){
    *symbol = expr[(*n)++];                 ///from here get token
    switch(*symbol){
        case '(': return lparen;                 ///why return these???
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return time;
        case '%': return mod;
        case '\0': return eos;                  ///???
        default: return operand;
    }
}




int eval(void){
    precedent token;            ///由symbol 接收輸入資料 轉成 precedent token 類別的型態(幫助後面語法撰寫).
    char symbol;
    int op1,op2;
    int n=0;
    int top=-1;
    token = get_token(&symbol, &n);
    
    
    
    
    while(token != eos){
        if(token == operand){
            add(&top,symbol - '0');///型態轉換 char to int
        }
        else{
            ///remove two operands , perform operation,and return result to the stack
            
                        
            op2 = delete(&top);
            op1 = delete(&top);
            switch(token) {
                case plus:  add(&top, op1+op2);
                    break;
                case minus: add(&top, op1-op2);
                    break;
                case time: add(&top, op1*op2);
                    break;
                case divide: add(&top, op1/op2);
                    break;
                case mod: add(&top, op1%op2);
            }
        }
        token = get_token(&symbol, &n);                 ///???
    }
    return delete(&top);                                ///???
    
}






int main()
{
    while(scanf(" %s",expr) != EOF){
        printf("%d\n", eval());
    }
    return 0 ;
}
