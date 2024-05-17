#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ELEMENT 200
#define HEAP_FULL(N) (N==MAX_ELEMENT - 1)
#define HEAP_EMPTY(N) (!N)


typedef struct element{
    int key;
}element;

element heap[MAX_ELEMENT] = {0};     // 主要放資料的空間
int n =0;                       //資料從1開始存取







//*************************************************************************************



void print_max_heap(int n)
{
    int i, j = 1;

    for(i = 1; i <= n ; i++){
        printf("%3d", heap[i].key);
        //  檢查是否當層最後一個元素 ＆＆ 看是不是最後一個元素
        if(i == 2*j - 1 && i != n){
            j = pow(2, i);           // 2^i  目的是為了換行 每層的最左邊是2的次方

            printf("\n");
        }
    }
    printf("\n");
}




//*************************************************************************************

//MARK: delete root change to 最底層元素



element delete_max_heap(int *n)
{
    int parent, child;

    element item, temp;

    if(HEAP_EMPTY(*n)){
        fprintf(stderr, "The heap is empty\n");
        exit(1);
    }

    //刪除的最大值
    item = heap[1];

    //最後一個元素
    temp = heap[(*n)--];

    parent = 1; child = 2;

    //先。找到子節點哪個最大值
    while (*n >= child) {
        if((*n > child) && (heap[child].key < heap[child + 1].key)){
            child++;
        }

    //在判斷 最後 兩個節點比看誰大 決定上移 or 補節點數值
        if(temp.key > heap[child].key ){
            break;
        }

    //如果沒進入上層韓式的話代表此時的 heap最後一元素(temp) < 比過的子節點(child)
        heap[parent] = heap[child];  //子節點值上移
        parent = child;            // parent 位置下移到原本的 child 位置 成為新的 parent
        child = child*2;           // child 位置移到新的左子節點 child
    }

    //在判斷 最後 兩個節點比看誰大 決定上移
    heap[parent] = temp;

    return item;


}



//*************************************************************************************

//MARK: insert_max_heap


void insert_max_heap(element item, int *n)
{
    int i;

    if(HEAP_FULL(*n)){
        fprintf(stderr, "The heap is full");
        exit(1);
    }

    i = ++(*n); // 資料從1開始存取資料

          // data非第一筆          如果插入資料比父節點資料大的話交換
    while( (i != 1) && (item.key > heap[i/2].key) ){
        heap[i] = heap[i/2];
        i = i/2;
    }

    heap[i] = item ;

}




//*******************************************************************************************************



int main(void)
{
    element item;         // 要被放入資料的暫時空間


    item.key = 25; insert_max_heap(item, &n);
    item.key = 20; insert_max_heap(item, &n);
    item.key = 2; insert_max_heap(item, &n);
    item.key = 14; insert_max_heap(item, &n);
    item.key = 10; insert_max_heap(item, &n);
    item.key = 5; insert_max_heap(item, &n);
    item.key = 21; insert_max_heap(item, &n);

    print_max_heap(n);


    item = delete_max_heap(&n);
    printf("\npop: %d\n", item.key);
    print_max_heap(n);

    item = delete_max_heap(&n);
    printf("\npop: %d\n", item.key);
    print_max_heap(n);

//    printf("heap[0]= %d\n",heap[0].key);

    return 0;
}


