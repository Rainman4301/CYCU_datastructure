#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 50
#define COMPARE(x,y) ((x)<(y) ? -1 :(x)==(y) ? 0: 1)


struct polynomial{
    float coef;
    int expon;
};
struct polynomial term[MAX_TERMS];     //節省空間
int avail = 0;



void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);

void attach(float coefficient, int exponent);

void print_polynomial(int start,int end);






/// 增加新的 矩陣 記憶體空間 給 多項式
void attach(float coefficient,int exponent)
{
    if(avail>=MAX_TERMS){
        fprintf(stderr,"too many terms in polynomial");
        exit(1);
    }
    term[avail].coef=coefficient;                                    ///ppp
    term[avail++].expon=exponent;              // term[avail].expon = exponent; avail++;
}







///add A(x) and B(x) to obtain D(x)
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
    float coefficient;
    *startd = avail;
    
    printf("starta: %d// finisha: %d //startb: %d// finishb: %d\n",starta,finisha,startb,finishb);
    while(starta<=finisha && startb<=finishb)                                                                       ///ppp
        switch(COMPARE(term[starta].expon, term[startb].expon)){
            case -1:                                                 ///a expon < b expon
                attach(term[startb].coef, term[startb].expon);
                startb++;
                break;
            case 0:                                                  /// equal exponents
                coefficient= term[starta].coef + term[startb].coef;
                if (coefficient)
                    attach(coefficient,term[starta].expon);
                starta++;
                startb++;
                break;
            case 1:                                                  ///a expon > b expon
                attach(term[starta].coef,term[starta].expon);
                starta++;
                break;
        }
    
    printf("starta: %d// finisha: %d //startb: %d// finishb: %d\n",starta,finisha,startb,finishb);
    
    
    
//    (如果Ａ函式到x^50結束了  但Ｂ函式還有 x^40+x^30....需要印出來)
    /// add  in  remaining  terms  of  A(x)
    for(; starta <= finisha; starta++)
        attach(term[starta].coef,term[starta].expon);
    
    /// add in remaining terms of B(x)
    for(; startb <= finishb; startb++)
        attach(term[startb].coef,term[startb].expon);
    
    
    *finishd = avail - 1;
}






void print_polynomial(int start, int end)
{
    int i = start, exp;
    float coef;
    
    
    printf("%.2f", term[i].coef);
    if(term[i].expon != 0){
        printf("x^%d",term[i].expon);
    }
    
    for(i++;i <= end ; i ++){
        coef= term[i].coef;
        exp= term[i].expon;
        if( coef == 0) continue;
        
        
        if(coef == 1. && exp != 0)
            printf("+ %.2f",coef);
        else if (coef>0)
            printf(" + %.2f",coef);
        else
            printf(" - %.2f",coef * -1);
            
        
        
        if (term[i].expon != 0){
            printf("x^%d", term[i].expon);
        }
    }
    printf("\n");
    
}







int main(){
    int i , j;
    
    int a_coef[]={2,1}, b_coef[]={1,10,3,1},a_exp[]={100,0}, b_exp[]={4, 3, 2, 0};
    
    
    int a_start = 0, a_finish = 1, b_start = 2, b_finish = 5, d_start, d_finish;
    
    
    
    avail = 6;                                                                                  ///p
    for(i=a_start,j=0 ; i<=a_finish ; i++,j++){
        term[i].coef = a_coef[j];
        term[i].expon = a_exp[j];
    }
    
    for(i=b_start,j=0 ; i<=b_finish ; i++,j++){
        term[i].coef=b_coef[j];
        term[i].expon=b_exp[j];
    }
    
    
    
    printf("A(x) = \n");
    print_polynomial(a_start, a_finish);
    printf("B(x) = \n");
    print_polynomial(b_start, b_finish);
    padd(a_start, a_finish, b_start, b_finish, &d_start, &d_finish);
    
    printf("A(x) + B(x) = ");
    print_polynomial(d_start, d_finish);
    
    
    
//    for(int i =0;i<=d_finish;i++){
//        printf("%.2f    %d  // ", term[i].coef,term[i].expon);
//    }
    
}
