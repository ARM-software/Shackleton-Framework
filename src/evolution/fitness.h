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
double (*fpfitness_llvm_pass)(node_str* indiv, char* file, char** src_files, uint32_t num_src_files, bool vis, bool cache, char* cache_file);
uint32_t (*fpfitness_binary_up_to_512)(node_str *n, bool vis);

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   fitness_pre_cache_simple
 *
 * DESCRIPTION
 *
 *  Creates a file that describes the control values for fitness using LLVM opt
 *
 * PARAMETERS
 *
 *  char* folder - the main run folder that the control will be saved to
 *  char* bool - whether or not caching is being used
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (object_type == SIMPLE) {
 *     fitness_pre_cache_simple(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_simple(char* folder, bool cache);

/*
 * NAME
 *
 *   fitness_cache_simple
 *
 * DESCRIPTION
 *
 *  Creates a file that describes an individual along with their fitness
 *
 * PARAMETERS
 *
 *  double fitness - the fitness of the individual in question
 *  node_str* indiv - the individual that is to be evaluated
 *  char* cache_file - the file that will hold the outputted information
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (cache) {
 *     fitness_cache_simple(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_simple(double fitness, node_str* indiv, char* cache_file);

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
 *   fitness_pre_cache_assembler
 *
 * DESCRIPTION
 *
 *  Creates a file that describes the control values for fitness using LLVM opt
 *
 * PARAMETERS
 *
 *  char* folder - the main run folder that the control will be saved to
 *  char* bool - whether or not caching is being used
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (object_type == ASSEMBLER) {
 *     fitness_pre_cache_assembler(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_assembler(char* folder, bool cache);

/*
 * NAME
 *
 *   fitness_cache_assembler
 *
 * DESCRIPTION
 *
 *  Creates a file that describes an individual along with their fitness
 *
 * PARAMETERS
 *
 *  double fitness - the fitness of the individual in question
 *  node_str* indiv - the individual that is to be evaluated
 *  char* cache_file - the file that will hold the outputted information
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (cache) {
 *     fitness_cache_assembler(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_assembler(double fitness, node_str* indiv, char* cache_file);

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
 *   fitness_pre_cache_osaka_string
 *
 * DESCRIPTION
 *
 *  Creates a file that describes the control values for fitness using LLVM opt
 *
 * PARAMETERS
 *
 *  char* folder - the main run folder that the control will be saved to
 *  char* bool - whether or not caching is being used
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (object_type == OSAKA_STRING) {
 *     fitness_pre_cache_osaka_string(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_osaka_string(char* folder, bool cache);

/*
 * NAME
 *
 *   fitness_cache_osaka_string
 *
 * DESCRIPTION
 *
 *  Creates a file that describes an individual along with their fitness
 *
 * PARAMETERS
 *
 *  double fitness - the fitness of the individual in question
 *  node_str* indiv - the individual that is to be evaluated
 *  char* cache_file - the file that will hold the outputted information
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (cache) {
 *     fitness_cache_osaka_string(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_osaka_string(double fitness, node_str* indiv, char* cache_file);

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
 *   fitness_pre_cache_llvm_pass
 *
 * DESCRIPTION
 *
 *  Creates a file that describes the control values for fitness using LLVM opt
 *
 * PARAMETERS
 *
 *  char* folder - the main run folder that the control will be saved to
 *  char* test_file - the file that will be measured for its control values
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (object_type == LLVM_PASS) {
 *     fitness_pre_cache_llvm_pass(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_llvm_pass(char* folder, char* test_file, char** src_files, uint32_t num_src_files, bool cache);

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
 *  double - the fitness value for indiv
 *
 * EXAMPLE
 *
 *  double llvm_pass_fit = fitness_llvm_pass(node, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

double fitness_llvm_pass(node_str* indiv, char* file, char** src_files, uint32_t num_src_files, bool vis, bool cache, char* cache_file);

/*
 * NAME
 *
 *   fitness_pre_cache_binary_up_to_512
 *
 * DESCRIPTION
 *
 *  Creates a file that describes the control values for fitness using LLVM opt
 *
 * PARAMETERS
 *
 *  char* folder - the main run folder that the control will be saved to
 *  char* bool - whether or not caching is being used
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (object_type == BINARY_UP_TO_512) {
 *     fitness_pre_cache_llvm_pass(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_binary_up_to_512(char* folder, bool cache);

/*
 * NAME
 *
 *   fitness_cache_binary_up_to_512
 *
 * DESCRIPTION
 *
 *  Creates a file that describes an individual along with their fitness
 *
 * PARAMETERS
 *
 *  double fitness - the fitness of the individual in question
 *  node_str* indiv - the individual that is to be evaluated
 *  char* cache_file - the file that will hold the outputted information
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * if (cache) {
 *     fitness_cache_binary_up_to_512(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_binary_up_to_512(double fitness, node_str* indiv, char* cache_file);

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
 *  fitness_pre_cache
 *
 * DESCRIPTION
 *
 *  Does an initial setup cache, is dependent on the object type
 *
 * PARAMETERS
 *
 *  char* folder - the folder where the pre caching files will be housed
 *  char* file - for some object types, will be a file used for the caching
 *  osaka_object_typ type - the object type for this evolutionary run
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  if (cache) {
 *      fitness_pre_cache(main_folder, test_file, ot);    
 *  }
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void fitness_pre_cache(char* folder, char* test_file, char** src_files, uint32_t num_src_files, osaka_object_typ type, bool cache);

/*
 * NAME
 *
 *  fitness_cache
 *
 * DESCRIPTION
 *
 *  Caches 
 *
 * PARAMETERS
 *
 *  double fitness_value - the fitness value of the individual to be cached
 *  node_str* indiv - pointer to the individual to be cached
 *  char* cache_file - file where the cached information will reside
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  fitness_cache(value, individual, "individual1.txt");
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void fitness_cache(double fitness_value, node_str* indiv, char* cache_file);

/*
 * NAME
 *
 *  fitness_top
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
 *  double - the fitness value for indiv
 *
 * EXAMPLE
 *
 *  double fitness = fitness_top(node, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

double fitness_top(node_str* indiv, bool vis, char* test_file, char** src_files, uint32_t num_src_files, bool cache, char* cache_file);

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