/**
 * @author ECE 3058 TAs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lrustack.h"

/**
 * This file contains some starter code to get you started on your LRU implementation. 
 * You are free to implement it however you see fit. You can design it to emulate how this
 * would be implemented in hardware, or design a purely software stack. 
 * 
 * We have broken down the LRU stack's
 * job/interface into two parts:
 *  - get LRU: gets the current index of the LRU block
 *  - set MRU: sets a certain block's index as the MRU. 
 * If you implement it using these suggestions, you will be able to test your LRU implementation
 * using lrustacktest.c
 * 
 * NOTES: 
 *      - You are not required to use this LRU interface. Feel free to design it from scratch if 
 *      that is better for you.
 *      - This will not behave like your traditional LIFO stack  
 */

/**
 * Function to initialize an LRU stack for a cache set with a given <size>. This function
 * creates the LRU stack. 
 * 
 * @param size is the size of the LRU stack to initialize. 
 * @return the dynamically allocated stack. 
 */
lru_stack_t* init_lru_stack(int size) {
    //  Use malloc to dynamically allocate a lru_stack_t
    //printf("Initializing LRU Stack\n");
	lru_stack_t* stack = (lru_stack_t*) malloc(sizeof(lru_stack_t));
    //  Set the stack size the caller passed in
	stack->size = size;
    
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write any other code needed to initialize your LRU Stack. 
    //  Essentially write any initializations needed for anything you
    //  added to lru_stack_t.
    ////////////////////////////////////////////////////////////////////
    stack->head = NULL;
    stack->tail = NULL;
    //printf("Initializing LRU Stack\n");
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////

	return stack;
}

/**
 * Function to get the index of the least recently used cache block, as indicated by <stack>.
 * This operation should not change/mutate your LRU stack. 
 * 
 * @param stack is the stack to run the operation on.
 * @return the index of the LRU cache block.
 */
int lru_stack_get_lru(lru_stack_t* stack) {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write code to get the index of the LRU block from the LRU 
    //  Stack. 
    ////////////////////////////////////////////////////////////////////
    printf("Getting LRU index from stack \n");
    //Ashan's change
    if  (stack != NULL) {
        if(stack->tail != NULL){  //if index is present in tail
            return stack->tail->index; // retireve index
        }
    }
    else {
        return -1; // otherwise return index -1 as LRU is empty
    }
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
}

/**
 * Function to mark the cache block with index <n> as MRU in <stack>. This operation should
 * change/mutate the LRU stack.
 * 
 * @param stack is the stack to run the operation on.
 * @param n the index to promote to MRU.  
 */
void lru_stack_set_mru(lru_stack_t* stack, int n) {
	////////////////////////////////////////////////////////////////////
    //  TODO: Write code to set the passed in block index  as the MRU 
    //  element in the LRU Stack. 
    ////////////////////////////////////////////////////////////////////
    ///Ashans change
    // Check if the stack is empty
    printf("Setting MRU index in stack \n");
    if (stack->head == NULL) {
        // Create a new node with the given index and set it as MRU
        Node* new_node = (Node*) malloc(sizeof(Node));
        new_node->index = n;
        new_node->next = NULL;
        new_node->prev = NULL;
        stack->head = new_node;
        stack->tail = new_node;
        return;
    }
    
    // Find the node with the given index
    Node* current = stack->head;
    while (current != NULL && current->index != n) {
        current = current->next;
    }
    
    // If the node is not found, add to head as MRU
    if (current == NULL) {
        current = (Node*) malloc(sizeof(Node));
        current->index = n;
        current->next = stack->head;
        current->prev = NULL;
        stack->head->prev = current;
        stack->head = current;
    } else {
        // If the node is the tail, update the tail pointer
        if (current == stack->tail) {
            stack->tail = current->prev;
        }
        
        // Remove the node from its current position
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        
        // Move the node to the front
        current->next = stack->head;
        current->prev = NULL;
        stack->head->prev = current;
        stack->head = current;
    }

    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
}

/**
 * Function to free up any memory you dynamically allocated for <stack>
 * 
 * @param stack the stack to free
 */
void lru_stack_cleanup(lru_stack_t* stack) {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write any code if you need to do additional heap allocation
    //  cleanup
    ////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////

    free(stack);        // Free the stack struct we malloc'd
}