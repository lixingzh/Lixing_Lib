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

typedef enum {
   eBINARY_TREE_FIND_TYPE_TARGET,
   eBINARY_TREE_FIND_TYPE_PREDECESSOR,
   eBINARY_TREE_FIND_TYPE_SUCCESSOR,
   eBINARY_TREE_FIND_TYPE_MAX,
} BINARY_TREE_FIND_TYPE_E;

typedef bool (*BinaryTree_INSERT) (struct BinaryTreeNode *p_root);
typedef bool (*BinaryTree_DELETE) (struct BinaryTreeNode *p_root, void* p_target);
typedef struct BinaryTreeNode* (*BinaryTree_FIND) (struct BinaryTreeNode *p_root, void *p_target, BINARY_TREE_FIND_TYPE_E e_type);

typedef struct BinaryTreeAPI {
   BinaryTree_INSERT insert;
   BinaryTree_DELETE delete;
   BinaryTree_FIND find;
} BinaryTreeAPI;

typedef struct BinaryTreeNode {
   void *p_val;
   struct BinaryTreeNode *p_left;
   struct BinaryTreeNode *p_right;
   BinaryTreeAPI apis;
} BinaryTreeNode;



#endif /* __BINARY_TREE_H__ */
