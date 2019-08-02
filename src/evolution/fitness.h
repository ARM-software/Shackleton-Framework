/*
 ============================================================================
 Name        : fitness.h
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
    
 Description : Main and helper functions for determining the fitness
               of an individual and using that fitness value within
               the evolution process
 ============================================================================
 */

#ifndef EVOLUTION_FITNESS_H_
#define EVOLUTION_FITNESS_H_

/*
 * IMPORT
 */

#include "../osaka/osaka.h"
#include "../support/llvm.h"
#include <stdbool.h>
#include "sys/time.h"

/*
 * STATIC
 */

uint32_t (*fpfitness_simple)(node_str *n, bool vis);
uint32_t (*fpfitness_assembler)(node_str *n, bool vis);
uint32_t (*fpfitness_osaka_string)(node_str *n, bool vis);
uint32_t (*fpfitness_llvm_pass)(node_str *n, char* file, bool vis);
uint32_t (*fpfitness_binary_up_to_512)(node_str *n, bool vis);

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   fitness_simple
 *
 * DESCRIPTION
 *
 *  Calculates the fitness value specifically for a simple
 *  individual, currently is only a default
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t simple_fit = fitness_simple(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_simple(node_str* indiv, bool vis);

/*
 * NAME
 *
 *   fitness_assembler
 *
 * DESCRIPTION
 *
 *  Calculates the fitness value specifically for an assembler
 *  individual, currently is only a default
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t assembler_fit = fitness_assembler(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_assembler(node_str* indiv, bool vis);

/*
 * NAME
 *
 *   fitness_osaka_string
 *
 * DESCRIPTION
 *
 *  Calculates the fitness value specifically for an osaka_string
 *  individual, currently is only a default
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t osaka_string_fit = fitness_osaka_string(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_osaka_string(node_str* indiv, bool vis);

/*
 * NAME
 *
 *   fitness_llvm_pass
 *
 * DESCRIPTION
 *
 *  Calculates the fitness value specifically for an llvm pass
 *  individual, based on the optimization of the code outputted
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t llvm_pass_fit = fitness_llvm_pass(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_llvm_pass(node_str* indiv, char* file, bool vis);

/*
 * NAME
 *
 *   fitness_binary_up_to_512
 *
 * DESCRIPTION
 *
 * Calculates the fitness value specifically for an binary_up_to_512
 * inidividual, currently is only a default. AUTO-GENERATED
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t binary_up_to_512_fit = fitness_binary_up_to_512(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_binary_up_to_512(node_str* indiv, bool vis);

/*
 * NAME
 *
 *   fitness_top
 *
 * DESCRIPTION
 *
 *  Applies the correct fitness function based on the
 *  specific object type of the individual
 *
 * PARAMETERS
 *
 *  node_str* indiv - the individual that is to be evaluated
 *  bool vis - whether or not visualization is enabled
 *
 * RETURN
 *
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t fitness = fitness_top(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_top(node_str* indiv, bool vis, char* test_file);

/*
 * NAME
 *
 *   fitness_setup
 *
 * DESCRIPTION
 *
 *  initializes all typdefs for function pointers to their
 *  respective methods in fitness.h
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
 * fitness_setup();
 *
 * SIDE-EFFECT
 *
 * alters the typedefs
 *
 */

void fitness_setup();

#endif /* EVOLUTION_FITNESS_H_ */