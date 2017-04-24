#ifndef ALG_BST_H_
#define ALG_BST_H_

typedef struct bst_node {
    struct bst_node* left_child;
    struct bst_node* right_child;
    struct bst_node* parent;
    int value;
} bst_node;

/*
typedef struct {
    bst_node* root;
} binary_search_tree;
*/

bst_node* bst_insert(bst_node** root, int value);
bst_node* bst_search(bst_node* root, int value);
int bst_delete(bst_node** tree, int value);

#endif
