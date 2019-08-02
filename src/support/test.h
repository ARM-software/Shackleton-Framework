/*
 ============================================================================
 Name        : test.h
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
    
 Description : Contains tests for specific functionalities
               used in the Shackleton framework
 ============================================================================
 */

#ifndef SUPPORT_TEST_H_
#define SUPPORT_TEST_H_

/*
 * IMPORT ...
 */

#include "sys/time.h"
#include "llvm.h"
#include "../evolution/evolution.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   test_basic_printing
 *
 * DESCRIPTION
 *
 *  Tests different ways of printing a single node
 *
 * PARAMETERS
 *
 *  uint32_t gen_size -- generation size
 *  uint32_t indiv_size -- individual size
 *  osaka_object_typ ot -- object type to be created
 *  bool vis -- whether or not visualizations are enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_making_generation(4, 10, OSAKA_STRING, true)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_basic_printing(uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_llvm_form_opt_command_indiv
 *
 * DESCRIPTION
 *
 *  Tests the function that forms an opt command
 *  for llvm  optimization from an osaka individual
 *
 * PARAMETERS
 *
 *  char* file - the .ll file that the passes will be applied to
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_llvm_form_opt_command_indiv("hello.ll");
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_llvm_form_opt_command_indiv(char* file);

/*
 * NAME
 *
 *   test_llvm_form_exec_code_command
 *
 * DESCRIPTION
 *
 *  Tests the function that forms an exec code command
 *  for llvm  optimization from an osaka individual
 *
 * PARAMETERS
 *
 *  char* file - the .ll file that the passes will be applied to
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_llvm_form_exec_code_command("hello.ll");
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_llvm_form_exec_code_command(char* file);

/*
 * NAME
 *
 *   test_llvm_form_test_command
 *
 * DESCRIPTION
 *
 *  Tests the function that forms a serious of terminal
 *  commands that compiles both a source file and a test file
 *  that tests it into one executable, and runs it.
 *
 * PARAMETERS
 *
 *  char** src_files - an array of .cpp or .c files that have the functionality to be tested
 *  char* test_file - the file that contains the tests to be run
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_llvm_form_test_command();
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_llvm_form_test_command();

/*
 * NAME
 *
 *   test_onepoint_crossover
 *
 * DESCRIPTION
 *
 *  Tests that onepoint crossover with vis works
 *  as expected
 *
 * PARAMETERS
 *
 *  uint32_t indiv_size -- individual size
 *  osaka_object_typ ot -- object type to be created
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_onepoint_crossover(10, OSAKA_STRING, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_onepoint_crossover(uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_making_generation
 *
 * DESCRIPTION
 *
 *  Tests that one can create a generation of a given size, type, and 
 *  individual size and can visualize that
 *
 * PARAMETERS
 *
 *  uint32_t gen_size -- generation size
 *  uint32_t indiv_size -- individual size
 *  osaka_object_typ ot -- object type to be created
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_making_generation(4, 10, OSAKA_STRING, true)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_making_generation(uint32_t gen_size, uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_basic_mutation
 *
 * DESCRIPTION
 *
 *  Tests basic mutation where one node from an osaka indiv
 *  has all of its parameters changed
 *
 * PARAMETERS
 *
 *  uint32_t indiv_size -- individual size
 *  osaka_object_typ ot -- object type to be created
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_basic_mutation(10, OSAKA_STRING, true)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_basic_mutation(uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_crossover_twopoint_diff
 *
 * DESCRIPTION
 *
 *  Tests that one can create a generation of a given size, type, and 
 *  individual size and can visualize that
 *
 * PARAMETERS
 *
 *  uint32_t indiv_size -- individual size
 *  osaka_object_typ ot -- object type to be created
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_crossover_twopoint_diff(10, OSAKA_STRING, false)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_crossover_twopoint_diff(uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_copy_generation
 *
 * DESCRIPTION
 *
 *  Tests that check the copy generation method
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t indiv_size -- size of the individual osaka structures
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_copy_generation(3, 8, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_copy_generation(uint32_t pop_size, uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_selection_tournament
 *
 * DESCRIPTION
 *
 *  Tests that tournament selection works as expected
 *  and return a winner that is valid
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t indiv_size -- size of the individual osaka structures
 *  uint32_t tourn_size -- tournament size
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_selection_tournament(4, 4, 2, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_selection_tournament(uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, osaka_object_typ ot, bool vis, char* file);

/*
 * NAME
 *
 *   test_selection_tournament_multiple
 *
 * DESCRIPTION
 *
 *  Tests that tournament selection works as expected
 *  when it is called in succession 5 times
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t indiv_size -- size of the individual osaka structures
 *  uint32_t tourn_size -- tournament size
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_selection_tournament_multiple(4, 4, 2, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_selection_tournament_multiple(uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, osaka_object_typ ot, bool vis, char* file);

/*
 * NAME
 *
 *   test_generate_free_individual_inside_array
 *
 * DESCRIPTION
 *
 *  Frees an individual, while also repairing an array that it was in
 *
 * PARAMETERS
 *
 *  uint32_t pop_size
 *  uint32_t indiv_size
 *  osaka_object_typ ot
 *  bool vis
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_generate_free_individual_inside_array(gen, 20, 5, indiv, true);
 *
 * SIDE-EFFECT
 *
 *  completely frees an individual and repairs the array it was in
 *
 */

void test_generate_free_individual_inside_array(uint32_t pop_size, uint32_t indiv_size, osaka_object_typ ot, bool vis);

/*
 * NAME
 *
 *   test_evolution_basic_crossover_and_mutation
 *
 * DESCRIPTION
 *
 *  Tests that check the main basic evolution method
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t num_gens -- number of generations to be created/gone through
 *  uint32_t indiv_size -- number of nodes in a single individual
 *  uint32_t tourn_size -- size of tournaments
 *  uint32_t mut_perc -- percentage chance of being mutated during each generation
 *  uint32_t cross_perc -- percentage chance of being a part of a crossover during each generation
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_evolution_basic_crossover_and_mutation(20, 50, 2, 5, 25, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_evolution_basic_crossover_and_mutation(uint32_t pop_size, uint32_t num_gens, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file);

/*
 * NAME
 *
 *   test_evolution_basic_crossover_and_mutation_with_replacement
 *
 * DESCRIPTION
 *
 *  Tests that check the main basic evolution method with replacement
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t num_gens -- number of generations to be created/gone through
 *  uint32_t indiv_size -- number of nodes in a single individual
 *  uint32_t tourn_size -- size of tournaments
 *  uint32_t mut_perc -- percentage chance of being mutated during each generation
 *  uint32_t cross_perc -- percentage chance of being a part of a crossover during each generation
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_evolution_basic_crossover_and_mutation_with_replacement(20, 50, 2, 5, 25, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, bool cache);

/*
 * NAME
 *
 *   test_master
 *
 * DESCRIPTION
 *
 *  Master test method that calls other tests for the run
 *
 * PARAMETERS
 *
 *  uint32_t pop_size -- target size of the populations
 *  uint32_t num_gens -- number of generations to be created/gone through
 *  uint32_t indiv_size -- number of nodes in a single individual
 *  uint32_t tourn_size -- size of tournaments
 *  uint32_t mut_perc -- percentage chance of being mutated during each generation
 *  uint32_t cross_perc -- percentage chance of being a part of a crossover during each generation
 *  osaka_object_typ ot -- osaka object type to be used in the run
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * test_master(20, 50, 2, 5, 25, LLVM_PASS, true);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_master(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, bool cache);

#endif /* SUPPORT_TEST_H_ */