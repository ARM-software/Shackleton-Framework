/*
 ============================================================================
 Name        : osaka.c
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
    
 Description : Group of functions supporting the Osaka List Structure (OLS) specifically 
                developed for Linear Genetic Programming (LGP). This library provides a 
                set of base functions for manipulating the OLS.
 History :
    Andrew N. Sloss July 31st 2018
        -- starting creating the design for osaka
    
    Hannah M. Peeler June 3rd 2019
        -- edited to get rid of warnings during make, did so
           by changing (unsigned int) casts to (unsigned long)
           casts to get rid of size mismatch
        -- edited formatting for my own readability
 ============================================================================
 */

/*
 * IMPORT ...
 */

#include "osaka.h"
#include "osaka_test.h"
#include <string.h>

/*
 * STATIC
 */

bool OSAKA_INIT = false;
bool debug = false;
uint32_t global_nth;

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

uint32_t osaka_uid(void)  {

    static uint32_t uid = 0;

    return ++uid;

}

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

osaka_node_typ osaka_whatisnode(node_str *n)  {
  
    if (n==NULL) return EMPTY;

    if (LAST(n)==NULL && NEXT(n)==NULL) return ISOLATE;

    if (LAST(n)==NULL && NEXT(n)!=NULL) return HEADNODE;

    if (LAST(n)!=NULL && NEXT(n)==NULL) return TAILNODE;

    return INTERMEDIATE;

}

/*
 * NAME
 *
 *  __osaka_createnode(void)
 *
 * DESCRIPTION
 *
 *  Internal function which creates an OLS node that has the last_ptr, 
 *  next_ptr and object_ptr all set to NULL and object_type is set to NOTSET.
 *
 * PARAMETERS
 *
 *  none...
 *
 * RETURN
 *
 *  node_str * - new osaka node
 *
 * EXAMPLE
 *
 *  new = __osaka_createnode();
 *
 * SIDE-EFFECT
 *
 *  side-effect are that the node is updated
 *
 *  last_ptr = NULL
 *  next_ptr = NULL
 *  object_ptr = NULL
 *  object_type = 0
 *  uid = <uid>
 *
 */


node_str *__osaka_createnode(osaka_object_typ ot) {

    node_str *n;

    n = malloc(sizeof(node_str));

    if (n == NULL)  {
        printf ("error: failed to alloc memory for node_str [file:\'%s\',line:%d]\n",__FILE__,__LINE__);
        exit(0);
    }

    UID(n)=osaka_uid();
    NEXT(n)=NULL;
    LAST(n)=NULL;
    NEXT_LINK(n)=NULL;
    LAST_LINK(n)=NULL;
    OBJECT_TYPE(n)=NOTSET;
    OBJECT(n)=NULL;

    if(ot>=0 && ot<MAXTYPE) {
        OBJECT_TYPE(n)=ot;
        OBJECT(n)=object_table_function[OBJECT_TYPE(n)].osaka_createobject();
    }

    return n;

}

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

node_str *osaka_findtailnode(node_str *root)  {

    assert(root!=NULL);

    while (NEXT(root)!=NULL) {
        root=NEXT(root);
    }

    return root;

}

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

node_str *osaka_findheadnode(node_str *n) {

    assert(n!=NULL);

    while(LAST(n)!=NULL) {
        n = LAST(n);
    }

    return n;

}

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

node_str *osaka_addnodetotail(node_str *r,node_str *n)  {

    if (n==NULL){
        return r;
    }
    node_str *tail;
    assert(r!=NULL);

    tail=osaka_findtailnode(r);

    NEXT(tail)=n;
    LAST(n)=tail;
    NEXT(n)=NULL; // makes it only a node addition

    return r;

}

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

node_str *osaka_addnodetohead(node_str *r,node_str *n)  {

    assert(n!=NULL);
    assert(r!=NULL);

    LAST(r)=n;
    NEXT(n)=r;
    LAST(n)=NULL; // makes it only a node addition

    return n;

}

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
 * root = osaka_createnode(root,TAIL);
 *
 * OR
 *
 * root = osaka_createnode(root,HEAD);
 *
 * SIDE-EFFECT
 *
 * update the root list.
 *
 */

node_str *osaka_createnode(node_str *r,append_typ app_ty,osaka_object_typ ot) {

    node_str *n;

    n = __osaka_createnode(ot);

    if (osaka_whatisnode(r)!=EMPTY) {
        switch (app_ty) {
            case HEAD: return osaka_addnodetohead(r,n); break;
            case TAIL: return osaka_addnodetotail(r,n); break;
        }
    }

    return n;

}

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

void osaka_printnode(node_str *n) {

    assert(n!=NULL);
    printf("\n  object-independent items:\n");
    printf("node         : 0x%8.8lX\n",(unsigned long)n);
    printf("uid          : %d\n",UID(n));
    printf("object_type  : %d\n",OBJECT_TYPE(n));
    printf("object ptr   : 0x%8.8lX\n",(unsigned long)OBJECT(n));
    printf("next ptr >   : 0x%8.8lX\n",(unsigned long)NEXT(n));
    printf("last ptr <   : 0x%8.8lX\n",(unsigned long)LAST(n));

    if (OBJECT_TYPE(n)!=NOTSET) {
        if(OBJECT_TYPE(n)>=0 && OBJECT_TYPE(n)<MAXTYPE) {
            printf("\n  object-specific items: \n");
            object_table_function[OBJECT_TYPE(n)].osaka_printobject(OBJECT(n));
            printf("\n");
        }
        else  {
            printf ("error: writing unknown object type\n");
            exit(0);
        }
    }

}

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

void osaka_printnode_concise(node_str *n) {

    assert(n!=NULL);

    if (OBJECT_TYPE(n)!=NOTSET) {
        if(OBJECT_TYPE(n)>=0 && OBJECT_TYPE(n)<MAXTYPE) {
            printf("UID : %d ; ", UID(n));
            object_table_function[OBJECT_TYPE(n)].osaka_printobject(OBJECT(n));
        }
        else  {
            printf ("error: writing unknown object type\n");
            exit(0);
        }
    }

}

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

void osaka_describenode(char* desc, node_str *n) {

    assert(n!=NULL);

    if (OBJECT_TYPE(n)!=NOTSET) {
        if(OBJECT_TYPE(n)>=0 && OBJECT_TYPE(n)<MAXTYPE) {
            object_table_function[OBJECT_TYPE(n)].osaka_describeobject(desc, OBJECT(n));
        }
        else  {
            printf ("error: writing unknown object type\n");
            exit(0);
        }
    }

}

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

void osaka_printnodearray(node_str *n) {

    while (n != NULL) {
        osaka_printnode(n);
        n = NEXT(n);
    }

    return;

}

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

void osaka_prefix_mapto(node_str *n,void (*fun)(node_str *n)) {

    if (n==NULL) {
        return;
    }

    fun(n);
    osaka_prefix_mapto(NEXT(n),fun);

}

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
 

bool recurse_applytonode(node_str *root,bool (*fun)(node_str *n)) {
  
    if (root==NULL) {
        return true;
    }

    global_nth++;
  
    if (!fun(root)) {
        return false;
    }
    
    return recurse_applytonode(NEXT(root),fun);

}

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

void osaka_postfix_mapto(node_str *n,void (*fun)(node_str *n))  {
  
    if (n==NULL) {
        return;
    }

    osaka_postfix_mapto(NEXT(n),fun);

    fun(n);

}

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

uint32_t osaka_listlength(node_str *r)  {

    uint32_t i = 0;

    while (r!=NULL) {
        r = NEXT(r);
        i++;
    }

    return i;

}


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

void osaka_freenode(node_str *n)  {

    assert(n!=NULL);

    object_table_function[OBJECT_TYPE(n)].osaka_deleteobject(OBJECT(n));

    free(n);

}

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


void osaka_randomizenode(node_str *n) {


    if (n == NULL)  {
        printf ("error: cannot randomize a NULL node");
        exit(0);
    }

    object_table_function[OBJECT_TYPE(n)].osaka_randomizeobject(OBJECT(n));

}


void osaka_setnode(node_str *n, char* pass) {


    if (n == NULL)  {
        printf ("error: cannot randomize a NULL node");
        exit(0);
    }

    object_table_function[OBJECT_TYPE(n)].osaka_setobject(OBJECT(n), pass);

}

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


uint32_t osaka_fitness(node_str *n) {


    if (n == NULL)  {
        printf ("error: cannot calculate fitness of an indiv starting at a NULL node");
        exit(0);
    }

    //return object_table_function[OBJECT_TYPE(n)].osaka_fitnessobject(n);

}

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

node_str *osaka_nthnode(node_str *r,uint32_t nth) {

    assert(r!=NULL);
    assert(nth!=0);

    while(r!=NULL)  {
        --nth;
        if (nth==0) {
            return r;
        }
        r = NEXT(r);
    }

    return NULL;

}

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

node_str *osaka_deletenode(node_str *n) {

    node_str *t,*l;

    assert(n!=NULL);

    switch(osaka_whatisnode(n)) {
        case EMPTY:
            return NULL;
            break;
        case ISOLATE:
            //if(debug) printf ("--osaka: deleting ISOLATE node \n");
            osaka_freenode(n);
            return NULL;
            break;
        case HEADNODE:
            //if(debug) printf ("--osaka: deleting HEADNODE\n");
            t = NEXT(n);
            LAST(t) = NULL;
            osaka_freenode(n);
            return t;
            break;
        case TAILNODE:
            //if(debug) printf ("--osaka: deleting TAILNODE \n");
            t = LAST(n);
            NEXT(t) = NULL;
            osaka_freenode(n);
            return osaka_findheadnode(t);
            break;
        case INTERMEDIATE:
            //if(debug) printf ("--osaka: deleting INTERMEDIATE node \n");
            l = LAST(n);
            t = NEXT(n);
            NEXT(l) = t;
            LAST(t) = l;
            osaka_freenode(n);
            return osaka_findheadnode(l);
            break;
    }

    assert(1==0);
    return NULL;

}


/*
 * NAME
 *
 *  osaka_serialize
 *
 * DESCRIPTION
 *
 *  given a node_str, serialize it into a file
 *
 * PARAMETERS
 *
 *  node_str *r
 *  char *filepath
 *
 * RETURN
 *
 *  uint32_t
 *
 * EXAMPLE
 *
 *  size = osaka_serialize(node, file);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

uint32_t osaka_serialize(node_str *r,char *filepath)  {

    uint32_t x=0;
    FILE *handle;

    //assert(r!=NULL);

    handle=fopen(filepath,"wb");

    if(handle==NULL)  {
        printf("error: couldn't open \'%s\' at file:%s line:%d function:%s\n",filepath,__FILE__,__LINE__,__FUNCTION__);
        exit(0);
    }

    while(r!=NULL)  {
        fwrite(r,sizeof(node_str),1,handle);
        if(OBJECT_TYPE(r)!=NOTSET)  {
            if(OBJECT_TYPE(r)>=0 && OBJECT_TYPE(r)<MAXTYPE) {
                object_table_function[OBJECT_TYPE(r)].osaka_writeobject(handle,OBJECT(r));
            }
            else  {
                printf ("error: writing unknown object type\n");
                exit(0);
            }
        }
      
        x++;
        r=NEXT(r);
    
    }

    fclose(handle);
    return x;

}

/*
 * NAME
 *
 *  osaka_deserialize
 *
 * DESCRIPTION
 *
 *  given a file, serialize it into a node_str and return it
 *
 * PARAMETERS
 *
 *  char *filepath
 *
 * RETURN
 *
 *  node_str
 *
 * EXAMPLE
 *
 *  node = osaka_deserialize(file)
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

node_str *osaka_deserialize(char *filepath) {

    node_str *root=NULL,*tmp;
    FILE *handle;

    assert(filepath!=NULL);

    root=osaka_createnode(root,TAIL,NOTSET); // this will be discarded

    handle=fopen(filepath,"rb");

    if(handle==NULL)  {
        printf("error: couldn't open \'%s\' at file:%s line:%d function:%s\n",filepath,__FILE__,__LINE__,__FUNCTION__);
        exit(0);
    }

    while(!feof(handle))  {
        tmp = __osaka_createnode(NOTSET);
        fread(tmp,sizeof(node_str),1,handle);

        if(OBJECT_TYPE(tmp)!=NOTSET)  {
            if(OBJECT_TYPE(tmp)>=0 && OBJECT_TYPE(tmp)<MAXTYPE) {
               OBJECT(tmp)=object_table_function[OBJECT_TYPE(tmp)].osaka_readobject(handle);
            }
            else  {
                printf ("error: reading unknown object type\n");
                exit(0);
            }
        }
        
        root=osaka_addnodetotail(root,tmp);
    }

    //printf ("debug: pre list length %d\n",osaka_listlength(root));

    root=osaka_deletenode(root);
    root=osaka_deletenode(osaka_findtailnode(root));

    //printf ("debug: post list length %d\n",osaka_listlength(root));

    fclose(handle);
    return root;

}

/*
 * NAME
 *
 *  osaka_compare
 *
 * DESCRIPTION
 *
 *  given two node_str objects, compare them
 *
 * PARAMETERS
 *
 *  node_str *n0
 *  node_str *n1
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 *  are_equal = osaka_compare(node0, node1);
 *
 * SIDE-EFFECT
 *
 *  none...
 *
 */

bool osaka_compare(node_str *n0, node_str *n1)  {
    while(n0!=NULL && n1!=NULL) {
        if(OBJECT_TYPE(n0)!=OBJECT_TYPE(n1))  { 
            return false;
        }
        if (UID(n0)!=UID(n1)) {
            return false;
        }
        if (OBJECT_TYPE(n0) == 3 || OBJECT_TYPE(n0) == 5) {
            if (!object_table_function[OBJECT_TYPE(n0)].osaka_compareobject(OBJECT(n0), OBJECT(n1))) {
                //printf("llvm pass not equal: %s(%d) != %s(%d)\n", PASS(OBJECT(n0)), PASS_INDEX(OBJECT(n0)), PASS(OBJECT(n1)), PASS_INDEX(OBJECT(n1)));
                return false;
            }
        }

        n0=NEXT(n0);
        n1=NEXT(n1);
    }

    return (n0==n1);

}

/*
 * NAME
 *
 *  osaka_consistencyofnode  
 *
 * DESCRIPTION
 *
 * 
 *
 * PARAMETERS
 *
 *  node_str *n
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

bool osaka_consistencyofnode(node_str *n) {

    switch(osaka_whatisnode(n)) {
        case EMPTY: 
            return true; 
            break;
        case ISOLATE: 
            return true; 
            break;
        case HEADNODE:
            if (LAST(n)==NULL && NEXT(n)!=NULL && LAST(NEXT(n))==n) {
                return true;
            }
            return false;
            break;
        case TAILNODE:  
            if (NEXT(n)==NULL && LAST(n)!=NULL && NEXT(LAST(n))==n) {
                return true;
            }
            return false;
            break;
        case INTERMEDIATE:
            if (NEXT(LAST(n))==n && LAST(NEXT(n))==n) {
                return true;
            }
            return false;
            break;
        default:
            printf("error: node type not recognised file:\'%s\' line: %d\n",__FILE__,__LINE__);
            exit(EXIT_SUCCESS);
            break;
    }
    
    return false;

}
    
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
   
bool osaka_consistencycheck(node_str *r)  {

    global_nth=0;
    return recurse_applytonode(r,osaka_consistencyofnode);

}

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

node_str *osaka_copylist(node_str *r) {

    node_str *c=NULL,*cr=NULL,*nc=NULL;
    
    while(r!=NULL)  {
        c=malloc(sizeof(node_str));
        assert(c!=NULL);
        memcpy(c,r,sizeof(node_str));

        if (nc==NULL) {
            nc=cr=c;
            NEXT(c)=NULL;
            LAST(c)=NULL;
        }
        else  {
            NEXT(nc)=c;
            LAST(c)=nc;
            NEXT(c)=NULL;
            nc=c;
        }
          
        if (OBJECT_TYPE(r)!=NOTSET) {
            OBJECT(c)=object_table_function[OBJECT_TYPE(r)].osaka_copyobject(OBJECT(r));
        }

        r=NEXT(r);
    }

    return cr; // return the new root;

}

/*
 * NAME
 *
 *  osaka_innerfree  
 *
 * DESCRIPTION
 *
 *  This function frees a payload object memory. Designed to be used as 
 *  conjection with the osaka_outerfree() function call.
 *
 * PARAMETERS
 *
 *  node_str * - root 
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_postfix_mapto(n,xosaka_outerfree); // free list
 *
 * SIDE-EFFECT
 *
 *  frees a single node.
 *
 */

void xosaka_innerfree(node_str *n)  {

    assert(OBJECT(n)!=NULL); // node cannot be set and have no point to object
    free(OBJECT(n));

}
   
/*
 * NAME
 *
 *  osaka_freelist  
 *
 * DESCRIPTION
 *
 *  This function frees a single node of memory. Designed to be used as 
 *  part of a recursive function call.
 *
 * PARAMETERS
 *
 *  node_str * - root 
 *
 * RETURN
 *
 *  none...
 *
 * EXAMPLE
 *
 *  osaka_postfix_mapto(n,xosaka_outerfree); // free list
 *
 * SIDE-EFFECT
 *
 *  frees a single node.
 *
 */

void xosaka_outerfree(node_str *n)  {
  
    if(n==NULL) return;
    
    if(OBJECT_TYPE(n)!=NOTSET)
    xosaka_innerfree(n);

    free(n);

}

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

node_str *osaka_freelist(node_str *r) {

    osaka_postfix_mapto(r,xosaka_outerfree); // free list

    return NULL;

}

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

void osaka_print_available_object_types() {
    printf("Here are the available object types for the Osaka Structure: \n\n");
    printf("\t[1] SIMPLE\n");
    printf("\t[2] ASSEMBLER\n");
    printf("\t[3] OSAKA_STRING\n");
    printf("\t[4] LLVM_PASS\n");
    printf("\t[5] BINARY_UP_TO_512\n");
    printf("\t[6] GI_LLVM_PASS\n");
}

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

bool osaka_init(bool debug_mode)  {

    debug = debug_mode;

    printf ("-- initalizing OLS ... \n");

    if(!osaka_test_cycler(LOUD))  {
        printf("error: OLS test pass %s !!!\n",osaka_test_cycler(LOUD)?"true":"false");
        exit(0);
    }
    
    printf ("-- OLS successfully initialized\n");
    return true;

}