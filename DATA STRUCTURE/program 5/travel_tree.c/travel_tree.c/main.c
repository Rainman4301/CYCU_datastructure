#include <stdio.h>
#include <stdlib.h>

typedef struct node* tree_pointer;
typedef struct node{
    char data;
    tree_pointer left_child;
    tree_pointer right_child;
}node;



//MARK: stack
//using tree_pointer to point stack[]
#define MAX_STACK_SIZE 100
tree_pointer stack[MAX_STACK_SIZE]; //(指標陣列)


//MARK: queue
#define MAX_QIUEUE_SIZE 100
tree_pointer queue[MAX_QIUEUE_SIZE]; //(指標陣列)



//宣告
//MARK: tree
tree_pointer opd(char opd);
tree_pointer opt(tree_pointer lhs, char opt,tree_pointer rhs);









//------------------------------------------------------------------------------------------------------
//MARK: free tree(用後續法)

void free_tree(tree_pointer *root)
{
    if(*root){
        free_tree(& (*root)-> left_child);
        free_tree(& (*root)-> right_child);
        free(*root);
        *root = NULL;
    }
}


//MARK: make tree

tree_pointer get_node(void) {                  //這邊很奇怪 已經寫了 typedef struct node{}node;{卻不能使用 node 程式會出錯}
    tree_pointer nod = (tree_pointer)malloc(sizeof(node));
    nod->data = '0';
    nod->left_child = NULL;
    nod->right_child = NULL;
    return nod;
}




tree_pointer opt(tree_pointer lhs, char opt, tree_pointer rhs) {
    tree_pointer o = NULL;
    o = get_node();
    o->data = opt;
    o->left_child = lhs;
    o->right_child = rhs;
    return o;
}




tree_pointer opd(char opd) {
    tree_pointer t = NULL;
    t = get_node(); t->data = opd;
    return t;
}





//------------------------------------------------------------------------------------------------------





tree_pointer deleteq(int *front, int rear)
{
    if(*front == rear){
        return NULL;
    }
    
    *front = (*front + 1) % MAX_QIUEUE_SIZE;
    return queue[*front];
}


void queue_full(int *rear)
{
    //reset
    *rear = (*rear + MAX_QIUEUE_SIZE - 1) % MAX_QIUEUE_SIZE;
    fprintf(stderr,"error: queue is full");
    exit(1);
}


void addq(int front, int *rear, tree_pointer item)
{
    *rear = (*rear + 1) % MAX_QIUEUE_SIZE;
    
    if(front == *rear){
        queue_full(rear); //reset rear & print error
        return;
    }
    queue[*rear] = item;
}



//MARK: level_order(階層尋訪： 一層一層加入陣列指標中 搭配 queue)

void level_order(tree_pointer ptr)
{
    int front = 0, rear = 0;
    
    if(!ptr){
        return;     // empty tree
    }
    
    addq(front, &rear, ptr);
    
    for(;;){
        ptr = deleteq(&front , rear);
        if(ptr){
            printf("%c", ptr -> data);
            if(ptr -> left_child){
                addq(front, &rear, ptr->left_child);
            }
            if(ptr -> right_child){
                addq(front, &rear, ptr->right_child);
            }
        }
        else break;
    }
}







//------------------------------------------------------------------------------------------------------



tree_pointer delete(int *top)
{
    if(*top == -1){
        return NULL;
    }
    return stack[(*top)--];
}



void add (int *top, tree_pointer item)
{
    if(*top >= MAX_STACK_SIZE -1){
        fprintf(stderr, "error: stack is full\n");
        exit(1);
    }
    (*top)++;
    stack[*top] = item;
}


//MARK: iter_inorder (中序loop 搭配stack)
void iter_inorder(tree_pointer node)
{
    int top = -1;
    for(;;){
        
        // searching for left node
        for(;node;node = node ->left_child){
            add(&top,node);
        }
        
        // is similar to printf()
        node = delete(&top);
        if(!node) break;
        printf("%c", node -> data);
        
        // searching for right node
        node = node->right_child;
    }
}



//------------------------------------------------------------------------------------------------------



//MARK: inorder(中序)

void inorder(tree_pointer ptr)
{
    if(ptr){
        inorder(ptr ->left_child);
        printf("%c", ptr->data);
        inorder(ptr ->right_child);
    }
}



//MARK: preorder(先序)

void preord(tree_pointer ptr)
{
    if(ptr){
        printf("%c", ptr -> data);
        preord(ptr -> left_child);
        preord(ptr -> right_child);
    }
}




//MARK: 後序尋訪


void postord(tree_pointer ptr)
{
    if(ptr){
        postord(ptr -> left_child);
        postord(ptr -> right_child);
        printf("%c", ptr -> data);
    }
}

//------------------------------------------------------------------------------------------------------




//MARK: main
 
int main()
{
    tree_pointer t = opt( opt( opt( opt( opd('A'), '/', opd('B') ), '*', opd('C') ), '*', opd('D') ), '+', opd('E'));

    
    printf("%15s", "iter_inorder: ");   // 中序尋訪(loop搭配stack)
    iter_inorder(t); printf("\n");
    
    
    printf("%15s", "inorder: ");    // 中序尋訪
    inorder(t); printf("\n");
    
    
    printf("%15s", "preorder: ");     // 先序尋訪
    preord(t);
    printf("\n");
    
    
    printf("%15s", "postorder: ");      // 後序尋訪
    postord(t); printf("\n");
    
    
    printf("%15s", "level_order: ");        //階層尋訪（搭配 queue)
    level_order(t); printf("\n");
    
    
    free_tree(&t);
    return 0;
}


