/*
 ============================================================================
 Name        : test.c
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

/*
 * IMPORT ...
 */

#include "test.h"

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
 * test_basic_printing(10, OSAKA_STRING, true)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_basic_printing(uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    // test is completely disabled if visualization are not enabled
    if (vis) {

        // must create an individual to print
        node_str* indiv = generate_new_individual(indiv_size, ot);

        printf("Verbose printing ---------------------------------------------------------------------\n");
        visualization_print_individual_verbose(indiv);

        printf("\nConcise printing with addresses ------------------------------------------------------\n\n");
        visualization_print_individual_concise_addresses(indiv);

        printf("\n\nConcise printing with details: -------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(indiv);

        // newlines only for formatting reasons
        printf("\n\n");

        // always free individual at the end
        generate_free_individual(indiv);

    }

}

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

void test_llvm_form_opt_command_indiv(char* file) {

    char file_name[30];
    char base_name[60];
    char output_base[70];
    char input_file[60];
    char command[10000];
    node_str* indiv;

    char output_file1[60];
    char output_file2[60];
    char output_file3[60];
    char output_file4[60];

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(base_name, "src/files/llvm/");
    strcpy(output_base, "src/files/llvm/junk_output/");

    strcpy(input_file, base_name);
    strcat(input_file, file_name);
    strcat(input_file, ".ll");

    strcpy(output_file1, output_base);
    strcat(output_file1, file_name);
    strcat(output_file1, "1.ll");

    strcpy(output_file2, output_base);
    strcat(output_file2, file_name);
    strcat(output_file2, "2.ll");

    strcpy(output_file3, output_base);
    strcat(output_file3, file_name);
    strcat(output_file3, "3.ll");

    strcpy(output_file4, output_base);
    strcat(output_file4, file_name);
    strcat(output_file4, "4.ll");

    printf("\n\n ---------------------------------- About to form and run 1st command ---------------------------------- \n\n");
    indiv = generate_new_individual(10, LLVM_PASS);
    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file1, command);
    printf("\nThis is the first command: %s\n\n", command);
    llvm_run_command(command);
    generate_free_individual(indiv);
    printf("\n\n --------------------------------------- Done running 1st command -------------------------------------- \n\n");

    printf("\n\n ---------------------------------- About to form and run 2nd command ---------------------------------- \n\n");
    indiv = generate_new_individual(10, LLVM_PASS);
    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file2, command);
    printf("This is the second command: %s\n\n", command);
    llvm_run_command(command);
    generate_free_individual(indiv);
    printf("\n\n --------------------------------------- Done running 2nd command -------------------------------------- \n\n");

    printf("\n\n ---------------------------------- About to form and run 3rd command ---------------------------------- \n\n");
    indiv = generate_new_individual(10, LLVM_PASS);
    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file3, command);
    printf("This is the third command: %s\n\n", command);
    llvm_run_command(command);
    generate_free_individual(indiv);
    printf("\n\n --------------------------------------- Done running 3rd command -------------------------------------- \n\n");

    printf("\n\n ---------------------------------- About to form and run 4th command ---------------------------------- \n\n");
    indiv = generate_new_individual(10, LLVM_PASS);
    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file4, command);
    printf("This is the fourth command: %s\n\n", command);
    llvm_run_command(command);
    generate_free_individual(indiv);
    printf("\n\n --------------------------------------- Done running 4th command -------------------------------------- \n\n");

}

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

void test_llvm_form_exec_code_command(char* file) {

    char command[10000];

    uint32_t result;

    time_t time1, time2;
    clock_t clock1, clock2;
    struct timeval start, end; 

    llvm_form_exec_code_command(file, command);
    printf("\nCommand: %s\n\n", command);

    printf("Running the command now\n\n");

    gettimeofday(&start, NULL);

    result = system(command);

    gettimeofday(&end, NULL);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Done running, the command took %f seconds to run, according to gettimeofday()\n\n", time_taken);
    printf("The number returned by system was %d\n\n", result>>8);

}

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

void test_llvm_form_test_command() {

    char build_command[5000];
    char run_command[500];

    strcpy(build_command, "");
    strcpy(run_command, "");

    uint32_t build_result;
    uint32_t run_result;

    struct timeval start, end; 

    char* src_files[1];
    src_files[0] = "add.cpp";

    llvm_form_test_command(src_files, 1, "test.cpp", build_command, run_command);
    
    printf("\n------ Build Command: %s\n", build_command);
    printf("------ Running the build command now\n");
    build_result = system(build_command);
    printf("------ Build command returned with a result of %d\n\n", build_result>>8);

    printf("------ Run Command: %s\n", run_command);
    printf("------ Running the run command now\n");
    gettimeofday(&start, NULL);
    run_result = system(run_command);
    gettimeofday(&end, NULL);
    printf("------ Run command returned with a result of %d\n\n", run_result>>8);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Done running, the run command took %f seconds to run, according to gettimeofday()\n\n", time_taken);

}

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

void test_onepoint_crossover(uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    node_str* my_generation[2];
    generate_new_generation(my_generation, 2, indiv_size, ot);

    // perform twopoint crossover where the points do not have to be the same across both individuals
    crossover_onepoint_macro(my_generation[0], my_generation[1], vis);

    // always free the generation
    generate_free_generation(my_generation, 2);

}

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

void test_making_generation(uint32_t gen_size, uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    // create generation of variable size of osaka structures
    node_str* my_generation[gen_size];
    generate_new_generation(my_generation, gen_size, indiv_size, ot);

    // print every individual in the generation
    if (vis) {

        printf("Creating a new generation of size %d, with individuals of size %d ---------------------\n", gen_size, indiv_size);

        for (uint32_t n = 0; n < gen_size; n++) {
        
            printf("\nIndividual %d -------------------------------------------------------------------------\n", n+1);
            osaka_printnodearray(my_generation[n]);

        }

        printf("\nGeneration successfully created and printed above-------------------------------------\n\n");

    }

    // always free the generation
    generate_free_generation(my_generation, gen_size);

}

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

void test_basic_mutation(uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    // initialize a generation with only 1 individual
    node_str* my_generation[1];
    generate_new_generation(my_generation, 1, indiv_size, ot);

    // changes all the parameters of a randomly chosen node in the individual
    uint32_t new_item = (uint32_t) (osaka_listlength(my_generation[0]) * (rand() / (RAND_MAX + 1.0)) + 1);
    mutation_single_unit_all_params(my_generation[0], new_item, vis);

    // always free the generation at the end
    generate_free_generation(my_generation, 1);

    if (vis) {

        printf("\nTesting of basic mutation complete ---------------------------------------------------\n\n");

    }

}

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

void test_crossover_twopoint_diff(uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    // create generation with only 2 individuals
    node_str* my_generation[2];
    generate_new_generation(my_generation, 2, indiv_size, ot);

    // perform twopoint crossover where the points do not have to be the same across both individuals
    crossover_twopoint_diff(my_generation[0], my_generation[1], vis);

    // always free the generation
    generate_free_generation(my_generation, 2);

}

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

void test_copy_generation(uint32_t pop_size, uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    if (vis) {

        printf("Testing copying of a generation ------------------------------------------------------\n\n");

    }

    node_str* orig_gen[pop_size];
    node_str* new_gen[pop_size];

    generate_new_generation(orig_gen, pop_size, indiv_size, ot);

    if (vis) {
        
        for (int i = 0; i < pop_size; i++) {

            printf("Individual %d of original population: -------------------------------------------------\n", i);
            visualization_print_individual_verbose(orig_gen[i]);
            printf("\n");

        }

    }

    generate_copy_generation(orig_gen, new_gen, pop_size);

    if (vis) {
        
        for (int i = 0; i < pop_size; i++) {

            printf("Individual %d of copied population: ---------------------------------------------------\n", i);
            visualization_print_individual_verbose(new_gen[i]);
            printf("\n");

        }

    }

    if (vis) {

        printf("Testing of copying generations complete ----------------------------------------------\n\n");

    }

    generate_free_generation(orig_gen, pop_size);
    generate_free_generation(new_gen, pop_size);

}

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

void test_selection_tournament(uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, osaka_object_typ ot, bool vis, char* file) {

    if (vis) {

        printf("Testing tournament selection ---------------------------------------------------------\n\n");

    }

    node_str* winner = NULL;

    uint32_t winner_ind = 0;

    node_str* gen[pop_size];
    generate_new_generation(gen, pop_size, indiv_size, ot);

    if (vis) {
        
        printf("------------------------- Printing the entire generation -----------------------------\n\n");

        for (int i = 0; i < pop_size; i++) {

            printf("Individual %d: ------------------------------------------------------------------------\n\n", i);
            visualization_print_individual_concise_details(gen[i]);
            printf("\n\n");

        }

    }    

    winner_ind = selection_tournament(gen, winner, pop_size, tourn_size, vis, file);
    winner = gen[winner_ind];

    if (vis) {

        printf("Winner was node %d: -------------------------------------------------------------------\n\n", winner_ind);
        visualization_print_individual_concise_details(winner);
        printf("\n\n");
        
    }

    generate_free_generation(gen, pop_size);

    if (vis) {

        printf("Testing of tournament selection complete ---------------------------------------------\n\n");

    }

}

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

void test_selection_tournament_multiple(uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, osaka_object_typ ot, bool vis, char* file) {

    if (vis) {

        printf("Testing tournament selection multiple times ------------------------------------------\n\n");

    }

    node_str* winner1 = NULL;
    node_str* winner2 = NULL;
    node_str* winner3 = NULL;
    node_str* winner4 = NULL;
    node_str* winner5 = NULL;

    uint32_t winner1_ind = 0;
    uint32_t winner2_ind = 0;
    uint32_t winner3_ind = 0;
    uint32_t winner4_ind = 0;
    uint32_t winner5_ind = 0;

    node_str* gen[pop_size];
    generate_new_generation(gen, pop_size, indiv_size, ot);

    printf("getting here");

    winner1_ind = selection_tournament(gen, winner1, pop_size, tourn_size, vis, file);
    winner2_ind = selection_tournament(gen, winner2, pop_size, tourn_size, vis, file);
    winner3_ind = selection_tournament(gen, winner3, pop_size, tourn_size, vis, file);
    winner4_ind = selection_tournament(gen, winner4, pop_size, tourn_size, vis, file);
    winner5_ind = selection_tournament(gen, winner5, pop_size, tourn_size, vis, file);

    winner1 = gen[winner1_ind];
    winner2 = gen[winner2_ind];
    winner3 = gen[winner3_ind];
    winner4 = gen[winner4_ind];
    winner5 = gen[winner5_ind];

    if (vis) {

        printf("Winners that were selected: ----------------------------------------------------------\n\n");

        printf("Node %d: ----------------------------------------------------------------------------\n\n", UID(winner1));
        visualization_print_individual_concise_details(winner1);
        printf("\n\n");

        printf("Node %d: ----------------------------------------------------------------------------\n\n", UID(winner2));
        visualization_print_individual_concise_details(winner2);
        printf("\n\n");

        printf("Node %d: ----------------------------------------------------------------------------\n\n", UID(winner3));
        visualization_print_individual_concise_details(winner3);
        printf("\n\n");

        printf("Node %d: ----------------------------------------------------------------------------\n\n", UID(winner4));
        visualization_print_individual_concise_details(winner4);
        printf("\n\n");

        printf("Node %d: ----------------------------------------------------------------------------\n\n", UID(winner5));
        visualization_print_individual_concise_details(winner5);
        printf("\n\n");

    }

    generate_free_generation(gen, pop_size);

    if (vis) {

        printf("Testing of tournament selection multiple complete ------------------------------------\n\n");

    }

}


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

void test_generate_free_individual_inside_array(uint32_t pop_size, uint32_t indiv_size, osaka_object_typ ot, bool vis) {

    if (vis) {

        printf("Testing freeing individuals inside an array ------------------------------------------\n\n");
    
    }

    uint32_t copy_size = pop_size;

    node_str* gen[pop_size];
    generate_new_generation(gen, pop_size, indiv_size, ot);

    if (vis) {

        for (int i = 0; i < copy_size; i++) {
        
            printf("------------------ Printing Individual %d before removing any indivs ------------------\n\n", i);
            visualization_print_individual_concise_details(gen[i]);
            printf("\n\n");

        }

    }

    while (copy_size > 0) {

        uint32_t indiv_to_remove_ind = (uint32_t) (copy_size * (rand() / (RAND_MAX + 1.0)));
        node_str* indiv_to_remove = gen[indiv_to_remove_ind];

        if (vis) {

            printf("\nGoing to remove individual %d: --------------------------------------------------------\n\n", indiv_to_remove_ind);
            visualization_print_individual_concise_details(indiv_to_remove);
            printf("\n\n");

        }

        generate_free_individual_inside_array(gen, copy_size, indiv_to_remove_ind, gen[indiv_to_remove_ind]);

        copy_size = copy_size - 1;

        if (vis) {

            for (int i = 0; i < copy_size; i++) {
            
                printf("--------------------- Printing Individual %d after removing indiv ---------------------\n\n", i + 1);
                visualization_print_individual_concise_details(gen[i]);
                printf("\n\n");

            }

        }

    }

    if (vis) {

        printf("Testing freeing individuals inside an array complete ---------------------------------\n\n");

    }

}

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

void test_evolution_basic_crossover_and_mutation(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file) {

    if (vis) {

        printf("Testing the master basic evolution method --------------------------------------------\n\n");
    
    }

    node_str* best_indiv = evolution_basic_crossover_and_mutation(num_gens, pop_size, indiv_size, tourn_size, mut_perc, cross_perc, ot, vis, file);

    if (vis) {

        printf("Best individual that was passed back to the test: ------------------------------------\n\n");
        visualization_print_individual_concise_details(best_indiv);
        printf("\n\n--------------------------------------------------------------------------------------\n\n");

    }

    if (vis) {

        printf("Testing the master basic evolution method complete -----------------------------------\n\n");

    }

    generate_free_individual(best_indiv);

}

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

void test_evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, bool cache) {

    if (vis) {

        printf("Testing the master basic evolution method --------------------------------------------\n\n");
    
    }

    node_str* best_indiv = evolution_basic_crossover_and_mutation_with_replacement(num_gens, pop_size, indiv_size, tourn_size, mut_perc, cross_perc, ot, vis, file, cache);

    if (vis) {

        printf("Best individual that was passed back to the test: ------------------------------------\n\n");
        visualization_print_individual_concise_details(best_indiv);
        printf("\n\n--------------------------------------------------------------------------------------\n\n");

    }

    if (vis) {

        printf("Testing the master basic evolution method complete -----------------------------------\n\n");

    }

    generate_free_individual(best_indiv);

}

/*
 * NAME
 *
 *   test_system
 *
 * DESCRIPTION
 *
 *  Tests that the system command works as expected
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
 *  test_system();
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void test_system() {

    system("clang --version");

}

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

void test_master(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, bool cache) {

    //* Main Shackleton tests 
    //test_basic_printing(indiv_size, ot, vis);
    //test_onepoint_crossover(5, ot, vis);
    //test_crossover_twopoint_diff(10, ot, vis);
    //test_making_generation(2, 10, ot, vis);
    //test_basic_mutation(8, ot, vis);
    //test_copy_generation(1, 4, ot, vis);
    //test_selection_tournament(4, 4, 2, ot, vis, file);
    test_selection_tournament_multiple(pop_size, 5, tourn_size, ot, vis, file);
    //test_generate_free_individual_inside_array(pop_size, 20, ot, vis);
    //test_evolution_basic_crossover_and_mutation_with_replacement(num_gens, pop_size, 50, tourn_size, mut_perc, cross_perc, ot, vis, file, cache);
    //*/

    //* LLVM specific tests
    //test_llvm_form_opt_command_indiv("hello.cpp");
    //test_llvm_form_exec_code_command(file);
    //test_llvm_form_test_command();
    //test_system();
    //*/

    /* Possibly invalid tests
    test_evolution_basic_crossover_and_mutation(num_gens, pop_size, 20, tourn_size, mut_perc, cross_perc, ot, vis, file);
    test_evolution_basic_crossover_and_mutation(2, 4, 20, 2, 50, 75, ot, vis, file);
    */

}