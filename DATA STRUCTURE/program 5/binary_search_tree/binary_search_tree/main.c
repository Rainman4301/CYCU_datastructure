#include <stdio.h>
#include <stdlib.h>


#define IS_FULL(ptr) (!(ptr))


typedef struct nod* tree_ptr;
typedef struct nod{
    int data;
    tree_ptr left_child;
    tree_ptr right_child;

}nod;


//******************************************************************************************************************************


//MARK: free_tree

    // 用後續法(postorder)
void free_tree(tree_ptr *note)
{
    if(*note){
        free_tree(&(*note) -> left_child);
        free_tree(&(*note) -> right_child);
        free(*note);
        *note = NULL;
    }
}




//******************************************************************************************************************************


//MARK: 用迴圈
//用前續法(preorder)
tree_ptr search_loop(tree_ptr tree,int key)
{
    while(tree){
        if(key == tree -> data){
            return tree;
        }

        if(key < tree->data){
            tree = tree->left_child;
        }

        else{
            tree = tree -> right_child;
        }
    }

    return NULL;
}







//MARK: 用遞迴
//用前續法(preorder)
tree_ptr search_recursion(tree_ptr root,int n)
{
    if (!root)  return NULL;        //指到位置是空的


    if(n == root -> data)
        return root;

    if(n < root -> data )
        return search_recursion(root -> left_child, n);

    return search_recursion(root -> right_child, n);

}







//******************************************************************************************************************************

void inorder_tree(tree_ptr tree)
{
    if(tree){

        inorder_tree(tree -> left_child);
        printf("%3d", tree -> data);
        inorder_tree(tree -> right_child);

    }
}




//******************************************************************************************************************************


//MARK: remodified 為了插入數值用(確定要插入的值是否已在樹中)      (用search2)改過的

tree_ptr modified_search(tree_ptr tree, int key)
{
    tree_ptr p = NULL;


    //這裡雖然tree一開始是根節點但這裡用來找尋最左or最右的節點
    while(tree){
        if(key == tree -> data)
            return NULL;

        p = tree;

        if(key < tree->data)
            tree = tree -> left_child;
        else
            tree = tree -> right_child;
    }

    return p;  //樹空 or 回傳最後找到之節點
}





//MARK:  insert_node

                    //樹結點。      //存入值。
void insert_node(tree_ptr *node, int num )
{
    tree_ptr ptr , temp ;
    temp = modified_search((*node), num);


    if(temp || !(*node)){       // 表示temp 如果有值(TRUE)代表（num不在樹中準備插入)  如果無值(NULL)代表 （num不在樹中 or 樹是空的）

        ptr = (tree_ptr)malloc(sizeof(nod));

        if( IS_FULL(ptr) ){
            fprintf(stderr,"The memory is full\n");
            exit(1);

        }

        ptr -> data = num;
        ptr -> left_child = NULL;
        ptr -> right_child = NULL;

        if(*node){                      //如果樹不是空的
            if(num < temp -> data)
                temp -> left_child = ptr;

            else   temp -> right_child = ptr;
        }
        else   *node = ptr;             //樹是空的 插入值當作根節點
    }
}



//******************************************************************************************************************************




int main(){

    tree_ptr ptr = NULL, tree = NULL;


    //插入順序不同會改變樹的結構
    insert_node(&tree, 40);
    insert_node(&tree, 20);
    insert_node(&tree, 60);
    insert_node(&tree, 10);
    insert_node(&tree, 30);
    insert_node(&tree, 50);
    insert_node(&tree, 70);
    insert_node(&tree, 45);
    insert_node(&tree, 55);
    insert_node(&tree, 52);


    inorder_tree(tree);
    printf("\n");


    ptr = search_recursion(tree,52);
    if(ptr == NULL){
        printf("Not in the tree\n");
    }
    else{
        printf("%3d is in the tree\n",ptr->data);
    }



    ptr = search_loop(tree,53);
    if(ptr == NULL){
        printf("Not in the tree\n");
    }
    else{
        printf("%3d is in the tree\n",ptr->data);
    }



    free_tree(&tree);
}
