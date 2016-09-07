#include "complete_bst.h"
#include <stdio.h>
#include <stdlib.h>

/******************** LOCAL FUNCTIONS ********************/
static void construct_sub_node(BinaryTreeNode **p_node, void* array, size_t val_size, int start_idx, int end_idx)
{
    if(start != end)
    {
        int mid = start_idx + (end_idx - start_idx) / 2;
        *p_node = calloc(1, val_size);
        memcpy(p_node, array + mid * val_size, val_size);
        construct_sub_node(&p_node->p_left, array, val_size,start_idx, mid);
        construct_sub_node(&p_node->p_right, array, val_size,mid+1, end_idx);
    }
}

/******************** PUBLIC API ********************/
BinaryTree* complete_binary_tree_construct_from_sorted_array(void* array, BINARY_TREE_VAL_TYPE_E e_val_type, size_t num_elem, size_t val_size)
{
    int loop = 0;
    BinaryTree *p_tree = calloc(1, sizeof(*p_tree));
    construct_sub_node(p_tree->p_root, array, val_size, 0, num_elem);

    return p_tree;
}