/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Binary Search Tree implementation
 */

#include "bst.h"
#include "utils.h"

static bst_node_t *__bst_node_create(char *data)
{
    char *rc;
    bst_node_t *bst_node;

    bst_node = malloc(sizeof(bst_node_t));
    DIE(bst_node == NULL, "bst_node malloc");

    bst_node->left = bst_node->right = NULL;

    bst_node->data = calloc(BST_DATA_LEN, sizeof(char));
    DIE(bst_node->data == NULL, "bst_node->data malloc");

    rc = strncpy(bst_node->data, data, BST_DATA_LEN - 1);
    DIE(rc != bst_node->data, "bst_node->data strncpy");

    return bst_node;
}

bst_tree_t *bst_tree_create(int (*cmp_f) (const char *, const char *))
{
    bst_tree_t *bst_tree;

    bst_tree = malloc(sizeof(bst_tree_t));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree->root  = NULL;
    bst_tree->cmp   = cmp_f;

    return bst_tree;
}

void bst_tree_insert(bst_tree_t *bst_tree, char *data)
{
    int rc;
    bst_node_t *root    = bst_tree->root;
    bst_node_t *parent  = NULL;
    bst_node_t *node    = __bst_node_create(data);

    if (root == NULL) {
        bst_tree->root = node;
        return;
    }

    parent = root;
    while (1) {
        rc = bst_tree->cmp(node->data, parent->data);

        if (rc < 0) {
            if (parent->left) {
                parent = parent->left;
            } else {
                parent->left = node;
                break;
            }
        } else {
            if (parent->right) {
                parent = parent->right;
            } else {
                parent->right = node;
                break;
            }       
        }
    }
}

static bst_node_t *__pred_inorder(bst_node_t *node)
{
    struct bst_node_t* curr = node; 
  
    while (curr && curr->right != NULL) { 
        curr = curr->right;
    }
  
    return curr; 
}

static bst_node_t *__succ_inorder(bst_node_t *node)
{
    struct bst_node_t* curr = node; 
  
    while (curr && curr->left != NULL) { 
        curr = curr->left;
    }
  
    return curr; 
}

static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
                                    char *data,
                                    int (*f) (const char *, const char *))
{
    int rc;
    bst_node_t *tmp;

    if (!bst_node) {
        return NULL;
    }

    rc = f(data, bst_node->data);

    if (rc < 0)
    {
        bst_node->left =  __bst_tree_remove(bst_node->left, data, f);
    }
    else if (rc > 0)
    {
        bst_node->right = __bst_tree_remove(bst_node->right, data, f);
    }
    else
    {
        // nod cu un singur copil sau fara copii
        if (bst_node->left == NULL)
        {
            tmp = bst_node->right;
            free(bst_node->data);
            free(bst_node);
            return tmp;
        }
        else if (bst_node->right == NULL)
        {
            tmp = bst_node->left;
            free(bst_node->data);
            free(bst_node);
            return tmp;
        }

        // nod cu 2 copii
        bst_node_t *max_left = __pred_inorder(bst_node->left);
        bst_node_t *min_right = __succ_inorder(bst_node->right);

        if ( f(data, max_left->data) > f(min_right->data, data) )
        {
            memcpy(bst_node->data, min_right->data, strlen(min_right->data));
            bst_node->right = __bst_tree_remove(bst_node->right, min_right->data, f);
        }
        else
        {
            memcpy(bst_node->data, max_left->data, strlen(max_left->data));
            bst_node->left = __bst_tree_remove(bst_node->left, max_left->data, f);
        }  
    }

    return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, char *data)
{
    bst_tree->root = __bst_tree_remove(bst_tree->root, data, bst_tree->cmp);
}

static void __bst_tree_free(bst_node_t *bst_node)
{
	if (bst_node == NULL) {
		return;
    }
	__bst_tree_free(bst_node->left);
	__bst_tree_free(bst_node->right);

	free(bst_node->data);
	free(bst_node);
}

void bst_tree_free(bst_tree_t *bst_tree)
{
    __bst_tree_free(bst_tree->root);
    free(bst_tree);
}
