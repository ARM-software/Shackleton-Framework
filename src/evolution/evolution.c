/*
 ============================================================================
 Name        : evolution.c
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
 ============================================================================
 */

/*
 * IMPORT
 */

#include "evolution.h"

/*
 * ROUTINES
 */

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

void evolution_create_new_gen_folder(char* main_folder, uint32_t gen) {

    char new_directory_name[70];
    char new_directory[80];
    char generation_num[4];

    strcpy(new_directory_name, main_folder);
    strcat(new_directory_name, "/generation_");
    sprintf(generation_num, "%d", gen);
    strcat(new_directory_name, generation_num);

    strcpy(new_directory, "mkdir ");
    strcat(new_directory, new_directory_name);

    system(new_directory);

}

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

node_str* evolution_basic_crossover_and_mutation(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file) {

    if (vis) {
        printf("Performing our basic tournament/crossover/mutation evolution -------------------------\n\n");
    }

    // indexes and temporary values to keep track of information
    uint32_t temp_crossover = 0;
    uint32_t temp_mutation1 = 0;
    uint32_t temp_mutation2 = 0;
    uint32_t fitness1 = 0;
    uint32_t fitness2 = 0;
    uint32_t copy_size = 0;
    uint32_t contestant1_ind = 0;
    uint32_t contestant2_ind = 0;
    uint32_t swap_ind = 0;

    node_str* contestant1_orig = NULL;
    node_str* contestant2_orig = NULL;
    node_str* contestant1 = NULL;
    node_str* contestant2 = NULL;
    node_str* best_node = NULL;
    node_str* final_node = NULL;

    node_str* current_generation[pop_size];
    node_str* copy_gen[pop_size];
    double fitness_values[pop_size];
    generate_new_generation(current_generation, pop_size, indiv_size, ot);

    // calculate initial fitness values for the current generation
    for (uint32_t k = 0; k < pop_size; k++) {
        fitness_values[k] = fitness_top(current_generation[k], false, file, false, NULL);
    }

    /*if (vis) {

        for (int i = 0; i < pop_size; i++) {
        
            printf("----------------------- Printing Individual %d before beginning -----------------------\n\n", i + 1);
            visualization_print_individual_concise_details(current_generation[i]);
            printf("\n\n");

        }

    }*/

    for (uint32_t g = 0; g < num_gens; g++) {

        if (vis) {

            printf("----------------------------------- Generation %d -----------------------------------\n\n", g + 1);

        }

        // at the start of every generation, copy over the last generation
        generate_copy_generation(current_generation, copy_gen, pop_size);
        copy_size = pop_size;

        for (uint32_t p = 0; p < (pop_size / 2); p++) {

            if (vis) {

                printf("---------------------------- Iteration %d of Generation %d ----------------------------\n\n", p + 1, g + 1);

            }

            contestant1_ind = selection_tournament(copy_gen, fitness_values, contestant1, copy_size, tourn_size, vis, file);
            contestant2_ind = selection_tournament(copy_gen, fitness_values, contestant2, copy_size, tourn_size, vis, file);

            // contestants cannot be the same individual, the indices must be different
            while (contestant1_ind == contestant2_ind) {
                contestant2_ind = selection_tournament(copy_gen, fitness_values, contestant2, copy_size, tourn_size, vis, file);
            }

            // swap if contestant1 comes before contestant2, swap so deletion order is correct
            if (contestant1_ind < contestant2_ind) {
                swap_ind = contestant1_ind;
                contestant1_ind = contestant2_ind;
                contestant2_ind = swap_ind;
            }

            // get actual individuals using the indices
            contestant1 = copy_gen[contestant1_ind];
            contestant2 = copy_gen[contestant2_ind];

            /*if (vis) {

                printf("Contestant 1 starts at node %d\n", UID(contestant1));
                printf("Contestant 2 starts at node %d\n\n", UID(contestant2));

            }*/

            temp_crossover = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
            temp_mutation1 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
            temp_mutation2 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));

            //printf("temp_crossover for this iteration: %d\n", temp_crossover);
            //printf("temp_mutation1 for this iteration: %d\n", temp_mutation1);
            //printf("temp_mutation2 for this iteration: %d\n", temp_mutation2);

            // random numbers are used to decide if the crossover or mutation operators will be used with a certain probability
            if (temp_crossover <= cross_perc) {
                crossover_onepoint_macro(contestant1, contestant2, vis);
            }
            if (temp_mutation1 <= mut_perc) {
                uint32_t random = (uint32_t) (indiv_size * (rand() / (RAND_MAX + 1.0))) + 1;
                mutation_single_unit_all_params(contestant1, random, vis);
            }
            if (temp_mutation2 <= mut_perc) {
                uint32_t random = (uint32_t) (indiv_size * (rand() / (RAND_MAX + 1.0))) + 1;
                mutation_single_unit_all_params(contestant2, random, vis);
            }

            // free individuals from current population to make room for new individuals
            generate_free_individual(current_generation[p]);
            generate_free_individual(current_generation[p + (pop_size / 2)]);

            // copy over new individuals into the new generation
            current_generation[p] = osaka_copylist(contestant1);
            current_generation[p + (pop_size / 2)] = osaka_copylist(contestant2);

            // remove the individuals from the copied generation
            generate_free_individual_inside_array(copy_gen, copy_size, contestant1_ind, contestant1);
            generate_free_individual_inside_array(copy_gen, copy_size - 1, contestant2_ind, contestant2);

            copy_size = copy_size - 2;

            if (vis) {

                printf("\n-------------- End of Iteration %d of Generation %d, copy_size is now %d ---------------\n\n", p + 1, g + 1, copy_size);

            }

        }

        // recalculate fitness values for the current generation
        for (uint32_t k = 0; k < pop_size; k++) {
            fitness_values[k] = fitness_top(current_generation[k], false, file, false, NULL);
        }

        /*if (vis) {

            for (int i = 0; i < pop_size; i++) {
        
                printf("------------------- Printing Individual %d at end of Generation %d --------------------\n\n", i + 1, g + 1);
                visualization_print_individual_concise_details(current_generation[i]);
                printf("\n\n");

            }

            printf("-------------------------------- End of Generation %d --------------------------------\n\n", g + 1);

        }*/

    }

    // is currently a dummy decision, will be replaces later with better logic
    best_node = current_generation[0];
    final_node = osaka_copylist(best_node);

    if (vis) {
        
        printf("Best node: ---------------------------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(final_node);
        printf("\n\n--------------------------------------------------------------------------------------\n\n");

    }

    // always free the generation at the end
    generate_free_generation(current_generation, pop_size);

    if (vis) {
        printf("Evolution complete -------------------------------------------------------------------\n\n");
    }
    
    return final_node;

}

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

node_str* evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, osaka_object_typ ot, bool vis, char* file, bool cache) {

    char main_folder[50];

    if (cache) {

        char hours_str[10], minutes_str[10], seconds_str[10], day_str[10], month_str[10], year_str[10]; 

        // get current date and time
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
    
        // get all values into a string format
        sprintf(hours_str, "%d", local->tm_hour);
        sprintf(minutes_str, "%d", local->tm_min);
        sprintf(seconds_str, "%d", local->tm_sec);
        sprintf(day_str, "%d", local->tm_mday);
        sprintf(month_str, "%d", local->tm_mon+1);
        sprintf(year_str, "%d", local->tm_year+1900);

        // form new directory in src/files/cache for this evolutionary run
        strcpy(main_folder, "src/files/cache/run_");
        strcat(main_folder, month_str);
        strcat(main_folder, "_");
        strcat(main_folder, day_str);
        strcat(main_folder, "_");
        strcat(main_folder, year_str);
        strcat(main_folder, "_");
        strcat(main_folder, hours_str);
        strcat(main_folder, "_");
        strcat(main_folder, minutes_str);
        strcat(main_folder, "_");
        strcat(main_folder, seconds_str);

        // create and run the command for making the new directory
        char create_dir[60];
        strcpy(create_dir, "mkdir ");
        strcat(create_dir, main_folder);
        system(create_dir);

    }

    if (vis) {
        printf("Performing our basic tournament/crossover/mutation evolution with replacement --------\n\n");
    }

    printf("%s", cache ? "true" : "false");

    // indexes and temporary values to keep track of information
    uint32_t temp_crossover = 0;
    uint32_t temp_mutation1 = 0;
    uint32_t temp_mutation2 = 0;
    uint32_t fitness1 = 0;
    uint32_t fitness2 = 0;
    uint32_t copy_size = 0;
    uint32_t contestant1_ind = 0;
    uint32_t contestant2_ind = 0;
    uint32_t swap_ind = 0;

    node_str* contestant1_orig = NULL;
    node_str* contestant2_orig = NULL;
    node_str* contestant1 = NULL;
    node_str* contestant2 = NULL;
    node_str* best_node = NULL;
    node_str* final_node = NULL;

    node_str* current_generation[pop_size];
    node_str* copy_gen[pop_size];
    double fitness_values[pop_size];
    generate_new_generation(current_generation, pop_size, indiv_size, ot);

    // calculate initial fitness values for the current generation
    for (uint32_t k = 0; k < pop_size; k++) {
        fitness_values[k] = fitness_top(current_generation[k], false, file, false, NULL);
    }

    if (vis) {

        for (int i = 0; i < pop_size; i++) {
        
            printf("----------------------- Printing Individual %d before beginning -----------------------\n\n", i + 1);
            visualization_print_individual_concise_details(current_generation[i]);
            printf("\n\n");

        }

    }

    for (uint32_t g = 0; g < num_gens; g++) {

        if (vis) {
            printf("----------------------------------- Generation %d -----------------------------------\n\n", g + 1);
        }

        if (cache) {
            evolution_create_new_gen_folder(main_folder, g);
        }

        // at the start of every generation, copy over the last generation
        generate_copy_generation(current_generation, copy_gen, pop_size);
        copy_size = pop_size;

        for (uint32_t p = 0; p < (pop_size / 2); p++) {

            if (vis) {
                printf("---------------------------- Iteration %d of Generation %d ----------------------------\n\n", p + 1, g + 1);
            }

            contestant1_ind = selection_tournament(copy_gen, fitness_values, contestant1, copy_size, tourn_size, vis, file);
            contestant2_ind = selection_tournament(copy_gen, fitness_values, contestant2, copy_size, tourn_size, vis, file);

            // contestants cannot be the same individual, the indices must be different
            while (contestant1_ind == contestant2_ind) {
                contestant2_ind = selection_tournament(copy_gen, fitness_values, contestant2, copy_size, tourn_size, vis, file);
            }

            // swap if contestant1 comes before contestant2, swap so deletion order is correct
            if (contestant1_ind < contestant2_ind) {
                swap_ind = contestant1_ind;
                contestant1_ind = contestant2_ind;
                contestant2_ind = swap_ind;
            }

            // get actual individuals using the indices
            contestant1 = copy_gen[contestant1_ind];
            contestant2 = copy_gen[contestant2_ind];

            if (vis) {
                printf("Contestant 1 starts at node %d\n", UID(contestant1));
                printf("Contestant 2 starts at node %d\n\n", UID(contestant2));
            }

            temp_crossover = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
            temp_mutation1 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
            temp_mutation2 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));

            // random numbers are used to decide if the crossover or mutation operators will be used with a certain probability
            if (temp_crossover <= cross_perc) {
                crossover_onepoint_macro(contestant1, contestant2, vis);
            }
            if (temp_mutation1 <= mut_perc) {
                uint32_t random = (uint32_t) (indiv_size * (rand() / (RAND_MAX + 1.0))) + 1;
                mutation_single_unit_all_params(contestant1, random, vis);
            }
            if (temp_mutation2 <= mut_perc) {
                uint32_t random = (uint32_t) (indiv_size * (rand() / (RAND_MAX + 1.0))) + 1;
                mutation_single_unit_all_params(contestant2, random, vis);
            }

            // free individuals from current population to make room for new individuals
            generate_free_individual(current_generation[p]);
            generate_free_individual(current_generation[p + (pop_size / 2)]);

            // copy over new individuals into the new generation
            current_generation[p] = osaka_copylist(contestant1);
            current_generation[p + (pop_size / 2)] = osaka_copylist(contestant2);

            if (vis) {
                printf("\n-------------- End of Iteration %d of Generation %d, copy_size is now %d ---------------\n\n", p + 1, g + 1, copy_size);
            }

        }

        // refresh fitness values for the current_generation
        for (uint32_t k = 0; k < pop_size; k++) {
            fitness_values[k] = fitness_top(current_generation[k], false, file, false, NULL);
        }

        generate_free_generation(copy_gen, copy_size);

        if (vis) {

            for (int i = 0; i < pop_size; i++) {
                printf("------------------- Printing Individual %d at end of Generation %d --------------------\n\n", i + 1, g + 1);
                visualization_print_individual_concise_details(current_generation[i]);
                printf("\n\n");
            }

        }

        if (cache) {

            char directory_name[70];
            char generation_num[4];

            sprintf(generation_num, "%d", g);

            strcpy(directory_name, main_folder);
            strcat(directory_name, "/generation_");
            strcat(directory_name, generation_num);

            for (int i = 0; i < pop_size; i++) {

                char individual_num[4];

                sprintf(individual_num, "%d", i);

                char cache_file[100];
                strcpy(cache_file, directory_name);
                strcat(cache_file, "/individual");
                strcat(cache_file, individual_num);
                strcat(cache_file, ".txt");

                fitness_top(current_generation[i], vis, file, true, cache_file);

            }

            char best_file[100];
            strcpy(best_file, directory_name);
            strcat(best_file, "/best_individual.txt");

            uint32_t winner = 0;
            double winner_value = fitness_values[0];

            for (uint32_t j = 1; j < pop_size; j++) {
                if (selection_compare_fitness(fitness_values[j], winner_value, ot)) {
                    winner = j;
                    winner_value = fitness_values[j];
                }
            }

            printf("\nBest fitness is that of individual %d : %f\n\n", winner, winner_value);

            fitness_llvm_pass_indiv_file(winner_value, current_generation[winner], best_file);

        }

        if (vis) {
            printf("-------------------------------- End of Generation %d --------------------------------\n\n", g + 1);
        }

    }

    // is currently a dummy decision, will be replaces later with better logic
    best_node = current_generation[0];
    final_node = osaka_copylist(best_node);

    if (vis) {
        printf("Best node: ---------------------------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(final_node);
        printf("\n\n--------------------------------------------------------------------------------------\n\n");
    }

    // always free the generation at the end
    generate_free_generation(current_generation, pop_size);

    if (vis) {
        printf("Evolution complete -------------------------------------------------------------------\n\n");
    }
    
    return final_node;

}