#include <stdio.h>
#include <stdlib.h>                                 //因為用exit
#include <math.h>                                   //p
#define MAX_SIZE 101
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void sort (int[],int);                 /*selection sort*/
int main (void) {
    int i, n;
    int list[MAX_SIZE];
    printf ("Enter the number of numbers to generate: ");
    scanf (" %d", &n);
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, " Improper value of n\n");                  //p
        exit (1);                                                   //p
    }
    for (i = 0; i < n; i++) {
        /* randomly generate numbers */
        list [i] = (rand() %1000);
        printf(" %d  ",list[i]);
    }
    sort(list, n);
    printf("\n Sorted array: \n  ");
    for (i = 0; i < n; i++) /* print out sorted  numbers */
        printf(" %d ", list[i]);
    printf("\n");
    return 0;
}


void sort(int list[], int n) {



    //每次回圈把最小或最大放最左邊
    //選擇排序
    /*

    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }

     */


    //泡沫排序法(每一圈把最小或最大放右邊)
    int temp;

    for(int i =0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(list[j]<list[j+1]){
                SWAP(list[j], list[j+1], temp);
            }
        }
    }








}





