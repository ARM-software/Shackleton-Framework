/*
 ============================================================================
 Name        : generation.c
 Author      : Hannah M. Peeler
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
    
 Description : All functions needed for creating generations, individuals,
               and objects for an evolutionary run. Designed to be used
               as the initialization step and then not touched once
               the individuals start evolving and mutating
 ============================================================================
 */

/*
 * IMPORT
 */

#include "generation.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   generate_new_initialized_node
 *
 * DESCRIPTION
 *
 *  Generates a new sequence of units in the form of an osaka structure
 *
 * PARAMETERS
 *
 *  osaka_object_typ osaka_type -- tells which type of osaka object we're creating
 *
 * RETURN
 *
 *  node_str*
 *
 * EXAMPLE
 *
 * node_str* new_osaka = generate_new_initialized_node(ASSEMBLER);
 *
 * SIDE-EFFECT
 *
 *  creates a new osaka structure
 *
 */

node_str* generate_new_initialized_node(osaka_object_typ osaka_type) {

    node_str* new_node = osaka_createnode(NULL, HEAD, osaka_type);
    
    // initializes all parameters in the single node, specific to object type
    osaka_randomizenode(new_node);

    return new_node;

}

/*
 * NAME
 *
 *   generate_new_inidividual
 *
 * DESCRIPTION
 *
 *  Given a size parameter, creates an initial, fully
 *  randomly generated individual with that many nodes
 *
 * PARAMETERS
 *
 *  uint32_t individual_size -- number of nodes in individual
 *  osaka_object_type osaka_type -- osaka structure type to be used
 *
 * RETURN
 *
 *  node_str* -- pointer to head of an osaka structure
 *
 * EXAMPLE
 *
 * node_str* new_osaka_structure = generate_new_individual(size, ASSEMBLER);
 *
 * SIDE-EFFECT
 *
 *  creates individual_size number of osaka nodes
 *
 */

node_str* generate_new_individual(uint32_t individual_size, osaka_object_typ osaka_type) {
    
    node_str *head = generate_new_initialized_node(osaka_type);

    // add as many nodes as is the individual_size to the single individual
    for (uint32_t k = 0; k < individual_size - 1; k++) {
        head = osaka_addnodetotail(head, generate_new_initialized_node(osaka_type));
    }

    return head;

}

/*
 * NAME
 *
 *   generate_new_generation
 *
 * DESCRIPTION
 *
 *  Given a size parameter, creates an initial, fully
 *  randomly generated generation with that many individuals
 *
 * PARAMETERS
 *
 *  node_str** gen -- pointer to generation of osaka_structures
 *  uint32_t generation_size -- number of individuals in generation
 *  uint32_t individual_size -- number of nodes in individual
 *  osaka_object_type osaka_type -- osaka structure type to be used
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * node_str** new_osaka_generation = generate_new_generation(size, ASSEMBLER);
 *
 * SIDE-EFFECT
 *
 *  creates generation_size number of osaka structures
 *
 */

void generate_new_generation(node_str** gen, uint32_t generation_size, uint32_t individual_size, osaka_object_typ osaka_type) {

    // each index in the array is a pointer to the head of an osaka structure
    for (uint32_t g = 0; g < generation_size; g++) {

        gen[g] = generate_new_individual(individual_size, osaka_type);

    }

}

/*
 * NAME
 *
 *   generate_copy_generation
 *
 * DESCRIPTION
 *
 *  Given an existing generation and some details about it,
 *  copies all of its contents over, with entirely new created nodes
 *  to a new generation object
 *
 * PARAMETERS
 *
 *  node_str** orig -- pointer to generation of osaka_structures
 *  uint32_t generation_size -- number of individuals in generation
 *  node_str** copy -- pointer to head of empty generation to hold copy
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * generate_copy_generation(original, copy, size);
 *
 * SIDE-EFFECT
 *
 *  creates new list of osaka structures that must be freed later
 *
 */

void generate_copy_generation(node_str** orig, node_str** copy, uint32_t generation_size) {

    for (int i = 0; i < generation_size; i++) {

        copy[i] = osaka_copylist(orig[i]);

    }

}

/*
 * NAME
 *
 *   generate_free_individual
 *
 * DESCRIPTION
 *
 *  Frees an individual, including all its internal nodes
 *
 * PARAMETERS
 *
 *  node_str* indiv
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * generate_free_individual(spent_gen, 5);
 *
 * SIDE-EFFECT
 *
 *  completely frees an individual
 *
 */

void generate_free_individual(node_str* indiv) {

    // we must free every single node in this individual
    uint32_t list_length = osaka_listlength(indiv);

    for (uint32_t i = list_length; i > 0; i--) {

        osaka_deletenode(osaka_nthnode(indiv, i));

    }

}

/*
 * NAME
 *
 *   generate_free_individual_inside_array
 *
 * DESCRIPTION
 *
 *  Frees an individual, including all its internal nodes
 *
 * PARAMETERS
 *
 *  node_str** array
 *  uint32_t ind
 *  node_str* indiv
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * generate_free_individual_inside_array(gen, 20, 5, indiv);
 *
 * SIDE-EFFECT
 *
 *  completely frees an individual and repairs the array it was in
 *
 */

void generate_free_individual_inside_array(node_str** array, uint32_t gen_size, uint32_t ind, node_str* indiv) {

    // we must free every single node in this individual
    uint32_t list_length = osaka_listlength(indiv);

    for (uint32_t i = list_length; i > 0; i--) {

        osaka_deletenode(osaka_nthnode(indiv, i));

    }

    for (int k = ind; k < gen_size - 1; k++) {

        array[k] = array[k + 1];

    }

}

/*
 * NAME
 *
 *   generate_free_generation
 *
 * DESCRIPTION
 *
 *  Frees a generation, including all its internal individuals/nodes
 *
 * PARAMETERS
 *
 *  node_str** generation
 *  uint32_t gen_size
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * generate_free_generation(spent_gen, 5);
 *
 * SIDE-EFFECT
 *
 *  completely frees a generation
 *
 */

void generate_free_generation(node_str** generation, uint32_t gen_size) {

    // we must free every individual in this generation
    for (uint32_t g = 0; g < gen_size; g++) {

        generate_free_individual(generation[g]);
    
    } 

}