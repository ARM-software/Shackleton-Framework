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

    if (individual_size == 0) {
        individual_size = rand() % 80 + 10;
    }

    // add as many nodes as is the individual_size to the single individual
    for (uint32_t k = 0; k < individual_size - 1; k++) {
        head = osaka_addnodetotail(head, generate_new_initialized_node(osaka_type));
    }
    return head;
}

node_str** generate_level_passes(const int num_levels, osaka_object_typ osaka_type) {
    if (osaka_type != 3) {
        printf("Function not allowed in the current object type, returning NULL\n");
        return NULL;
    }
    int* default_string_lengths = llvm_default_level_string_lengths(num_levels);
    char*** default_strings = llvm_set_default_level_strings(default_string_lengths, num_levels);
    node_str** level_passes = malloc(sizeof(node_str*) * num_levels);
    for (uint32_t l = 0; l < num_levels; l++) {
        level_passes[l] = generate_individual_from_default(default_strings[l], default_string_lengths[l], osaka_type);
    }
    free(default_string_lengths);
    for (int l = 0; l < num_levels; l++) {
        free(default_strings[l]);
    }
    free(default_strings);
    return level_passes;
}

node_str* generate_individual_from_default(char** passes, int num_passes, osaka_object_typ osaka_type) {
    node_str *head = generate_find_node(passes[0], osaka_type);
    // add as many nodes as is the individual_size to the single individual
    for (int p = 1; p < num_passes; p++) {
        //printf("%s\n", passes[p]);
        head = osaka_addnodetotail(head, generate_find_node(passes[p], osaka_type));
    }
    return head;
    // for each pass, find the node using valid pass, if pass exists in valid pass, add to individual
}

// same level as `node_str* generate_new_initialized_node(osaka_object_typ osaka_type)`
node_str* generate_find_node(char* pass, osaka_object_typ osaka_type) {
    node_str* new_node = osaka_createnode(NULL, HEAD, osaka_type);
    osaka_setnode(new_node, pass);
    //llvm_pass_set_object_from_pass(object_llvm_pass_str* o, char* pass)
    return new_node;
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

void generate_new_generation(node_str** gen, uint32_t population_size, uint32_t individual_size, osaka_object_typ osaka_type, bool gi, const char** levels, const int num_levels) {
    // each index in the array is a pointer to the head of an osaka structure
    int num_gi = gi ? population_size/2 : 0;
    node_str** level_passes = generate_level_passes(num_levels, osaka_type);
    for (uint32_t g = 0; g < num_gi; g++) {
        uint32_t rand_level_ind = (uint32_t) (num_levels * (rand() / (RAND_MAX + 1.0)));
        char level[10];
        strcpy(level, levels[rand_level_ind]);
        node_str* level_pass = osaka_copylist(level_passes[rand_level_ind]);
        /*
        uint32_t temp_mutation1 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
        if (temp_mutation1 <= mut_perc) {
            uint32_t indiv_size_1 = osaka_listlength(level_pass);
            uint32_t random = (uint32_t) (indiv_size_1 * (rand() / (RAND_MAX + 1.0))) + 1;
            mutation_single_unit_all_params(level_pass, random, vis);
        }*/
        // randomly select a default optimization level and mutate it to add to the generation
        gen[g] = level_pass;
    }
    for (uint32_t g = num_gi; g < population_size; g++) {
        node_str* new_seq = generate_new_individual(individual_size, osaka_type);
        gen[g] = new_seq;
        //gen_id[g] = (*max_id_ptr)++;
    }

    generate_free_generation(level_passes, num_levels);
    free(level_passes);
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
 *   generate_copy_gen_id
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
 * generate_copy_gen_id(original, copy, size);
 *
 * SIDE-EFFECT
 *
 *  creates new list of osaka structures that must be freed later
 *
 */

void generate_copy_gen_id(int* orig, int* copy, uint32_t generation_size) {

    for (int i = 0; i < generation_size; i++) {
        copy[i] = orig[i];
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
        if (indiv != NULL) {
            osaka_deletenode(osaka_nthnode(indiv, i));
        }
        else {
            printf("inside generate_free_individual, indiv %d== NULL\n", i);
        }

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
        //printf("Freed individual #%d of %d in the generation\n", g, gen_size);
    } 

}