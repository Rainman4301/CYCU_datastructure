#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


#define COMPARE(a,b) ((a) < (b) ? -1 : (a) == (b) ? 0: 1)
#define IS_FULL(ptr) (!(ptr))


typedef struct poly_node* poly_pointer;
typedef struct poly_node{
    float coef;
    int expon;
    poly_pointer link;
}poly_node;

poly_pointer avail = NULL;




void free_avail(void)
{
    poly_pointer temp;
    while(avail){
        temp = avail -> link;
        free(avail);
        avail = temp;
    }
}




//回收不用得鍵結串鍊(不刪除)
void cerase(poly_pointer *ptr)
{
    poly_pointer temp;
    if(*ptr){
        temp = (*ptr) -> link;
        (*ptr) -> link = avail;
        avail = temp;
        *ptr = NULL;
    }
}






void attach(float coefficient, int exponential, poly_pointer *ptr);
poly_pointer get_node(void);
poly_pointer cpadd(poly_pointer *a,poly_pointer *b)       //不加星號是因為不想改變原函式的指標為址
{                                              //   要用*的話要記得(*a)如此用
    poly_pointer starta, d , lastd , startb;
    int sum, done = FALSE;
    
    startb = *b;
    starta = *a;
    (*a) = (*a) -> link;
    (*b) = (*b) -> link;
    d = get_node();
    d -> expon = -1;
    lastd = d;
    
    do{
        switch(COMPARE((*a)->expon, (*b)->expon)){
            case -1:     // a->expon < b->expon
                attach((*b)->coef, (*b)->expon, &lastd);
                (*b) = (*b) -> link;
                break;
            case 0:      // a->expon = b->expon            這就是為什麼要多創一個[0][-1]  才知道比完結束
                if(starta -> expon == startb -> expon){
                    done = TRUE;
                    break;
                }
                else{
                    sum = (*a) -> coef + (*b) -> coef;
                    if(sum){
                        attach(sum, (*a)->expon, &lastd);
                        (*a) = (*a) -> link;
                        (*b) = (*b)-> link;
                    }
                }
                break;
            case 1:      // a->expon > b->expon
                attach((*a)->coef, (*a)->expon, &lastd);
                (*a) = (*a) -> link;
                break;
        }
    } while(!done);
    
    lastd -> link = d;   // (d)[0][-1]->[-3][10]->[2][8]->[10][6]->(lastd)[1][0]->[0][-1]
    
//    printf("==%d==", lastd ->expon);
    
    return d;
    
}






void print_poly(poly_pointer ptr){
    poly_pointer head = ptr;
    int flag =0;
    
    while(head != (ptr = ptr->link)){       // head == a == ptr ==[0][-1]: -> [2][8] -> [1][0] -> [0][-1]
        if(flag){   //為了第二次印多項式時能幫忙印 + OR -
            printf("%c", ptr->coef < 0 ? '-' : '+');                //if (ptr->coef < 0) == T => print '-'
        }                                                     // .................== F  => print '+'
        
        printf("%.2f", flag ? fabsf(ptr -> coef) : ptr->coef);       //(flag ?) if(flag==1) print[fabs(x)  傳回x的絕對值]  if(flag==0) print[(ptr->link)]         為了數字做輸入的時候 不管正負都先印整數， 前面符號會另外印
        
        //第一次回圈時 flag == 0 用 ptr->coef(直接印係數 ex. 2 or -3),  第二次迴圈時 flag == 1 用fabsf()取係數的絕對值  因為前一項函式（因為flag=1)會幫忙印出 + or -
                                
        
        if(ptr -> expon != 0){
            printf("* X^%d" , ptr->expon);
        }
        if(!flag){
            flag = 1;
        }
        
    }
    printf("\n");
        
}






void attach(float coefficient, int exponential, poly_pointer *ptr)
{
    poly_pointer buf = (poly_pointer)malloc(sizeof(poly_node));
    
    if(IS_FULL(buf)){
        fprintf(stderr,"The memory have been empty");
        exit(1);
    }
    
    buf -> coef = coefficient;
    buf -> expon = exponential;
    
    
    buf -> link = (*ptr) -> link;
    (*ptr) -> link = buf;
    *ptr = buf;            //這裡的指標順序是 [1]->[0][-1](領導指標 *ptr[1])
                            //              [1]->[2]->[0][-1](領導指標 *ptr[2])
}                           //              [1]->[2]->[3]->[0][-1](領導指標 *ptr[3])





                                    
poly_pointer get_node(void)             ///creat a node for  use
{
    poly_pointer node;                 ///creat a recycle TRUNK
    
    
    //回收後的鍵結串鍊再度使用
    if(avail){
        node = avail;
        avail = avail -> link;
    }
    else{
        node = (poly_pointer)malloc(sizeof(poly_node));
        if(IS_FULL(node)){
            fprintf(stderr,"The memory has been full");
            exit(1);
        }
    }
    
    node -> coef = 0;
    node -> expon = 0;
    node -> link = NULL;
    return node;
}





poly_pointer creat_poly(void)
{
    poly_pointer temp = get_node();
    temp -> expon = -1;
    
    temp -> link = temp;        //circulate
    return temp;
}





int main ()
{
    poly_pointer a = NULL, b = NULL, d = NULL, temp = NULL;
    
    
    
    a = creat_poly();       //2x^8 + 1
    temp = a;
    attach(2,8,&temp);      //(a)[0][-1] -> (temp)*[2][8] -> [0][-1]
    attach(1,0,&temp);      //(a)[0][-1] -> [2][8] -> (temp)*[1][0] -> [0][-1]
//    temp -> link = a;
    
  
    
    printf("A(X) = ");
    print_poly(a);
    
    
    
    b = creat_poly();       // -3X^10 + 10X^6
    temp = b;
    attach(-3,10,&temp);    //(b)[0][-1] -> (temp)[-3][10]
    attach(10,6,&temp);     //(b)[0][-1] -> [-3][10] -> (temp)[10][6] -> [0][-1]
//    temp -> link = b;      //  this is a circulative linked list


    printf("B(X) = ");
    print_poly(b);
    
    
    
    d = cpadd(&a,&b);
    
    printf("B(X) = ");
    print_poly(d);
    
    printf("a: %d\n",a->expon);
    printf("b: %d\n",b->expon);
    printf("d: %d\n",d->expon);
    //delete (a,b) and recycle (d)
    cerase(&a);
    cerase(&b);
    cerase(&d);
    
    
    
    //free the memory
    free_avail();
    
    return 0;

}
