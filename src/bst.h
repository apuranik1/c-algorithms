#ifndef ALG_BST_H_
#define ALG_BST_H_

struct _bst_node {
    struct _bst_node* left_child;
    struct _bst_node* right_child;
    struct _bst_node* parent;
    int value;
};
typedef struct _bst_node bst_node;

/*
typedef struct {
    bst_node* root;
} binary_search_tree;
*/

bst_node* bst_insert(bst_node** root, int value);
bst_node* bst_search(bst_node* root, int value);
int bst_delete(bst_node** tree, int value);

#endif
