/*
   File: binary_tree.h
   Description:
      APIs of manipulations for a binary tree. 
      Including: 
         *construct tree
         *insert node
         *delete node
         *find node 
         *and so on
   Author: Lixing Zhang
   Date: Sep 3 2016
*/

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum {
   eVAL_TYPE_LONG,
   eVAL_TYPE_DOUBLE,
   eVAL_TYPE_STRING,
   eVAL_TYPE_USER_DEFINE,
   eVAL_TYPE_MAX
} BINARY_TREE_VAL_TYPE_E;

typedef enum {
   eBINARY_TREE_FIND_TYPE_TARGET,
   eBINARY_TREE_FIND_TYPE_PREDECESSOR,
   eBINARY_TREE_FIND_TYPE_SUCCESSOR,
   eBINARY_TREE_FIND_TYPE_MAX,
} BINARY_TREE_FIND_TYPE_E;

typedef enum {
   eBINARY_TREE_TRAVERSE_INORDER,
   eBINARY_TREE_TRAVERSE_PREORDER,
   eBINARY_TREE_TRAVERSE_POSTORDER,
   eBINARY_TREE_TRAVERSE_MAX
} BINARY_TREE_TRAVERSE_E;

typedef void (*UserDefineFree) (void* p_val);

typedef struct BinaryTreeNode BinaryTreeNode;
typedef char* (*BinaryTree_PRINT) (void* p_val);
typedef bool (*BinaryTree_INSERT) (BinaryTree *p_tree, void* p_val);
typedef bool (*BinaryTree_DELETE) (BinaryTree *p_tree, void* p_target);
typedef int (*BinaryTree_CMP) (void *p_val1, void *p_val2);
typedef BinaryTreeNode* (*BinaryTree_FIND) (BinaryTree *p_tree, void *p_target, BINARY_TREE_FIND_TYPE_E e_type, BinaryTreeNode *p_parent);
typedef void (*BinaryTree_FREE) (BinaryTreeNode *p_node, UserDefineFree free_func);
typedef void (*BinaryTree_Traverse) (BinaryTreeNode *p_root, BINARY_TREE_TRAVERSE_E e_traverse_type, BinaryTree_PRINT print_func);

typedef struct {
   BINARY_TREE_VAL_TYPE_E e_type;
   BinaryTree_CMP compare;
} BINARY_TREE_SUPPORTED_CMP_S;


typedef struct BinaryTreeAPI {
   BinaryTree_INSERT insert;
   BinaryTree_DELETE delete;
   BinaryTree_FIND find;
   BinaryTree_FREE free_node;
   // support user define
   BinaryTree_CMP compare;
   BinaryTree_PRINT print_val;
   UserDefineFree user_def_free;
} BinaryTreeAPI;

struct BinaryTreeNode{
   void *p_val;
//BINARY_TREE_VAL_TYPE_E e_val_type;
   struct BinaryTreeNode *p_left;
   struct BinaryTreeNode *p_right;
};

typedef struct BinaryTree{
   BinaryTreeNode *p_root;
   size_t val_size;
   BINARY_TREE_VAL_TYPE_E e_val_type;
   BinaryTreeAPI apis;
}BinaryTree;

// Constructors
BinaryTree* binary_tree_construct(BINARY_TREE_VAL_TYPE_E e_val_type, size_t val_size);
BinaryTree* binary_tree_construct_from_array(void* array, BINARY_TREE_VAL_TYPE_E e_val_type, size_t val_size);
bool binary_tree_set_print_func(BinaryTree *p_tree, BinaryTree_PRINT p_func);
bool binary_tree_set_cmp_func(BinaryTree *p_tree, BinaryTree_CMP p_func);
bool binary_tree_set_free_func(BinaryTree *p_tree, UserDefineFree p_func);

#endif /* __BINARY_TREE_H__ */
