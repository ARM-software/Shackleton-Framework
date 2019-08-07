/*
 ============================================================================
 Name        : selection.h
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

#ifndef EVOLUTION_SELECTION_H_
#define EVOLUTION_SELECTION_H_

/*
 * IMPORT
 */

#include "../osaka/osaka.h"
#include "../support/visualization.h"
#include "fitness.h"

/*
 * ROUTINES
 */

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

bool selection_get_min_max(osaka_object_typ object_type);
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
 *  double fitness1 - the fitness that is expected to be the "best"
 *  double fitness2 - the fitness that is being compared with
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

bool selection_compare_fitness(double fitness1, double fitness2, osaka_object_typ object_type);

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
 *  double* fitness_values_all - fitness values for the entire current population
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

uint32_t selection_tournament(node_str** population, double* fitness_values_all, node_str* result, uint32_t pop_size, uint32_t tournament_size, bool vis, char* file);

#endif /* EVOLUTION_SELECTION_H_ */