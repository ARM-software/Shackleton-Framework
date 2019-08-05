/*
 ============================================================================
 Name        : osaka.h
 Author      : Andrew Sloss, Hannah Peeler
 Version     : 1.0
 Copyright   : 
 
    Copyright 2019 Arm Inc., Andrew Sloss, Hannah Peeler

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Please refer to 
    https://github.com/ARM-software/Shackleton-Framework/blob/master/LICENSE.TXT
    for a full overview of the license covering this work.
    
 Description : Group of functions supporting the Osaka list specifically developed for Linear
                Genetic Programming (LGP).
 History :
    Andrew N. Sloss July 31st 2018
        -- starting creating the design for osaka
    
    Hannah Peeler June 3rd 2019
        -- began editing for use within Project Shackleton Framework
 ============================================================================
 */

#ifndef OSAKA_H_
#define OSAKA_H_

/*
 * IMPORT
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "../module/modules.h"
#include "../support/utility.h"

/*
 * DATATYPES
 */

typedef enum    {
    EMPTY = 0,
    ISOLATE = 1,
    HEADNODE = 2,
    TAILNODE = 3,
    INTERMEDIATE = 4
} osaka_node_typ;

typedef enum    {
    NOTSET = -1,
    SIMPLE = 0,
    ASSEMBLER = 1,
    OSAKA_STRING = 2,
    LLVM_PASS = 3,
	BINARY_UP_TO_512 = 4
} osaka_object_typ;

typedef enum    {
    HEAD = 1,
    TAIL = 2,
} append_typ;

typedef struct node_str {
    uint32_t uid;
    osaka_object_typ objtype;
    void *object_ptr;
    struct node_str *last_ptr;
    struct node_str *next_ptr;
    struct node_str *last_link;
    struct node_str *next_link;
} node_str;

/*
 * MACROS
 */

#define NEXT(s) s->next_ptr
#define LAST(s) s->last_ptr
#define NEXT_LINK(s) s->next_link
#define LAST_LINK(s) s->last_link
#define OBJECT(s) s->object_ptr
#define OBJECT_TYPE(s) s->objtype
#define UID(s) s->uid

#define DEBUG(s)  if (debug) printf(s);

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   osaka_uid
 *
 * DESCRIPTION
 *
 *  This function increments an internal counter and returns a unique
 *  value. Normally useful for initial development and debugging. It
 *  limits the size of the list to 2^31.
 *
 * PARAMETERS
 *
 *  none...
 *
 * RETURN
 *
 *  new uid value
 *
 * EXAMPLE
 *
 * UID(n) = osaka_uid();
 *
 * SIDE-EFFECT
 *
 *  updates uid static variable
 *
 */

uint32_t osaka_uid(void);

/*
 * NAME
 *
 *   osaka_whatisnode
 *
 * DESCRIPTION
 *
 *  This function returns the node type i.e. EMPTY, ISOLATE, HEADNODE,
 *  TAILNODE or INTERMEDIATE.
 *
 *  EMPTY corresponds to an empty list i.e. NULL
 *  ISOLATE corresponds to both last_ptr and next_ptr are NULL
 *  HEADNODE corresponds to last_ptr is NULL and next_ptr is non-NULL
 *  TAILNODE corresponds to next_ptr is NULL and last_ptr is non-NULL
 *  INTERMEDIATE corresponds to both next_ptr and last_ptr being non-NULL
 *
 * PARAMETERS
 *
 *  node_str *n - pointer to a node
 *
 * RETURN
 *
 *  osaka_node_typ {EMPTY,ISOLATE,HEADNODE,TAILNODE,INTERMEDIATE}
 *
 * EXAMPLE
 *
 *  switch(osaka_whatisnode(n))
 *  {
 *  case EMPTY: ...
 *
 * SIDE-EFFECT
 *
 *  no side effect
 *
 */

osaka_node_typ osaka_whatisnode(node_str *n);

/*
 * NAME
 *
 *   osaka_findtailnode
 *
 * DESCRIPTION
 *
 *  This function finds the tail node of the OLS. When the tail is found 
 *  the pointer is returned of the tail node.  
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 * 
 * RETURN
 *
 *  node_str * - tail node is returned 
 *
 * EXAMPLE
 *
 *   tail=osaka_findtailnode(root);
 *
 * SIDE-EFFECT
 *
 *  asserts if the root node is NULL. 
 *
 */

node_str *osaka_findtailnode(node_str *root);

/*
 * NAME
 *
 *  osaka_findheadnode
 *
 * DESCRIPTION
 *
 *  osaka_findheadnode return the root node given an arbitrary node in the list.
 *
 * PARAMETERS
 *
 *  node_str *n
 *
 * RETURN
 *
 *  node_str * - root node
 *
 * EXAMPLE
 *
 *  root=osaka_rootnode(n);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

node_str *osaka_findheadnode(node_str *n);

/*
 * NAME
 *
 *   osaka_addnodetotail
 *
 * DESCRIPTION
 *
 *   This function adds a single node to the tail. Takes the root of the list and goes
 *   to the end of the list and appends the node.
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *  node_str *n - new node
 *
 * RETURN
 *
 * root anchor is returned
 *
 * EXAMPLE
 *
 * root = osaka_addnodetotail(root,new_node);
 *
 * SIDE-EFFECT
 *
 * asserts if either new node or root are NULL
 *
 */

node_str *osaka_addnodetotail(node_str *r,node_str *n);

/*
 * NAME
 *
 *   osaka_addnodetohead
 *
 * DESCRIPTION
 *
 *   This function adds a single node to the head. Takes the root of the list and
 *   appends the new node to the head of the list.
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *  node_str *n - new node
 *
 * RETURN
 *
 * root anchor is returned
 *
 * EXAMPLE
 *
 * root = osaka_addnodetohead(root,new_node);
 *
 * SIDE-EFFECT
 *
 * asserts if either new node or root are NULL
 *
 */

node_str *osaka_addnodetohead(node_str *r,node_str *n);

/*
 * NAME
 *
 *   osaka_createnode
 *
 * DESCRIPTION
 *
 *   This function creates a node and places it either at the head or tail. If the root
 *   is empty the function returns a node.
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *  node_str *n - new node
 *
 * RETURN
 *
 * root anchor is returned
 *
 * EXAMPLE
 *
 * root = osaka_createnode(root,TAIL,SIMPLE);
 *
 * OR
 *
 * root = osaka_createnode(root,HEAD,ASSEMBLER);
 *
 * SIDE-EFFECT
 *
 * update the root list.
 *
 */

node_str *osaka_createnode(node_str *r,append_typ app_ty,osaka_object_typ ot);

/*
 * NAME
 *
 *  osaka_printnode
 *
 * DESCRIPTION
 *
 *  This function print out a single node.
 *
 * PARAMETERS
 *
 *  node_str *n - node to printed out
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_printnode(n);
 *
 * SIDE-EFFECT
 *
 *  print out a node
 *
 */

void osaka_printnode(node_str *n);

/*
 * NAME
 *
 *  osaka_printnode_concise
 *
 * DESCRIPTION
 *
 *  This function print out a single node with only its internals.
 *
 * PARAMETERS
 *
 *  node_str *n - node to printed out
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_printnode_concise(n);
 *
 * SIDE-EFFECT
 *
 *  print out a node
 *
 */

void osaka_printnode_concise(node_str *n);

/*
 * NAME
 *
 *  osaka_describenode
 *
 * DESCRIPTION
 *
 *  This function loads a char* variable with a description of the value of the node
 *
 * PARAMETERS
 *
 *  char* desc - variable to load the description into
 *  node_str *n - node to be described
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_describenode(output, n);
 *
 * SIDE-EFFECT
 *
 *  changes the value of desc
 *
 */

void osaka_describenode(char* desc, node_str *n);

/*
 * NAME
 *
 *  osaka_printnodearray
 *
 * DESCRIPTION
 *
 *  This function prints out every node in a node_str
 *  array, starting from the head.
 *
 * PARAMETERS
 *
 *  node_str *n - head of node array to be printed
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_printnodearray(n);
 *
 * SIDE-EFFECT
 *
 *  print out a node array
 *
 */

void osaka_printnodearray(node_str *n);

/*
 * NAME
 *
 *   osaka_prefix_maptop
 *
 * DESCRIPTION
 *
 *  Recurses through the list applying function prototype in order
 *  i.e. head first
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *  void (*fun)(node_str *n) - function prototype
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_prefix_maptop(root,osaka_printnode);
 *
 * SIDE-EFFECT
 *
 *  fun is applied to all the nodes in the list
 *
 */

void osaka_prefix_mapto(node_str *n,void (*fun)(node_str *n));

/*
 * NAME
 *
 *
 * DESCRIPTION
 *
 *
 * PARAMETERS
 *
 *
 * RETURN
 *
 *
 * EXAMPLE
 *
 *
 * SIDE-EFFECT
 *
 *
 */
 

bool recurse_applytonode(node_str *root,bool (*fun)(node_str *n));


/*
 * NAME
 *
 *   osaka_postfix_maptop
 *
 * DESCRIPTION
 *
 *   Recurses through the list applying function prototype in reverse
 *   order i.e. tail first
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *  void (*fun)(node_str *n) - function prototype
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_postfix_maptop(root,free);
 *
 * SIDE-EFFECT
 *
 *  fun is applied to all nodes in the list in reverse order
 *
 */

void osaka_postfix_mapto(node_str *n,void (*fun)(node_str *n));

/*
 * NAME
 *
 *  osaka_listlength
 *
 * DESCRIPTION
 *
 *  osaka_listlength takes a list and returns the length. Return zero if list has no nodes.
 *
 * PARAMETERS
 *
 *  node_str *r - root anchor for the list
 *
 * RETURN
 *
 *  returns the length of the list
 *
 * EXAMPLE
 *
 *  len=osaka_listlength(root);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

uint32_t osaka_listlength(node_str *r);

/*
 * NAME
 *
 *  osaka_freenode
 *
 * DESCRIPTION
 *
 *  osaka_freenode takes a node_ptr and frees the memory area.
 *
 * PARAMETERS
 *
 *  node_str *n - node to be released
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_freenode(n);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

void osaka_freenode(node_str *n);

/*
 * NAME
 *
 *  osaka_randomizenode
 *
 * DESCRIPTION
 *
 *  Takes in a node_ptr and randomizes all the parameters inside 
 *  that node_ptr's object
 *
 * PARAMETERS
 *
 *  none...
 *
 * RETURN
 *
 *  node_str * - existing osaka node
 *
 * EXAMPLE
 *
 *  osaka_randomizenode(rand_node)
 *
 * SIDE-EFFECT
 *
 *  side-effect are that the node is updated
 *  by changing the values in the object
 *
 */


void osaka_randomizenode(node_str *n);

/*
 * NAME
 *
 *  osaka_fitness
 *
 * DESCRIPTION
 *
 *  Takes in a node_ptr and calculates the fitness of
 *  the individual starting at that node
 *
 * PARAMETERS
 *
 *  none...
 *
 * RETURN
 *
 *  node_str * - existing osaka node
 *
 * EXAMPLE
 *
 *  osaka_fitness(rand_node)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */


uint32_t osaka_fitness(node_str *n);

/*
 * NAME
 *
 *  osaka_nthnode
 *
 * DESCRIPTION
 *
 *  osaka_nthnode return nth node in the list.
 *
 * PARAMETERS
 *
 *  node_str *r
 *  uint32_t nth - nth node
 *
 * RETURN
 *
 *  node_str * - nth node
 *
 * EXAMPLE
 *
 *  root=osaka_nthnode(n,1);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

node_str *osaka_nthnode(node_str *r,uint32_t nth);

/*
 * NAME
 *
 *  osaka_deletenode
 *
 * DESCRIPTION
 *
 *  osaka_deletenode deletes a node from a list
 *
 * PARAMETERS
 *
 *  node_str *n
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  root=osaka_deletenode(root);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

node_str *osaka_deletenode(node_str *n);

/*
 * NAME
 *
 *  osaka_serialize
 *  
 * DESCRIPTION
 *
 * 
 *
 * PARAMETERS
 *
 *
 * RETURN
 *
 *
 * EXAMPLE
 *
 *
 * SIDE-EFFECT
 *
 *
 */

uint32_t osaka_serialize(node_str *r,char *filepath);

/*
 * NAME
 *
 *  osaka_deserialize
 *  
 * DESCRIPTION
 *
 * 
 *
 * PARAMETERS
 *
 *
 * RETURN
 *
 *
 * EXAMPLE
 *
 *
 * SIDE-EFFECT
 *
 *
 */

node_str *osaka_deserialize(char *filepath);

/*
 * NAME
 *
 *  osaka_compare
 *  
 * DESCRIPTION
 *
 * 
 *
 * PARAMETERS
 *
 *
 * RETURN
 *
 *
 * EXAMPLE
 *
 *
 * SIDE-EFFECT
 *
 *
 */

bool osaka_compare(node_str *n0, node_str *n1);
    
/*
 * NAME
 *
 *  osaka_consistencycheck
 *  
 * DESCRIPTION
 *
 * 
 *
 * PARAMETERS
 *
 *
 * RETURN
 *
 *
 * EXAMPLE
 *
 *
 * SIDE-EFFECT
 *
 *
 */
   
bool osaka_consistencycheck(node_str *r);

/*
 * NAME
 *
 *  osaka_copylist
 *  
 * DESCRIPTION
 *
 *  Constructs a replica of a list and returns a return to the replicated 
 *  list.
 *
 * PARAMETERS
 *
 *  node_str *
 *
 * RETURN
 *
 *  node_str *
 *
 * EXAMPLE
 *
 *  new=osaka_copylist(r0);
 *
 * SIDE-EFFECT
 *
 *  Allocates memory for the data structure. 
 *
 */

node_str *osaka_copylist(node_str *r);

/*
 * NAME
 *
 *  osaka_freelist  
 *
 * DESCRIPTION
 *
 *  This function recursively frees the nodes of a list. 
 *
 * PARAMETERS
 *
 *  node_str * - root 
 *
 * RETURN
 *
 *  NULL, pointer
 *
 * EXAMPLE
 *
 *  r0=osaka_freelist(r0);
 *
 * SIDE-EFFECT
 *
 *  frees every node in the osaka list.
 *
 */

node_str *osaka_freelist(node_str *r);

/*
 * NAME
 *
 *  osaka_print_available_object_types
 *
 * DESCRIPTION
 *
 *  Print out all available object types for the user
 *  currently of the Osaka Structure. They are listed in
 *  a numbered list
 *
 * PARAMETERS
 *
 *  none
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  osaka_print_available_object_types();
 *
 * SIDE-EFFECT
 *
 *  prints out information to the console
 * 
 */

void osaka_print_available_object_types();

/*
 * NAME
 *
 *  osaka_init
 *
 * DESCRIPTION
 *
 *  Initialize the osaka library. Debug can be either turned on or off via 
 *  initialization. The initialization process tests out the library 
 *  implementation before returning control. Call this function before 
 *  using the osaka library.
 *
 * PARAMETERS
 *
 *  bool debug_mode // true debug on and false off
 *
 * RETURN
 *
 *  bool - return true if successful...
 *
 * EXAMPLE
 *
 *  if (osaka_init(true))
 *  {
 *  ...
 *  }
 *
 * SIDE-EFFECT
 *
 *  limited side-effects
 * 
 */

bool osaka_init(bool debug_mode);

#endif /* OSAKA_H_ */
