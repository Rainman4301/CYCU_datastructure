#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree_pointer;
struct node {
    char data;
    tree_pointer left_child, right_child;
};

// MARK: Stack
#define MAX_STACK_SIZE 100
tree_pointer stack[MAX_STACK_SIZE] ;

// MARK: Queue
#define MAX_QUEUE_SIZE 100
tree_pointer queue[MAX_QUEUE_SIZE] ;

// MARK: Tree
tree_pointer opd(char opd);
tree_pointer opt(tree_pointer lhs, char opt, tree_pointer rhs);



void free_tree(tree_pointer *root);
void iter_inord(tree_pointer node);
void level_ord(tree_pointer ptr);
void postord(tree_pointer ptr);
void preord(tree_pointer ptr);
void inord(tree_pointer ptr);


// MARK: Main
int main() {
    tree_pointer t =
    opt( opt( opt( opt( opd('A'), '/', opd('B') ), '*', opd('C') ), '*', opd('D') ), '+', opd('E'));
    printf("%15s", "iter_inorder: ");         ///中序尋訪（迴圈模式）
    iter_inord(t); printf("\n");

    printf("%15s", "inorder: ");            ///中序尋訪
    inord(t); printf("\n");

    printf("%15s", "preorder: ");            ///先序尋訪
    preord(t); printf("\n");

    printf("%15s", "postorder: ");           ///後序尋訪
    postord(t); printf("\n");

    printf("%15s", "level_order: ");         ///階層尋訪
    level_ord(t); printf("\n");

    free_tree(&t);                  ///可用中序尋訪（釋出）
    return 0;
}

// MARK: Stack

void stack_full(void) {
    fprintf(stderr, "error: stack is full\n");
    exit(1);
}

/* add an item to the global stack */
void add(int *top, tree_pointer item) {
    if (*top >= MAX_STACK_SIZE - 1)
        return stack_full();
    (*top)++;
    stack[*top] = item;
}

tree_pointer stack_empty(void) {
    //fprintf(stderr, "error: stack is empty\n");
    return NULL;
}

/* return the top element from the stack */
tree_pointer delete(int *top) {
    if (*top == -1)
        /* returns an error key */
        return stack_empty();
    return stack[(*top)--];
}

// MARK: Queue

void queue_full(int *rear) {
    *rear = (*rear + MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE;
    fprintf(stderr, "error: queue is full\n");
    exit(1);
}

/* add an item to the queue */
void addq(int front, int *rear, tree_pointer item) {
    *rear = (*rear + 1) % MAX_QUEUE_SIZE;
    if  (front == *rear) {
        queue_full(rear); /* reset rear and print error */
        return;
    }
    queue[*rear] = item;
}

tree_pointer queue_empty(void) {
    //fprintf(stderr, "error: queue is empty\n");
    return NULL;
}

/* remove front element from the queue and put it in item */
tree_pointer deleteq(int *front, int rear) {

    if (*front == rear)
        /* queue_empty returns an error key */
        return queue_empty();
    *front = (*front + 1) % MAX_QUEUE_SIZE;
    return queue[*front];
}






// MARK: Tree

tree_pointer get_node(void) {
    tree_pointer node = (tree_pointer)malloc(sizeof(struct node));
    node->data = '0';
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

void free_tree(tree_pointer *root) {
    if (*root) {
        free_tree(&(*root)->left_child);
        free_tree(&(*root)->right_child);
        free(*root);
        *root = NULL;
    }
}

/* get a node and set the data of node is opd*/
tree_pointer opd(char opd) {
    tree_pointer t = NULL;
    t = get_node(); t->data = opd;
    return t;
}

/* get a node and set the data of node is opt*/
/* set the left_child of node is lhs and set the right_child of node is rhs*/
tree_pointer opt(tree_pointer lhs, char opt, tree_pointer rhs) {
    tree_pointer o = NULL;
    o = get_node();
    o->data = opt;
    o->left_child = lhs;
    o->right_child = rhs;
    return o;
}







void inord(tree_pointer ptr) {                    ///中序尋訪
    if (ptr) {
        inord(ptr->left_child);
        printf("%c", ptr->data);
        inord(ptr->right_child);
    }
}

void preord(tree_pointer ptr) {                   ///先序尋訪
    if (ptr) {
        printf("%c", ptr->data);
        preord(ptr->left_child);
        preord(ptr->right_child);
     }
}

void postord(tree_pointer ptr) {                  ///後序尋訪
    if (ptr) {
        postord(ptr->left_child);
        postord(ptr->right_child);
        printf("%c", ptr->data);
    }
}

void iter_inord(tree_pointer node) {                          ///中序尋訪（迴圈模式
    int top = -1; /* initialize stack */
    for (;;) {
        for (; node; node = node->left_child)
            add(&top, node); /* add to stack */
        node = delete(&top); /* delete from stack */
        if (!node) break; /* empty stack */
        printf("%c", node->data);
        node = node->right_child;
    }
}

/* level order tree traversal */
void level_ord(tree_pointer ptr) {                        ///階層尋訪
    int front = 0, rear = 0;
    if (!ptr) return; /* empty tree */
    addq(front, &rear, ptr);
    for (;;) {
        ptr = deleteq(&front, rear);
        if (ptr) {
            printf("%c", ptr->data);
            if (ptr->left_child)
                addq(front, &rear, ptr->left_child);
            if (ptr->right_child)
                addq(front, &rear, ptr->right_child);
        }
        else break;
    }
}
