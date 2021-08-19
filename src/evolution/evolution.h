/*
 ============================================================================
 Name        : evolution.h
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
    
 Description : Core file for pulling all evolutionary
               capabilities together into 1 file

               Will include initialization and manipulation
               of the population based on what parameters are
               provided to main
 ============================================================================
 */

#ifndef EVOLUTION_EVOLUTION_H_
#define EVOLUTION_EVOLUTION_H_

/*
 * IMPORT
 */

#include <unistd.h> //Added 6/8/2021, for checking whether file exists
#include "mutation.h"
#include "crossover.h"
#include "generation.h"
#include "selection.h"
#include "indivdata.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   evolution_cache_generation
 *
 * DESCRIPTION
 *
 *  For a given general, caches information on every individual
 *  and its fitness in a folder within run/
 *
 * PARAMETERS
 *
 *  char* main_folder - the folder in which the new file will be housed
 *  uint32_t gen - the generation number within this run
 *  uint32_t pop_size - size of a single generation
 *  node_str** curr_gen - the current generation that is being cached
 *  bool vis - whether or not visualization is enabled
 *  char* file - the test file
 *  double* fitness_values - fitness values for every individual in the current generation
 *  osaka_object_typ ot - the object type that is being used for this run
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  evolution_cache_generation(main_folder_str, 5);
 *
 * SIDE-EFFECT
 *
 *  Affects the value of main_folder variable
 *
 */

void evolution_cache_generation_old(bool cache, char* main_folder, uint32_t gen, uint32_t pop_size, node_str** curr_gen, bool vis, char* file, char** src_files, uint32_t num_src_files, double* fitness_values, osaka_object_typ ot, double* track_fitness, int offset);

/*
 * NAME
 *
 *   evolution_create_new_run_folder
 *
 * DESCRIPTION
 *
 *  For an evolutionary run, creates a run folder
 *  that will hold all cached data if caching is enabled
 *
 * PARAMETERS
 *
 *  char* main_folder - the variable the path of the new folder will be loaded into
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  evolution_create_new_run_folder(main_folder_str);
 *
 * SIDE-EFFECT
 *
 *  Affects the value of main_folder variable
 *
 */

//void evolution_create_new_run_folder(char* main_folder, const char *cache_id); // Added 6/21/2021
//void evolution_create_new_run_folder(char* main_folder); 

/*
 * NAME
 *
 *   evolution_create_new_gen_folder
 *
 * DESCRIPTION
 *
 *  For an evolutionary run, creates a new generation folder
 *  that will hold all cached data if caching is enabled
 *
 * PARAMETERS
 *
 *  char* main_folder - has the base folder path that the new folder will be added to
 *  uint32_t gen - the generation number for this directory
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  evolution_create_new_gen_folder(3);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

//void evolution_create_new_gen_folder(char* main_folder, uint32_t gen);

/*
 * NAME
 *
 *   evolution_create_new_folder
 *
 * DESCRIPTION
 *
 *  Creates a new folder
 *  that will hold all cached data if caching is enabled
 *
 * PARAMETERS
 *
 *  char* directory_name - has the name of the folder path
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  evolution_create_new_folder(directory_name);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

//void evolution_create_new_folder(char* new_directory_name);


/*
 * NAME
 *
 *   evolution_basic_crossover_and_mutation
 *
 * DESCRIPTION
 *
 *  Completes an evolutionary process in which num_gens
 *  generations are created, each pop_size number of individuals 
 *  within them. During each generation, each individual will have
 *  a mut_perc/100 chance of being mutated and have a cross_perc/100 
 *  chance of being crossed with another individual
 *
 * PARAMETERS
 *
 *  uint32_t num_gens -- number of generations to be created/gone through
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t indiv_size -- number of nodes in a single individual
 *  uint32_t tourn_size -- size of tournaments
 *  uint32_t mut_perc -- percentage chance of being mutated during each generation
 *  uint32_t cross_perc -- percentage chance of being a part of a crossover during each generation
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  node_str* - best individual in final generation
 *
 * EXAMPLE
 *
 * node_str* best = evolution_basic_crossover_and_mutation(20, 50, 50, 2, 5, 25, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

node_str* evolution_basic_crossover_and_mutation(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file);


void select_elites(int pop_size, int num_elites, double* fitness_values, int* current_gen_id, int* elite_indx, int* elite_id);
void evolution_cache_gen(bool cache, char* main_folder, \
            node_str** current_generation, double* fitness_values, int* current_gen_id, \
            double* track_fitness, \
            int pop_size, int num_gens, int g, int offset, osaka_object_typ ot);
int find_best(double* fitness_values, int pop_size, osaka_object_typ ot);
void evolution_log_to_summary(bool cache, char* main_folder, \
            double* fitness_values, int* current_gen_id, \
            double winner_fitness, \
            int pop_size, int num_gens, int g, int offset);
void print_elites(int num_elites, int* elite_indx, double* fitness_values, int* elite_id, node_str** current_gen);
void print_random(int num_new_random, int num_elites, int* current_gen_id);
void create_elites(int num_elites, int* elite_ids, node_str** copy_gen, node_str** current_generation, int* copy_gen_id, int* current_gen_id, double* fitness_values);
void create_randoms(int num_elites, int num_new_random, int* max_id, node_str** current_generation, int* current_gen_id, int indiv_size, osaka_object_typ ot, DataNode*** all_indiv_ptr, int* hash_cap);
void select_parents(uint32_t* c_ind1, uint32_t* c_ind2, node_str** copy_gen, double* fitness_values, int copy_size, int tourn_size, bool vis);
void generate_offspring(int parent1_ind, int parent2_ind, node_str** copy_gen, int* copy_gen_id, int num_offspring, node_str** offsprings, bool* ofs_change, int* ofs_id, uint32_t cross_perc, uint32_t mut_perc, bool vis, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr);
void genetic_operators(node_str* contestant1, node_str* contestant2, bool* c1_change, bool* c2_change, uint32_t cross_perc, uint32_t mut_perc, bool vis);
void select_offspring(node_str** best, int* best_id, node_str** offsprings, bool* ofs_change, int* ofs_id, int num_offspring, int parent1_ind, int parent2_ind, double* fitness_values, bool vis, char* test_file, char** src_files, uint32_t num_src_files, bool cache, char* cache_file, const char *cache_id, int g, DataNode*** all_indiv_ptr, uint32_t num_runs, bool fitness_with_var);
void update_generation(node_str* contestant1, node_str* contestant2, int c1_id, int c2_id, node_str** current_generation, int* current_gen_id, int pop_size, int num_elites, int num_new_random, int p);
void create_mutants(node_str** copy_gen, node_str** current_generation, double* fitness_values,\
                        int* copy_gen_id, int* current_gen_id, int* max_id_ptr, \
                        uint32_t tourn_size, uint32_t pop_size, uint32_t cross_perc, uint32_t mut_perc, \
                        uint32_t num_elites, uint32_t num_new_random, uint32_t copy_size, \
                        uint32_t num_runs, uint32_t num_offspring, \
                        char* file, char** src_files, uint32_t num_src_files, \
                        bool vis, int g, \
                        bool cache, char* cache_file, const char* cache_id, \
                        DataNode*** all_indiv_ptr, int* hash_cap_ptr, bool fitness_with_var);
void log_all_indiv_info(bool cache, DataNode** all_indiv, char* main_folder, int num_runs, int max_id);
void log_redo_basic(char* folder, char* file, bool cache, const char *cache_id, double best_fitness, uint32_t num_runs, bool fitness_with_var, int g, const char** levels, int num_levels);
bool check_termination(double best_fitness, double* lowest_ptr, int* stale_counter_ptr, const int stale_limit);
int evolution_clean_up(int num_elites, node_str** current_generation, uint32_t pop_size, \
                                bool vis, char* main_folder, char* file, const char* cache_id, bool cache, \
                                DataNode** all_indiv, int num_runs, int max_id, int g, \
                                osaka_object_typ ot, double* fitness_values, int* current_gen_id);
/*
 * NAME
 *
 *   evolution_basic_crossover_and_mutation_with_replacement
 *
 * DESCRIPTION
 *
 *  Completes an evolutionary process in which num_gens
 *  generations are created, each pop_size number of individuals 
 *  within them. During each generation, each individual will have
 *  a mut_perc/100 chance of being mutated and have a cross_perc/100 
 *  chance of being crossed with another individual. It is the same as 
 *  the other basic crossover and mutation method, but individuals
 *  can be chosen multiple times
 *
 * PARAMETERS
 *
 *  uint32_t num_gens -- number of generations to be created/gone through
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t indiv_size -- number of nodes in a single individual
 *  uint32_t tourn_size -- size of tournaments
 *  uint32_t mut_perc -- percentage chance of being mutated during each generation
 *  uint32_t cross_perc -- percentage chance of being a part of a crossover during each generation
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  node_str* - best individual in final generation
 *
 * EXAMPLE
 *
 * node_str* best = evolution_basic_crossover_and_mutation_with_replacement(20, 50, 50, 2, 5, 25, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

int evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, uint32_t elite_perc, osaka_object_typ ot, bool vis, char* file, char** src_files, uint32_t num_src_files, bool cache, double* track_fitness, const char *cache_id, const char** levels, int num_levels); //Added 6/9/2021
//node_str* evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, char** src_files, uint32_t num_src_files, bool cache);

#endif /* EVOLUTION_EVOLUTION_H_ */
