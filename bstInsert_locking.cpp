/**
 * Implementation for a thread-safe binary search tree
 * 
 * Course: Process Oriented Programming
 * Lab assignment 2: A thread-safe binary search tree
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#include "bst.h"
/**
 * Interface for a thread-safe binary search tree
 *
 * Course: Process Oriented Programming
 * Lab assignment 2: A thread-safe binary search tree
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 */

#ifndef __BST__
#define __BST__

#include <pthread.h>

typedef struct bstNode {
	 pthread_mutex_t mutex;
    int data;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

typedef struct bstTree {
    struct bstNode *root;
} bstTree;

bstTree *bst_new(void);
void bst_delete(bstTree *t);

bstNode *bst_new_node(int data);
void bst_delete_node(bstNode *node);

int bst_insert_node(bstTree *tree, bstNode *node);
int bst_remove_node(bstTree *tree, int data);
int bst_remove_node_ts_cg(bstTree *tree, int data);
int bst_remove_node_ts_fg(bstTree *tree, int data);

void bst_print(bstTree *tree);

#endif /* __BST__ */


/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * c-file-style: "stroustrup"
 * End:
 */

pthread_mutex_t full_mutex = PTHREAD_MUTEX_INITIALIZER;

bstTree *
bst_new(void) {
    bstTree *t;

    t = malloc(sizeof(bstTree));

    t->root = NULL;

    /* Add any further initialization you need for the bstTree here */

    return t;
}

static void
__bst_delete(bstNode *n) {
    if (n == NULL)
        return;

    __bst_delete(n->left);
    __bst_delete(n->right);
    bst_delete_node(n);
}

void
bst_delete(bstTree *t) {
    if (t == NULL)
        return;

    bstNode *n = t->root;
    __bst_delete(n);

    free(t);
}


bstNode *
bst_new_node(int data) {
    bstNode *n;

    n = malloc(sizeof(bstNode));
    if (n == NULL) {
	fprintf(stderr, "Out of memory!\n");
	exit(1);
    }
	 pthread_mutex_t tmp = PTHREAD_MUTEX_INITIALIZER;
    n->left = NULL;
    n->right = NULL;
    n->data = data;
    n->mutex = tmp;

    return n;
}


void 
bst_delete_node(bstNode *n) {
    if (n == NULL) {
	fprintf(stderr, "Invalid node\n");
	return;
    }

    free(n);
}

static void 
__bst_print_preorder(bstNode *n) {
    if (n != NULL) {
        printf("%d ", n->data);
        __bst_print_preorder(n->left);
        __bst_print_preorder(n->right);
   }
}

static void  __attribute__ ((unused)) 
__bst_print_inorder(bstNode *n) {
    if (n != NULL) {
        __bst_print_inorder(n->left);
        printf("%d ", n->data);
        __bst_print_inorder(n->right);
    }
}

void 
bst_print(bstTree *t) {
    __bst_print_preorder(t->root);
    printf("\n");
}


int 
bst_insert_node(bstTree *t, bstNode *n) {
    bstNode *current_node;
    bstNode **current_ptr;

    if (t == NULL) {
	fprintf(stderr, "Invalid BST.\n");
	return 1;
    }

    // assert(!n->left && !n->right);
    //assert(t != NULL);

    current_ptr = &t->root;

    while (*current_ptr) {
	current_node = *current_ptr;
	if (n->data < current_node->data) {
	    current_ptr = &current_node->left;
	} else if (n->data > current_node->data) {
	    current_ptr = &current_node->right;
	} else {
	    // already present
	    return 1;
	}
    }

    *current_ptr = n;

    return 0;
}

static int 
fg_bst_min(bstNode *n) {
    
    if (n->left != NULL)
    {
    
	 pthread_mutex_lock(&n->left->mutex);	// Lock current nod
	 pthread_mutex_unlock(&n->mutex);	// Unlock parent node
	 return fg_bst_min(n->left);
	}
    else
    {
    	pthread_mutex_unlock(&n->mutex);	// Unlock parent node
		return n->data;
	}
}

static bstNode *
fg_bst_remove_node(bstNode *current, bstNode *parent, int data) {
	/* Separat fall fÃ¶r fÃ¶rsta rekursionsanropet */
   if (data < current->data) {
		if (current->left != NULL)
		{
			if(parent != NULL)
			{
		 	 	pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
		 	 	pthread_mutex_lock(&current->left->mutex);	// Lock current node
	   	 	return fg_bst_remove_node(current->left, current, data);
	   	}
	   	else
	   	{
	   		pthread_mutex_lock(&current->left->mutex);	// Lock current node
	   		return fg_bst_remove_node(current->left, current, data);
	   	}
		}
		else
		{
			 pthread_mutex_unlock(&current->mutex);	// Unlock current node
			 if(parent != NULL)
			 {
		 	 	pthread_mutex_unlock(&parent->mutex);	// Unlock parent node'
		 	 }
	   	 return NULL;
	   }
   } 
   else if (data > current->data) {
		if (current->right != NULL)
		{
			if(parent != NULL)
			{
			 	pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
				pthread_mutex_lock(&current->right->mutex);	// Lock current node
				return fg_bst_remove_node(current->right, current, data);
			}
			else {
		 		pthread_mutex_lock(&current->right->mutex);	// Lock current node
	    		return fg_bst_remove_node(current->right, current, data);
	    	}
	 	}
		else
		{
		 	pthread_mutex_unlock(&current->mutex);	// Unlock current node
		 	if(parent != NULL)
			{
		 		pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
		 	}
	    	return NULL;
   	} 
   }
   else {
	// Node found
	if (current->left != NULL && current->right != NULL) {
		 
		 pthread_mutex_lock(&current->right->mutex);	// Unlock parent node
	    int new_data = fg_bst_min(current->right);
	    current->data = new_data;
	    
	    if(parent != NULL)
		 {
		 	pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
		 }
		 pthread_mutex_lock(&current->right->mutex);	// Lock current node	    
	    return fg_bst_remove_node(current->right, current, new_data);
	} else if (parent->left == current) {
		 
	    parent->left =  
		(current->left != NULL) ? current->left : current->right;
		
		 pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
	    return current;
	} else if (parent->right == current) {    
	    
	    parent->right = 
		(current->left != NULL) ? current->left : current->right;
		
		 pthread_mutex_unlock(&parent->mutex);	// Unlock parent node
	    return current;
	}
    }

    /* We shouldn't reach this point */

    //assert(0);

    return NULL;
}


static int 
__bst_min(bstNode *n) {
    if (n->left != NULL)
	return __bst_min(n->left);
    else
	return n->data;
}


static bstNode *
__bst_remove_node(bstNode *current, bstNode *parent, int data) {
   if (data < current->data) {
		if (current->left != NULL)
	   	 return __bst_remove_node(current->left, current, data);
		else
	   	 return NULL;
   } else if (data > current->data) {
	if (current->right != NULL)
	    return __bst_remove_node(current->right, current, data);
	else
	    return NULL;
   } 
   else {
	// Node found
	if (current->left != NULL && current->right != NULL) {
		 
	    int new_data = __bst_min(current->right);
	    current->data = new_data;
	    return __bst_remove_node(current->right, current, new_data);
	} else if (parent->left == current) {
	    parent->left =  
		(current->left != NULL) ? current->left : current->right;
	    return current;
	} else if (parent->right == current) {
	    parent->right = 
		(current->left != NULL) ? current->left : current->right;
	    return current;
	}
    }

    /* We shouldn't reach this point */
    //assert(0);

    return NULL;
}

int 
bst_remove_node(bstTree *t, int data) {
	 
    int error;

    if (t == NULL) {
	fprintf(stderr, "Invalid BST.\n");
	return 1;
    }

    bstNode *root = t->root;
    if (root == NULL)
        return 1;

    if (root->data == data) {
	bstNode *aux_root = bst_new_node(0);
	aux_root->left = root;
	bstNode *removed = __bst_remove_node(root, aux_root, data);	
	t->root = aux_root->left;
	assert(removed != NULL);
	error = 0;
	
	/* Critical section */
	bst_delete_node(removed);
    } else {
	bstNode *removed = __bst_remove_node(root, NULL, data);
	if (removed != NULL) {
	    error = 0;
	    
	    /* Critical section */
	    bst_delete_node(removed);
	} else {
	    //printf("Value %d not found in the BST.\n", data);
	    error = 1;
	}
    }

    /* Returns 0 if the removal was successful, > 0 otherisize */
    return error;
}

int 
bst_remove_node_ts_cg(bstTree *t, int data) {
    /* TODO: Implement a thread-safe function which removes nodes from
       the binary search tree. In this function you can follow the
       naive approach and use a big lock which ensures exclusive
       access to the binary tree */

    int error = 1;
    
	pthread_mutex_lock(&full_mutex);    
   //printf("Lock acquired! \n");
    if (t == NULL) {
	fprintf(stderr, "Invalid BST.\n");
	pthread_mutex_unlock(&full_mutex);
	//printf("Lock released! \n");
	return 1;
    }

    bstNode *root = t->root;
    if (root == NULL)
    {
    		pthread_mutex_unlock(&full_mutex);
//printf("Lock released! \n");
        	return 1;
	}
    if (root->data == data) {
	bstNode *aux_root = bst_new_node(0);
	aux_root->left = root;
	bstNode *removed = __bst_remove_node(root, aux_root, data);	
	t->root = aux_root->left;
	//assert(removed != NULL);
	error = 0;
	bst_delete_node(removed);
    } else {
	bstNode *removed = __bst_remove_node(root, NULL, data);
	if (removed != NULL) {
	    error = 0;
	    bst_delete_node(removed);
	} else {
	    //printf("Value %d not found in the BST.\n", data);
	    error = 1;
	}
    }

	pthread_mutex_unlock(&full_mutex);
	//printf("Lock released! \n");
    /* Returns 0 if the removal was successful, > 0 otherisize */
    return error;

}

int 
bst_remove_node_ts_fg(bstTree *t, int data) {
    /* TODO: Implement a thread-safe function which removes nodes from 
       the binary search tree. In this function you may *NOT* use a big lock
       which ensures exclusive access to the binary tree */
 
    int error = 1;
		
    if (t == NULL) {
	fprintf(stderr, "Invalid BST.\n");
	return 1;
    }

    bstNode *root = t->root;
    if (root == NULL)
        return 1;

    if (root->data == data) {
	bstNode *aux_root = bst_new_node(0);
	aux_root->left = root;
	pthread_mutex_lock(&aux_root->mutex);	// lock parent node
	pthread_mutex_lock(&root->mutex);	// lock child node
	bstNode *removed = fg_bst_remove_node(root, aux_root, data);	
	t->root = aux_root->left;
	if(removed == NULL)
		printf("REMOVED blEV NULL");
	//assert(removed != NULL);
	error = 0;
	
	/* Critical section */
	bst_delete_node(removed);
   } 
   else {
   pthread_mutex_lock(&root->mutex);	// lock parent node
	bstNode *removed = fg_bst_remove_node(root, NULL, data);
	if (removed != NULL) {
		
	    error = 0;
	    
	    /* Critical section */
	    bst_delete_node(removed);
	} else {
	    printf("Value %d not found in the BST.\n", data);
	    error = 1;
	}
    }

    /* Returns 0 if the removal was successful, > 0 otherisize */
    return error;
}


/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * c-file-style: "stroustrup"
 * End:
 */
