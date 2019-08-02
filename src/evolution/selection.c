/*
 ============================================================================
 Name        : selection.c
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
    
 Description : Contains method for selecting individuals from a population
               to then be varied into the next population
 ============================================================================
 */

/*
 * IMPORT
 */

#include "selection.h"

/*
 * ROUTINES
 */

 /*
 * NAME
 *
 *   selection_get_min_max
 *
 * DESCRIPTION
 *
 *  Returns true or false depending on if a fitness metric has the quality of
 *  larger is better, or smaller is better. True means that smaller is better (cost),
 *  false means that larger is better (benefit)
 *
 * PARAMETERS
 *
 *  osaka_object_typ object_type - what osaka object type the individuals being compared are
 *
 * RETURN
 *
 *  bool - whether a smaller fitness is better, or a larger fitness is better
 *
 * EXAMPLE
 *
 *  if ((fitness1 < fitness2) && selection_get_min_max(OBJECT_TYPE(o))) {
 *      best_fitness = fitness1;
 *  }
 *  else {
 *      best_fitness = fitness2;   
 *  }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

bool selection_get_min_max(osaka_object_typ object_type) {

    // determines if the fitness value is preferred to be
    // higher or lower.
    bool fitness_max_or_min[5] = {
        false,       // a larger fitness value for SIMPLE is better
        false,       // a larger fitness value for ASSEMBLER is better
        false,       // a larger fitness value for OSAKA_STRING is better
        true,        // a smaller fitness value for LLVM_PASS is better
        false        // a larger fitness value for BINARY_UP_TO_512 is better
    };

    return fitness_max_or_min[object_type];

}

/*
 * NAME
 *
 *   selection_compare_fitness
 *
 * DESCRIPTION
 *
 *  Compares to fitnesses. Returns true if fitness1 is "worse"
 *  than fitness2, which may mean that fitness1 is greater or less
 *  than fitness 2 depending on the type of the objects
 *
 * PARAMETERS
 *
 *  uint32_t fitness1 - the fitness that is expected to be the "best"
 *  uint32_t fitness2 - the fitness that is being compared with
 *  osaka_object_typ object_type - what osaka object type the individuals being compared are
 *
 * RETURN
 *
 *  bool - whether fitness2 is better than fitness1, or not
 *
 * EXAMPLE
 *
 *  if (selection_compare_fitness(fitness1, fitness2, LLVM_PASS)) {
 *      max_fitness = fitness2; // fitness2 was better than fitness1
 *  } 
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

bool selection_compare_fitness(uint32_t fitness1, uint32_t fitness2, osaka_object_typ object_type) {
    
    // if true, means that a larger value is better
    if (selection_get_min_max(object_type)) {
        return fitness2 > fitness1;
    }
    // if false, means that a smaller value is better
    else {
        return fitness2 < fitness1;
    }

}

/*
 * NAME
 *
 *   selection_tournament
 *
 * DESCRIPTION
 *
 *  From the entire population of individuals
 *  choose tournament_size to compete against one
 *  another and returns one winner
 *
 * PARAMETERS
 *
 *  node_str** population - tournament size population
 *  node_str* result - the node that was chosen
 *  uint32_t pop_size - size of the population
 *  uint32_t tournament_size - number of contestants in the tournament
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - index of the winner in the original population
 *
 * EXAMPLE
 *
 * uint32_t winner_index = selection_tournament(population, node, 50, 2);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t selection_tournament(node_str** population, node_str* result, uint32_t pop_size, uint32_t tournament_size, bool vis, char* file) {

    // Tournament selection with replacement, individuals can
    // be chosen more than once for the tournament selection process

    if (vis) {

        printf("Choosing using the basic tournament selection method ---------------------------------\n\n");

    }

    uint32_t fitness_values[tournament_size];
    uint32_t fitness_indices[tournament_size];
    uint32_t max_fitness = 0;
    uint32_t max_fitness_ind = -1;
    bool repeat_index = false;
    uint32_t num_chosen = 0;
    osaka_object_typ type = OBJECT_TYPE(population[0]);

    if (selection_get_min_max(type)) {
        max_fitness = UINT32_MAX;
    }

    // choose indexes of contestants in the tournament first
    while (num_chosen < tournament_size) {
        uint32_t index = (uint32_t) (pop_size * (rand() / (RAND_MAX + 1.0))); 
        for (int curr = 0; curr < num_chosen; curr++) {
            if (fitness_indices[curr] == index) {
                // repeated index, mark as such
                repeat_index = true;
            }
        }
        if (repeat_index) {
            // repeated index, need to pick another one
        }
        else {
            //not chosen yet, can add new index
            fitness_indices[num_chosen] = index;
            num_chosen++;
        }
        repeat_index = false;
    }

    for (uint32_t c = 0; c < tournament_size; c++) {

        fitness_values[c] = fitness_top(population[fitness_indices[c]], vis, file);

        // update which is the current best out of those chosen thus far
        if (selection_compare_fitness(fitness_values[c], max_fitness, type)) {
            max_fitness = fitness_values[c];
            max_fitness_ind = fitness_indices[c];
        }

    }

    if (vis) {

        printf("Individual chosen was number %d in the population -------------------------------------\n\n", max_fitness_ind);   

    }

    result = population[max_fitness_ind];
    return max_fitness_ind;

}