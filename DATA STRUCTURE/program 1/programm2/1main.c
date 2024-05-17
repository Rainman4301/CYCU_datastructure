#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_SIZE 101
#define COMPARE(x,y) ( (x) < (y) ? -1 : (x) == (y) ? 0 : 1 )



int binsearch (int list[],int searchnum,int left,int right)
{
    int middle;
    while(left<=right){
        middle=(left+right)/2;
        switch(COMPARE(list[middle], searchnum)){
            case -1: return binsearch(list, searchnum, middle+1, right);    ///recursive ( 遞迴)algorithm
            case 0: return middle;
            case 1: return binsearch(list, searchnum, left, middle-1);
        }
    }
    return -1;
}


void sort(int list[],int n)
{
    int i,j,min,temp;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++)
            if(list[j]<list[min])
                min=j;
        SWAP(list[i], list[min], temp);
    }
    
}

int main(void)
{
    int n,i;
    int list[MAX_SIZE];
    
    printf ("enter the number you want to generate:");
    scanf("%d",&n);
    if(n<1 || n>MAX_SIZE){
        fprintf (stderr,"improper quantity n\n");
        exit(1);
    }
    for(i=0;i<n;i++){
        list[i]=rand()%10000;
        printf(" %d ",list[i]);
    }
    sort (list,n);
    printf("\nsorted array:\n");
    for(i=0;i<n;i++){
        printf(" %d ",list[i]);
    }
    printf("\n");
    
    int find,pos;
    printf("\n input a number you want to find ");
    scanf("%d",&find);
    pos=binsearch(list, find, 0, n-1);
    
    if (pos!=-1) {
        printf("\n find %d at %d \n",find,pos);
    }
    else {
        printf("\n %d is not found. \n",find);
    }
    
    return 0;
    
}

