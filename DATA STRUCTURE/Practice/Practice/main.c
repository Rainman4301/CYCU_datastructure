#include <stdio.h>
#include <stdlib.h>

// MARK: Tree (Prototye)
typedef struct threaded_tree *threaded_ptr;
struct threaded_tree {
    char  data;
    short int left_thread;
    short int right_thread;
    threaded_ptr left_child;
    threaded_ptr right_child;
};

threaded_ptr new_node(void);
threaded_ptr create_tree(void);
void free_tree(threaded_ptr *root);

void insert_node(threaded_ptr root, char data);

/* find the inorder sucessor of tree in a threaded binary tree */
threaded_ptr insucc(threaded_ptr tree);
/* traverse the threaded binary tree inorder */
void tinorder(threaded_ptr tree);

// MARK: Main
int main() {
    threaded_ptr tree = create_tree();

    insert_node(tree, 'E');
    insert_node(tree, 'C');
    insert_node(tree, 'J');
    insert_node(tree, 'G');
    insert_node(tree, 'D');
    insert_node(tree, 'B');
    insert_node(tree, 'A');
    insert_node(tree, 'I');
    insert_node(tree, 'H');
    insert_node(tree, 'F');

    tinorder(tree); printf("\n");

    free_tree(&tree);
    return 0;
}

// MARK: Tree (Implementation)
threaded_ptr new_node() {
    threaded_ptr node = (threaded_ptr)malloc(sizeof(struct threaded_tree));
    node->data = '0';
    node->left_thread = 0;
    node->right_thread = 0;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

threaded_ptr create_tree() {
    threaded_ptr root = new_node();
    root->left_child = root;
    root->right_child = root;
    return root;
}

void free_node(threaded_ptr *node) {
    if (*node) {
        if (!(*node)->left_thread) {
            free_node(&(*node)->left_child);
        }
        if (!(*node)->right_thread) {
            free_node(&(*node)->right_child);
        }
        free(*node);
        *node = NULL;
    }
}

void free_tree(threaded_ptr *root) {
    free_node(&(*root)->left_child);
    free(*root);
    *root = NULL;
}

void insert_node(threaded_ptr root, char data) {
    threaded_ptr node = new_node();
    node->data = data;
    node->left_thread = 1;
    node->right_thread = 1;
    node->left_child = root;
    node->right_child = root;

    if (root->left_child == root) {
        root->left_child = node;
        return;
    }

    threaded_ptr p = root->left_child;

    while (1) {
        if (data == p->data) {
            free(node);
            return;
        }
        else if (data < p->data) {
            node->right_child = p;
            if (p->left_child == node->left_child) {
                p->left_thread = 0;
                p->left_child = node;
                break;
            }
            p = p->left_child;
        }
        else {
            node->left_child = p;
            if (p->right_child == node->right_child) {
                p->right_thread = 0;
                p->right_child = node;
                break;
            }
            p = p->right_child;
        }
    }
}

/* find the inorder sucessor of tree in a threaded binary tree */
threaded_ptr insucc(threaded_ptr tree) {
     threaded_ptr temp;
     temp = tree->right_child;
     if (!tree->right_thread)
         while (!temp->left_thread)
             temp = temp->left_child;
     return temp;
}

/* traverse the threaded binary tree inorder */
void tinorder(threaded_ptr tree) {
    threaded_ptr temp = tree;
    for (;;) {
        temp = insucc(temp);
        if (temp == tree) break;
        printf("%3c", temp->data);
    }
}
