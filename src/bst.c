#include <stdlib.h>
#include <assert.h>

#include "bst.h"

/*typedef binary_search_tree bst;*/
typedef bst_node node;

node* create_node(int value) {
    node* new_node = malloc(sizeof(node));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent = NULL;
    new_node->value = value;
    return new_node;
}

void free_node(node* to_delete) {
    if (to_delete->parent) {
        if (to_delete == to_delete->parent->right_child)
            to_delete->parent->right_child = NULL;
        else
            to_delete->parent->left_child = NULL;
    }
    free(to_delete);
}

void free_subtree(node* to_delete) {
    if (to_delete->left_child != NULL)
        free_node(to_delete->left_child);
    if (to_delete->right_child != NULL)
        free_node(to_delete->right_child);
    free_node(to_delete);
}

bst_node* bst_insert(node** root, int value) {
    node* new_node = create_node(value);

    if (*root == NULL) {
        return (*root = new_node);
    }

    node* target = *root;
    while (1) {
        if (target->value > value) {
            if (target->left_child == NULL) {
                target->left_child = new_node;
                break;
            }
            target = target->left_child;
        } else {
            if (target->right_child == NULL) {
                target->right_child = new_node;
                break;
            }
            target = target->right_child;
        }
    }

    new_node->parent = target;
    return new_node;
}

bst_node* bst_search(node* root, int value) {
    while (root != NULL && root->value != value) {
        root = (root->value > value) ? root->left_child : root->right_child;
    }
    return root;
}

bst_node* subtree_min(node* root) {
    assert(root);
    while (root->left_child)
        root = root->left_child;
    return root;
}

/* int subtree_delete(node** root, int value) {
} */

int bst_delete(node** root, int value) {
    node* target = bst_search(*root, value);

    if (!target) {
        return -1;
    }

    if (target->left_child && target->right_child) {
        /* weird case */
        node* replacement = subtree_min(target->right_child);
        target->value = replacement->value;
        bst_delete(&target->right_child, target->value);
    } else if (target->left_child || target->right_child) {
        /* swap out target with replacement, updating parent value */
        node* replacement = target->left_child ? target->left_child : target->right_child;
        node* parent = target->parent;
        *target = *replacement;
        target->parent = parent;
        /* delete (now redundant) replacement value */
        replacement->parent = NULL;
        free_node(replacement);
    } else {  /* none of the above - no children */
        if (target->parent) {
            if (target == target->parent->left_child)
                target->parent->left_child = NULL;
            else
                target->parent->right_child = NULL;
            free_node(target);
        } else {
            /* just nuked the root - better notify an adult */
            free_node(target);
            *root = NULL;
        }
    }
    return 0;
}
