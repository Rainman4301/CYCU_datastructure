#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(ptr) (!(ptr))

typedef struct node* tree_pointer;
typedef struct node{
    char data;
    tree_pointer left_child;
    tree_pointer right_child;
}node;


//***********************************************************************************************************

void free_tree(tree_pointer *root)
{
    if(*root){
        
        // 後續法(pos_order)
        free_tree(&(*root) -> left_child);
        free_tree(&(*root) -> right_child);
        free(*root);
        
        *root = NULL;
    }
}


//***********************************************************************************************************


void inorder(tree_pointer ptr)
{
    if(ptr){
        inorder(ptr -> left_child);
        printf("%c ", ptr -> data);
        inorder(ptr -> right_child);
    }
}



//***********************************************************************************************************

//MARK: 比較

int equal(tree_pointer first, tree_pointer second){
    return (
            
        //如果兩個都ＮＵＬＬ也是相同
        (!first && !second) ||
            
        // first & second 都非空
        (first && second &&
         
         //類似前續(preorder)
         // node都非空
        (first -> data == second -> data) &&
        equal(first -> left_child, second -> left_child) &&
        equal(first -> right_child, second -> right_child)
        )
            
    );
}



//MARK: 複製


tree_pointer copy(tree_pointer original)
{
    tree_pointer temp ;
    if(original){
        temp = (tree_pointer)malloc(sizeof(node));
        
        if(IS_FULL(temp)){
            fprintf(stderr, "The memory is full\n");
            exit(1);
        }
        
        // 也是後續法(poster)的一種
        temp -> left_child = copy(original -> left_child);
        temp -> right_child = copy(original -> right_child);
        temp -> data = original -> data;
        
        return temp;
    }
    return NULL;
}




//***********************************************************************************************************


tree_pointer get_node(void)
{
    tree_pointer nod = (tree_pointer)malloc(sizeof(node));
    if(!nod){
        fprintf(stderr, "error: memory is full\n");
    }
    nod -> data = '0';
    nod -> left_child = NULL;
    nod -> right_child = NULL;
    
    return nod;
}


tree_pointer opt(tree_pointer lhs,char opt,tree_pointer rhs)
{
    tree_pointer o = NULL;
    o = get_node();
    
    o -> data = opt;
    o -> left_child = lhs;
    o -> right_child = rhs;
    
    return o;
}



tree_pointer opd (char opd)
{
    tree_pointer t = NULL;
    t = get_node();
    t -> data = opd;
    
    return t;
}


//***********************************************************************************************************



int main (void)
{
    tree_pointer a = NULL, b = NULL, c = NULL;
    a = opt(opt(opt(opt(opd('A'),'/',opd('B')),'*',opd('C')),'*',opd('D')),'+',opd('E'));
    
    
    b = copy(a);
    c = copy(a);
    c -> data = '-';
    
    printf("a = "); inorder(a); printf("\n");
    printf("b = "); inorder(b); printf("\n");
    printf("c = "); inorder(c); printf("\n");
    
    printf("a %s b\n", equal(a,b)? "==":"!=");
    printf("a %s c\n", equal(a,c)? "==":"!=");
    printf("b %s c\n", equal(b,c)? "==":"!=");
    
    
    free_tree(&a);
    free_tree(&b);
    free_tree(&c);
    
    return 0;
}
