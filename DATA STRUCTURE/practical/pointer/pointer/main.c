#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct list_node* list_pointer;

typedef struct list_node

{
     int id;  /*   學號    */

     char name[20]; /*   姓名    */

     list_pointer link;    /*   指向下一個節點的指標    */

} list_node;

list_pointer head = NULL;      /*   鍵結串列起始指標     */






void search(list_pointer head)
{
    if(!head){
        printf("there have been no member you can search");
    }
    int searchID;
    printf("請輸入搜尋學號");
    scanf("%d",&searchID);
}




void delete(list_pointer *ptr, list_pointer head)
{
    if(! *ptr){
        fprintf(stderr, "The memory has empty");
        exit(1);
    }
    
    
    int deleteID;
    printf("請輸入刪除學號");
    scanf("%d",&deleteID);
    
    list_pointer temp , boost;
    temp = head;
    boost = head -> link;
    if(deleteID == temp -> id){
        head = boost;
        free(temp);
    }
    
    
    for(  ; boost ;temp = temp -> link, boost = boost -> link){         ///起點就刪除
        if(deleteID == boost->id){              ///最後一個刪除
            temp -> link = boost -> link;
            free(boost);
        }
        else{
            printf("資料不存在");
            
            break;
        }
    }
    
    
    
    
}







void print_list(list_pointer head)
{
    ///printf("The list contain:\n");
    for(  ; head; head = head -> link){
        printf("%d   %s   ",head -> id, head -> name );
    }
    printf("\n");
}







void creatspace(list_pointer *lead)
{
  
    list_pointer new = (list_pointer)malloc(sizeof(list_node));//giving space
    if(!new){
        fprintf(stderr,"The memory is FULL");
        exit(1);
    }
    printf("請輸入新增學號:\n");
    scanf("%d", new -> id);
    printf("請輸入姓名:\n");
    scanf("%s",new -> name);
    if(*lead){
        new -> link = *lead;
        *lead = new;
    
    }
    else{
        new -> link =NULL;
        *lead = new;
    }
    
    
}





int main()
{
    int i;
    printf("請輸入數字 １ ２ ３ ４\n輸入1是增加\n輸入2是刪除\n輸入3是收尋\n輸入4是結束選單\n");
    while(1){
        scanf("%d",&i);
        switch(i){
            case 1 :
                creatspace(&head);
                print_list(head);
                break;
            case 2 : delete(&head,head);
                break;
            case 3 : search(head);
                break;
            case 4 :
                break;
        }

        
        
    }
    
    
    return 0;
}
