

#include <stdio.h>
#include <stdlib.h>


typedef struct element{
    int key;
}element;


typedef struct node* node_pointer;
typedef struct node{
    
    node_pointer llink;
    node_pointer rlink;
    element data;
}node;






void ddelete(node_pointer node, node_pointer deleted);
void free_list(node_pointer *list) {
    node_pointer ptr = *list;
    while ((ptr = (*list)->rlink) != *list) {
        ddelete(*list, ptr);
    }
    free(*list);
    *list = NULL;
}




void ddelete(node_pointer node, node_pointer deleted) {
    if (node == deleted)
        printf("Deletion of head node not permitted.\n");
    else {
        deleted->llink->rlink = deleted->rlink;
        deleted->rlink->llink = deleted->llink;
        free(deleted);
    }
}




void inverse(node_pointer head){
    
    node_pointer temp=head;
    
    for(temp=head->rlink;temp!=head;temp = temp->rlink){}
    temp = temp->llink;
    
    do{
        printf("%d ", temp->data.key);
        temp=temp->llink;
    }while(temp!=head);
        
    
}




void print_list(node_pointer head){
    
    node_pointer ptr = head;
    while ((ptr = ptr->rlink) != head) {
        printf("%4d", ptr->data.key);
    }
    printf("\n");
    
}






                // head節點           新結點
void dinsert(node_pointer node, node_pointer new_node){
    
    new_node->llink = node;
    //原。 [-1]<-[-1]->[-1]  後        [40]<-(head)[-1]->[10]->[20]->(q)[30]->(p)[40]->[-1]
    new_node->rlink = node->rlink;
    node->rlink->llink=new_node;
    node->rlink = new_node;
    
}



node_pointer get_node(void){
    node_pointer temp;
    temp = (node_pointer)malloc(sizeof(node));
    
    temp->data.key=0;
    temp->llink=NULL;
    temp->rlink=NULL;
    
    return temp;
}



node_pointer creat_node(void){
    node_pointer temp = get_node();
    
    temp->data.key = -1;
    temp->llink = temp;
    temp->rlink = temp;
    
    return temp;
}


int main(void) {
    int i;
    node_pointer list = NULL, p = NULL, q = NULL;
    
    list = creat_node();
    
    
    // insert 10, 20, 30, 40, and 50.
    for ( i = 1, q = list; i <= 5; i++, q = p) {
        p = get_node();
        p->data.key = i * 10;
        dinsert(q, p);
    }
    
    print_list(list);
        
//    inverse(list);
    
    
    // delete 20 and 40.
    do {
        p = list;
        while (  (void)(p = p->rlink)  , (p->data.key % 20 != 0) && ( p != list ) );
        
        
        
        
        if (p != list){
//            printf("%d \n", p->data.key);
            ddelete(list, p);
        }
        
    } while (p != list);
    print_list(list);
    
    
    free_list(&list);
    
    
    
    return 0;
}
