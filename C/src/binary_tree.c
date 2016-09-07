/*
   File: binary_tree.c
   Description:
      implementation of the APIs defined in binary_tree.h
   Date: Sep 3 2016
   Author: Lixing Zhang
*/
#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

/****************  STATIC FUNCTIONS *****************/
/* Brief: 
      insert val into binary tree
   parameters:
      p_tree - tree structure
      p_val - val to insert
      val_size - size of the val in byte
   return:
      true - val inserted into tree
      false - failed to insert or already existed in the tree
*/
static bool BinaryTreeInsert(BinaryTree *p_tree, void* p_val)
{
   bool inserted = false;
   BinaryTreeNode **p_new_node = NULL;
   BinaryTreeNode *p_node = p_tree->p_root;
   int cmp = p_tree->apis.compare(p_node->p_val, p_val);
   while(0 != cmp)
   {
      if(cmp == 1)
      {
         if(NULL != p_node->p_left)
         {
            p_node = p_node->p_left;
         }
         else
         {
            p_new_node = &p_node->p_left; 
            break;
         }
      }
      else if(cmp == -1)
      {
         if(NULL != p_node->right)
         {
            p_node = p_node->right;
         }
         else
         {
            p_new_node = &p_node->right;
            break;
         }
      }
      cmp = p_tree->apis.compare(p_node->p_val, p_val);
   }
   if(0 == cmp)
   {
      printf("Val: %s was in the Tree\n", p_tree->apis.print_val(p_val));
   }
   else
   {
      *p_new_node = calloc(1, sizeof(*p_node));
      (*p_new_node)->p_val = calloc(1, p_tree->val_size);
      memcpy((*p_new_node)->p_val, p_val, p_tree->val_size);
      inserted = true;
   }
   return inserted;
}

static BinaryTreeNode* BinaryTreeFind(BinaryTree p_tree, void* p_target, BINARY_TREE_FIND_TYPE_E e_type, BinaryTreeNode **p_parent)
{
   BinaryTreeNode *p_found = NULL;
   BinaryTreeNode *p_node = p_tree->p_root;
   switch(e_type)
   {
      case eBINARY_TREE_FIND_TYPE_TARGET:
      {
         int cmp = p_tree->apis.compare(p_node->p_val, p_val);
         while(0 != cmp)
         {
            if(NULL != p_parent)
            {
               *p_parent = p_tree->p_root;
            }

            if(cmp == 1)
            {
               if(NULL != p_node->p_left)
               {
                  p_node = p_node->p_left;
               }
               else
               {
                  break;
               }
            }
            else if(cmp == -1)
            {
               if(NULL != p_node->right)
               {
                  p_node = p_node->right;
               }
               else
               {
                  break;
               }
            }
            cmp = p_tree->apis.compare(p_node->p_val, p_val);
         }

         if(0 == cmp)
         {
            p_found = p_node;
         }
         break;
      }
      default:
      {
         printf("find type <%d> for target<%s> FAILED", e_type, p_tree->apis.print_val(p_target));
         break;
      }
   }
   return p_found;
}

static bool BinaryTreeDelete(BinaryTree *p_tree, void* p_target)
{
   bool deleted = false;
   BinaryTreeNode *p_target_parent = NULL;
   BinaryTreeNode *p_rep_parent = NULL;

   BinaryTreeNode *p_target_node = p_tree->apis.find(p_tree, p_target, eBINARY_TREE_FIND_TYPE_TARGET, &p_target_parent);
   BinaryTreeNode *p_replacement = NULL;
   if(NULL != p_target_node)
   {
      p_replacement = BinaryTreeDeleteFindReplacement(p_tree, p_target, &p_rep_parent);
      if(p_replacement == p_target_node)
      {
         p_tree->apis.free_node(p_target_node, p_tree->apis.user_def_free);
         if(NULL != p_target_parent)
         {
            if(p_target_parent->p_left == p_target_node)
            {
               p_target_parent->p_left = NULL;
            }
            else if(p_target_parent->p_right == p_target_node)
            {
               p_target_parent->p_right = NULL;
            }
         }
         else
         {
            p_tree->p_root = NULL;
         }
         p_target_node = NULL;
      }
      else
      {
         memcpy(p_target_node->p_val, p_replacement->p_val, p_tree->val_size);
         BinaryTreeDelete(p_replacement, p_replacement, &p_rep_parent);
      }
   }
   else
   {
      printf("%s was not found in tree", p_tree->apis.print_val(p_target));
   }
   return deleted;
}

static BinaryTreeNode *BinaryTreeDeleteFindReplacement(BinaryTreeNode *p_node, void *p_val, BinaryTreeNode **p_parent)
{
   BinaryTreeNode *p_rep = NULL;
   if(NULL != p_node->p_left)
   {
      if(NULL != p_parent)
      {
         *p_parent = p_node;
      }
      p_node = p_node->p_left;
      while(NULL != p_node->p_right)
      {
         if(NULL != p_parent)
         {
            *p_parent = p_node;
         }
         p_node = p_node->p_right;
      }
      p_ret = p_node;
   }
   else if((NULL == p_ret)&&(NULL != p_node->p_right))
   {
      if(NULL != p_parent)
      {
         *p_parent = p_node;
      }
      p_node = p_node->p_right;
      while(NULL != p_node->p_left)
      {
         if(NULL != p_parent)
         {
            *p_parent = p_node;
         }
         p_node = p_node->p_left;
      }
      p_ret = p_node;

   }
   if(NULL == p_rep)
   {
      p_rep = p_node;
   }
   return p_rep;
}

static void BinaryTreeFree(BinaryTreeNode *p_node, UserDefineFree free_func)
{
   assert_or_return(NULL != p_node, VOID_RETURN)
   if(NULL == free.func)
      free(p_node->p_val);
   else
      free_func(p_node->p_val);
   free(p_node);
}
/****************  PUBLIC APIS *******************/
BinaryTree* binary_tree_construct(BINARY_TREE_VAL_TYPE_E e_val_type, size_t val_size)
{
   BinaryTree *p_ret = NULL;
   assert_or_return(e_val_type < eVAL_TYPE_MAX, NULL);
   
   p_ret = calloc(1, sizeof(*p_ret));
   if(NULL != p_ret)
   {
      p_ret->p_root = NULL;
      p_ret->e_val_type = (e_val_type >= eVAL_TYPE_MAX)? eVAL_TYPE_LONG : e_val_type;
      p_ret->val_size = val_size;
      binary_tree_set_api(p_ret);
   }
   return p_ret;
}

BinaryTree* binary_tree_construct_from_array(void* array, BINARY_TREE_VAL_TYPE_E e_val_type, size_t val_size)
{
   BinaryTree *p_ret = NULL;
   //TODO
   printf("%s(): NOT SUPPORTED YET :D\n");
   return p_ret;
}

bool binary_tree_set_print_func(BinaryTree *p_tree, BinaryTree_PRINT p_func)
{
   assert_or_return(NULL != p_tree, false);
   p_tree->apis.print_val = p_func;
}

bool binary_tree_set_cmp_func(BinaryTree *p_tree, BinaryTree_CMP p_func);
{
   assert_or_return(NULL != p_tree, false);
   p_tree->apis.compare = p_func;
}

bool binary_tree_set_free_func(BinaryTree *p_tree, UserDefineFree p_func);
{
   assert_or_return(NULL != p_tree, false);
   p_tree->apis.user_def_free = p_func;
}
