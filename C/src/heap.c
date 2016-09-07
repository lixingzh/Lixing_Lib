#include "binary_tree.h"
/******************* LOCAL FUNCTION *******************/
static int get_parent_idx(int index)
{
    return(index / 2);
}

static void get_children_index(size_t index, size_t num_elem, int *p_left, int *p_right)
{
    assert_or_return(index < num_elem);
    assert_or_return(NULL != p_left && NULL != p_right, VOID_RETURN);
    *p_left = 2*(index + 1) - 1;
    *p_right = 2*(index + 1);
}

static void heapify_node(BinaryTree *p_tree, void *p_array, int index, bool b_high_low)
{
    int parent_idx = get_parent_idx(index);
    if(true == b_high_low)
    {
        if(-1 == p_tree->apis.compare(p_array + parent_idx * p_tree->val_size,
                                      p_array + index * p_tree->val_size))
        {
            p_tree->apis.swap(p_array + parent_idx * p_tree->val_size,
                              p_array + index * p_tree->val_size);
        }
    }
    else
    {
        if(1 == p_tree->apis.compare(p_array + parent_idx * p_tree->val_size,
                                      p_array + index * p_tree->val_size))
        {
            p_tree->apis.swap(p_array + parent_idx * p_tree->val_size,
                              p_array + index * p_tree->val_size);
        }
    }
    heapify_node(p_tree, p_array, parent_idx, b_high_low);
}

/******************* PUBLIC_API *********************/
void heapify(BinaryTree *p_tree, void *p_array, size_t num_elem, bool b_high_low)
{
    int loop = 0;
    if(NULL == p_tree || NULL == p_array || num_elem ==0 || val_size == 0)
    {

    }
    else
    {
        if(p_tree->apis.compare != NULL && p_tree->apis.swap != NULL)
        {
            for(loop = num_elem - 1; loop >= 0; --loop)
            {
                heapify_node(p_tree, p_array, loop, b_high_low);
            }
        }
    }
}