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

void evolution_cache_generation_old(bool cache, char* main_folder, uint32_t gen, uint32_t pop_size, node_str** curr_gen, bool vis, char* file, char** src_files, uint32_t num_src_files, double* fitness_values, osaka_object_typ ot,double* track_fitness, int offset) {
//added 6/2/2021
//void evolution_cache_generation(char* main_folder, uint32_t gen, uint32_t pop_size, node_str** curr_gen, bool vis, char* file, char** src_files, uint32_t num_src_files, double* fitness_values, osaka_object_typ ot) {
    if (!cache) {
        return;
    }
    char directory_name[300];
    char generation_name[20];

    if (gen == -1) {
        //printf("writing best individual in intial population\n");
        sprintf(generation_name, "/initial_fitness");
    } else {
        sprintf(generation_name, "/generation_%d", gen+1);
    }

    strcpy(directory_name, main_folder);
    strcat(directory_name, generation_name);

    // add additional file for best individual in the generation
    char best_file[300];
    strcpy(best_file, directory_name);
    strcat(best_file, "/best_individual.txt");

    //printf("best_file: %s\n", best_file);

    uint32_t winner_ind = 0;
    double winner_value = fitness_values[0];
    for (uint32_t j = 1; j < pop_size; j++) {
        if (selection_compare_fitness(fitness_values[j], winner_value, ot)) {
            winner_ind = j;
            winner_value = fitness_values[j];
        }
    }
    node_str* winner_seq = curr_gen[winner_ind];


    // printing out fitness values for user's convenience, a sanity check
    /*for (uint32_t i = 0; i < pop_size; i++) {
        printf("fitness for %d is %f\n", i, fitness_values[i]);
    }
    printf("\nbest fitness is that of %d, %f\n", winner, winner_value);*/
    fitness_cache(winner_value, winner_seq, best_file);

    track_fitness[gen + offset] = winner_value;
    
    //return winner_value; //added 6/2/2021
    return;
}

void select_elites(int pop_size, int num_elites, double* fitness_values, int* current_gen_id, int* elite_indx, int* elite_id) {
    for (int i = 0; i < pop_size; i++) {
        printf("%s%d: %lf%s", i==0?"pop_fitness=[":"", current_gen_id[i], fitness_values[i], i==pop_size-1? "]\n":", ");
    }
    // update elite list as the best N individuals in the generation
    for (uint32_t e = 0; e < num_elites; e++) {
        elite_indx[e] = -1;
        elite_id[e] = -1;
    }
    for (int k = 0; k < pop_size; k++) {
        if (is_in_list(current_gen_id[k], elite_id, num_elites)) {
            continue; //to avoid populating elites with the same sequence (happens when sequence repeats in population)
        }
        for (int e = num_elites-1; e >= 0; e--) {
            if (elite_indx[e] == -1 || fitness_values[k] < fitness_values[elite_indx[e]]) {
                if (e != 0) {
                    elite_indx[e] = elite_indx[e - 1];
                    elite_id[e] = elite_indx[e]==-1? -1 : current_gen_id[elite_indx[e - 1]];
                } else {
                    elite_indx[e] = k;
                    elite_id[e] = current_gen_id[k];
                }
            } else {
                if (e < num_elites-1 && fitness_values[k] >= fitness_values[elite_indx[e]] && elite_indx[e] == elite_indx[e+1]) {
                    elite_indx[e + 1] = k;
                    elite_id[e + 1] = current_gen_id[k];
                }
            }
        }
    }
    //printf("Done selecting elites\n");
}

/*
Generate log file name for best individual and find best fitness;
Log best_individual to its own file and summary file 
*/
void evolution_cache_gen(bool cache, char* main_folder, \
            node_str** current_generation, double* fitness_values, int* current_gen_id, \
            double* track_fitness, \
            int pop_size, int num_gens, int g, int offset, osaka_object_typ ot) {
    if (!cache) {
        return;
    }
    // add additional file for best individual in the generation
    char best_file[300];
    strcpy(best_file, main_folder);
    strcat(best_file, "/best/best");

    char temp[50];
    strcpy(temp, "");
    if (g == -1) {
        sprintf(temp, "_initial.txt");
    } else {
        sprintf(temp, "_generation_%d.txt", g+1);
    }
    strcat(best_file, temp);

    // find best fitness
    int winner_index = find_best(fitness_values, pop_size, ot);
    int winner_id = current_gen_id[winner_index];
    double winner_fitness = fitness_values[winner_index];
    node_str* winner_seq = current_generation[winner_index];
    
    track_fitness[g + offset] = winner_fitness;
    //printf("saved to track_fitness\n");
    node_cache_llvm_pass(best_file, winner_seq, winner_fitness, winner_id);
    
    // print out and export the ID and fitness information to summary file
    evolution_log_to_summary(cache, main_folder, fitness_values, current_gen_id, winner_fitness, pop_size, num_gens, g, offset);
}

int find_best(double* fitness_values, int pop_size, osaka_object_typ ot) {
    // actually finding the individual with the best fitness
    uint32_t winner_ind = 0;
    double winner_fitness = fitness_values[0];
    for (uint32_t j = 1; j < pop_size; j++) {
        if (selection_compare_fitness(fitness_values[j], winner_fitness, ot)) {
            winner_ind = j;
            winner_fitness = fitness_values[j];
        }
    }
    return winner_ind;
}
    
void evolution_log_to_summary(bool cache, char* main_folder, \
            double* fitness_values, int* current_gen_id, \
            double winner_fitness, \
            int pop_size, int num_gens, int g, int offset) {
    // print out and export the ID and fitness information to summary file
    if (!cache) {
        return;
    }
    // log to /main_folder/track_fitness.csv
    char track_fitness_file[300];
    strcpy(track_fitness_file, main_folder);
    strcat(track_fitness_file, "/track_fitness.csv");
    FILE* track_fitness_file_ptr = fopen(track_fitness_file, "a");
    fprintf(track_fitness_file_ptr, "%lf%s", winner_fitness, g==num_gens-1?"\n":",");
    fclose(track_fitness_file_ptr);

    // log to /main_folder/test_compare.csv
    if (g == -1) { // if initial generation, no need to redo baseline evaluation, just add best fitness to end of line
        char test_compare_file[300];
        strcpy(test_compare_file, main_folder);
        strcat(test_compare_file, "/test_compare.csv");
        FILE* test_compare_ptr = fopen(test_compare_file, "a+");
        fprintf(test_compare_ptr, "%lf\n", winner_fitness);
        fclose(test_compare_ptr);
    }
    
    // track all id changes over generation, and a separate file recording their fitness
    // set up before constructing the all_indiv table so this is no longer needed
    /*for (int k = 0; k < pop_size; k++) {
        if (cache) {
            char track_id_file[300];
            strcpy(track_id_file, main_folder);
            strcat(track_id_file, "/track_id.csv");
            char track_all_fitness_file[300];
            strcpy(track_all_fitness_file, main_folder);
            strcat(track_all_fitness_file, "/track_all_fitness.csv");

            FILE* track_id_file_ptr = fopen(track_id_file, "a");
            FILE* track_all_fitness_file_ptr = fopen(track_all_fitness_file, "a");
            if (k == 0) {
                fprintf(track_id_file_ptr, "%s%d, %d%s", g==-1?"initial":"gen", g+1, current_gen_id[k], k<pop_size-1?",":"\n");
                fprintf(track_all_fitness_file_ptr, "%s%d, %d%s", g==-1?"initial":"gen", g+1, fitness_values[k], k<pop_size-1?",":"\n");
            } else {
                fprintf(track_id_file_ptr, "%d%s", current_gen_id[k], k<pop_size-1?",":"\n");
                fprintf(track_all_fitness_file_ptr, "%lf%s", fitness_values[k], k<pop_size-1?",":"\n");
            }
            fclose(track_id_file_ptr);
            fclose(track_all_fitness_file_ptr);
        }
    }*/
    //printf("Done logging to all files\n");
}

void print_elites(int num_elites, int* elite_indx, double* fitness_values, int* elite_id, node_str** current_gen) {
    printf("Created elite population of size %d: ", num_elites);
    if (num_elites > 0) {
        printf("elite_id=[");
    }
    for (int e = 0; e < num_elites; e++) {
        printf("%d (len=%d)%s", elite_id[e], osaka_listlength(current_gen[e]), (e==num_elites-1)?"], fitness=([":", ");
    }
    for (int e = 0; e < num_elites; e++) {
        printf("%lf%s", fitness_values[elite_indx[e]], (e==num_elites-1)?"])\n":", ");
    }
}

void print_random(int num_new_random, int num_elites, int* current_gen_id) {
    printf("Created random population of size %d: ", num_new_random);
    if (num_new_random > 0) {
        printf("new_alleles=[");
    }
    for (int e = 0; e < num_new_random; e++) {
        printf("%d%s", current_gen_id[num_elites+e], (e==num_new_random-1)?"]\n":", ");
    }
}

void create_elites(int num_elites, int* elite_indx, node_str** copy_gen, node_str** current_generation, int* copy_gen_id, int* current_gen_id, double* fitness_values) {
    for (uint32_t p = 0; p < num_elites; p++) {
        int elite_ind = elite_indx[p];
        node_str* elite = osaka_copylist(copy_gen[elite_ind]);
        // free individuals from current population to make room for elite individuals
        generate_free_individual(current_generation[p]);
        //printf("Freed individual #%d for elite #%d of %d\n", p, p+1, num_elites);
        current_generation[p] = elite;
        current_gen_id[p] = copy_gen_id[elite_ind];
    }
    //printf("Done filling up elites for the generation\n");
}

void create_randoms(int num_elites, int num_new_random, int* max_id_ptr, node_str** current_generation, int* current_gen_id, int indiv_size, osaka_object_typ ot, DataNode*** all_indiv_ptr, int* hash_cap_ptr) {
    //printf("\nbeginning of create_randoms, max_id=%d\n\n", *max_id);
    int new_allele_id;
    node_str* new_seq;
    for (uint32_t p = num_elites; p < num_elites + num_new_random; p++) {
        new_seq = generate_new_individual(indiv_size,ot);
        new_allele_id = node_add(new_seq, max_id_ptr, hash_cap_ptr, all_indiv_ptr, ot);
        //fitness_top(offsprings[i], vis, test_file, src_files, num_src_files, false, NULL, cache_id, (*all_indiv_ptr)[ofs_id[i]], num_runs, g, fitness_with_var);
        
        // free individuals from current population to make room for elite individuals
        generate_free_individual(current_generation[p]);
        //printf("Freed individual #%d for new allele #%d of %d (id=%d)\n", p, p-num_elites+1, num_elites, new_allele_id);
        current_generation[p] = new_seq;
        current_gen_id[p] = new_allele_id;
        //printf("new diversity allele created, unique ID: %d\n", new_allele_id);
    }
    //printf("Done filling up new individuals for the generation, max_id=%d\n", *max_id_ptr);
}

void select_parents(uint32_t* contestant1_ind, uint32_t* contestant2_ind, node_str** copy_gen, double* fitness_values, int copy_size, int tourn_size, bool vis) {
    //printf("inside select parents\n");
    uint32_t c1 = selection_tournament(copy_gen, fitness_values, NULL, copy_size, tourn_size, vis);
    uint32_t c2 = selection_tournament(copy_gen, fitness_values, NULL, copy_size, tourn_size, vis);
    
    // contestants cannot be the same individual, the indices must be different
    while (c1 == c2) {
        c2 = selection_tournament(copy_gen, fitness_values, NULL, copy_size, tourn_size, vis);
    }

    // swap if contestant1 comes before contestant2, swap so deletion order is correct
    if (c1 < c2) {
        uint32_t swap_ind = c1;
        c1 = c2;
        c2 = swap_ind;
    }
    
    // get actual individuals using the indices
    //*contestant1 = osaka_copylist(copy_gen[c1]);
    //*contestant2 = osaka_copylist(copy_gen[c2]);

    //printf("parents selected: c1: ind=%d, fitness=%lf, c2: ind=%d, fitness=%lf\n", c1, fitness_values[c1], c2, fitness_values[c2]);
    //printf("Contestants copied\n");

    *contestant1_ind = c1;
    *contestant2_ind = c2;
    //printf("Done selecting parents, contestant1_ind=%d, contestant2_ind=%d\n", c1, c2);
}

void generate_offspring(int parent1_ind, int parent2_ind, node_str** copy_gen, int* copy_gen_id, int num_offspring, node_str** offsprings, bool* ofs_change, int* ofs_id, uint32_t cross_perc, uint32_t mut_perc, bool vis, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr, osaka_object_typ ot) {
    for (int i = 0; i < num_offspring; i++) {
        ofs_change[i] = false;
        //printf("offspring #%d\n", i);
        if (i % 2 == 0) {
            offsprings[i] = osaka_copylist(copy_gen[parent1_ind]);
            ofs_id[i] = copy_gen_id[parent1_ind];
            if (i == num_offspring - 1) {
                node_str* temp = osaka_copylist(copy_gen[parent2_ind]);
                bool temp_change;
                genetic_operators(temp, offsprings[i], &temp_change, &ofs_change[i], cross_perc, mut_perc, vis);
                if (ofs_change[i]) {
                    ofs_id[i] = node_add(offsprings[i], max_id_ptr, hash_cap_ptr, all_indiv_ptr, ot);
                }
                generate_free_individual(temp);
            }
        }
        else {
            offsprings[i] = osaka_copylist(copy_gen[parent2_ind]);
            ofs_id[i] = copy_gen_id[parent2_ind];
            if (i != 1) {
                genetic_operators(offsprings[i-1], offsprings[i], &ofs_change[i-1], &ofs_change[i], cross_perc, mut_perc, vis);
                //printf("ofs_change[%d]=%s, ofs_change[%d]=%s\n", i-1, ofs_change[i-1]?"true":"false", i, ofs_change[i]?"true":"false");
                if (ofs_change[i-1]) {
                    ofs_id[i-1] = node_add(offsprings[i-1], max_id_ptr, hash_cap_ptr, all_indiv_ptr, ot);
                }
                if (ofs_change[i]) {
                    ofs_id[i] = node_add(offsprings[i], max_id_ptr, hash_cap_ptr, all_indiv_ptr, ot);
                }
            }
        }
    }
    //printf("Done generating offspring\n");
}

void genetic_operators(node_str* contestant1, node_str* contestant2, bool* c1_change, bool* c2_change, uint32_t cross_perc, uint32_t mut_perc, bool vis) {
    bool c1 = false, c2 = false;
    uint32_t temp_crossover = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
    uint32_t temp_mutation1 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
    uint32_t temp_mutation2 = (uint32_t) (100 * (rand() / (RAND_MAX + 1.0)));
    
    // random numbers are used to decide if the crossover or mutation operators will be used with a certain probability
    if (temp_crossover <= cross_perc) {
        crossover_onepoint_macro(contestant1, contestant2, vis);
        c1 = true;
        c2 = true;
    }
    //printf("Done applying crossover\n");
    if (temp_mutation1 <= mut_perc) {
        uint32_t indiv_size_1 = osaka_listlength(contestant1);
        uint32_t random = (uint32_t) (indiv_size_1 * (rand() / (RAND_MAX + 1.0))) + 1;
        mutation_single_unit_all_params(contestant1, random, vis);
        c1 = true;
    }
    //printf("Done applying mutation 1\n");
    if (temp_mutation2 <= mut_perc) {
        uint32_t indiv_size_2 = osaka_listlength(contestant2);
        uint32_t random = (uint32_t) (indiv_size_2 * (rand() / (RAND_MAX + 1.0))) + 1;
        mutation_single_unit_all_params(contestant2, random, vis);
        c2 = true;
    }
    //printf("Done applying mutation 2\n");
    *c1_change = c1;
    *c2_change = c2;
    //printf("Done applying genetic operators, c1_change=%s, c2_change=%s\n", c1?"true":"false", c2?"true":"false");
}

void select_offspring(node_str** best, int* best_id, node_str** offsprings, bool* ofs_change, int* ofs_id, int num_offspring, int parent1_ind, int parent2_ind, double* fitness_values, bool vis, char* test_file, char** src_files, uint32_t num_src_files, bool cache, char* cache_file, const char *cache_id, int g, DataNode*** all_indiv_ptr, uint32_t num_runs, bool fitness_with_var) {
    //printf("\nInside select_offspring, calculating offspring fitness, num_offspring=%d:\n", num_offspring);

    double ofs_fitness[num_offspring];
    for (int i = 0; i < num_offspring; i++) {
        ofs_fitness[i] = fitness_top(offsprings[i], vis, test_file, src_files, num_src_files, false, NULL, cache_id, (*all_indiv_ptr)[ofs_id[i]], num_runs, g, fitness_with_var);
        //printf("offspring #%d: fitness=%lf\n", i, ofs_fitness[i]);
    }
    //printf("Done calculating offspring fitness:\n");

    double min1_fit = ofs_fitness[0];
    int min1_ind = 0;
    double min2_fit = ofs_fitness[1];
    int min2_ind = 1;
    for (int i = 2; i < num_offspring; i++) {
        if (i % 2 == 0 && ofs_fitness[i] < min1_fit) {
            min1_fit = ofs_fitness[i];
            min1_ind = i;
        }
        if (i % 2 == 1 && ofs_fitness[i] < min2_fit) {
            min2_fit = ofs_fitness[i];
            min2_ind = i;
        }
    }
    /*
    printf("Best 2 individuals among all offsprings found:\n");
    printf("indiv 1: ofs_ind=%d, fitness=%lf, change=%s\n", min1_ind, min1_fit, ofs_change[min1_ind]?"true":"false");
    printf("indiv 2: ofs_ind=%d, fitness=%lf, change=%s\n", min2_ind, min2_fit, ofs_change[min2_ind]?"true":"false");
    */
    best[0] = osaka_copylist(offsprings[min1_ind]);
    best[1] = osaka_copylist(offsprings[min2_ind]);
    best_id[0] = ofs_id[min1_ind];
    best_id[1] = ofs_id[min2_ind];
    /*printf("ofs_id: [");
    for (int i = 0; i < num_offspring; i++) {
        printf("%d%s", ofs_id[i], i==num_offspring-1? "]\n":", ");
    }
    printf("best_id[0]=%d, best_id[1]=%d\n", best_id[0], best_id[1]);*/
    
    generate_free_generation(offsprings, num_offspring);

    /*printf("\nbest[0]: ");
    visualization_print_individual_concise_details(best[0]);
    printf("\nbest[1]: ");
    visualization_print_individual_concise_details(best[1]);
    printf("\n");*/

    //printf("Done selecting offspring\n");
}

void update_generation(node_str* contestant1, node_str* contestant2, int c1_id, int c2_id, node_str** current_generation, int* current_gen_id, int pop_size, int num_elites, int num_new_random, int p) {
    generate_free_individual(current_generation[num_elites + num_new_random + p]);
    //printf("Freed individual #%d for contestant 1\n", num_elites + num_new_random + p);
    current_generation[num_elites + num_new_random + p] = contestant1;
    current_gen_id[num_elites + num_new_random + p] = c1_id;

    //free//
    generate_free_individual(current_generation[num_elites + num_new_random + p + ((pop_size-num_elites-num_new_random) / 2)]);
    //printf("Freed individual #%d for contestant 2\n\n", num_elites + num_new_random + p + ((pop_size-num_elites-num_new_random) / 2));
    current_generation[num_elites + num_new_random + p + ((pop_size-num_elites-num_new_random) / 2)] = contestant2;
    current_gen_id[num_elites + num_new_random + p + ((pop_size-num_elites-num_new_random) / 2)] = c2_id;
    
    //printf("Done updating generation\n");
}

void create_mutants(node_str** copy_gen, node_str** current_generation, double* fitness_values,\
                        int* copy_gen_id, int* current_gen_id, int* max_id_ptr, \
                        uint32_t tourn_size, uint32_t pop_size, uint32_t cross_perc, uint32_t mut_perc, \
                        uint32_t num_elites, uint32_t num_new_random, uint32_t copy_size, \
                        uint32_t num_runs, uint32_t num_offspring, \
                        char* file, char** src_files, uint32_t num_src_files, \
                        bool vis, int g, osaka_object_typ ot,\
                        bool cache, char* cache_file, const char* cache_id, \
                        DataNode*** all_indiv_ptr, int* hash_cap_ptr, bool fitness_with_var) {
    uint32_t contestant1_ind = 0;
    uint32_t contestant2_ind = 0;
    node_str* offsprings[num_offspring];
    bool ofs_change[num_offspring];
    double ofs_fitness[num_offspring];
    int ofs_id[num_offspring];
    node_str* ofs_best[2];
    int best_id[2];

    for (uint32_t itr = 0; itr < ((pop_size - num_elites - num_new_random) / 2); itr++) {
        //printf("About to fill in position %d and %d\n", num_elites + num_new_random + itr, num_elites + num_new_random + itr + ((pop_size-num_elites-num_new_random) / 2));
        vis_itr(vis, itr, g);
        //printf("before select_parents\n");
        select_parents(&contestant1_ind, &contestant2_ind, \
                                copy_gen, fitness_values, \
                                copy_size, tourn_size, vis);
        //printf("after select_parents\n");
        //printf("before generate_offspring\n");
        generate_offspring(contestant1_ind, contestant2_ind, \
                                copy_gen, copy_gen_id, \
                                num_offspring, offsprings, ofs_change, ofs_id, \
                                cross_perc, mut_perc, vis, 
                                max_id_ptr, hash_cap_ptr, all_indiv_ptr, ot);
        //printf("after generate_offspring\n");
        vis_print_parents(vis, offsprings);
        //printf("before select_offspring\n");
        select_offspring(ofs_best, best_id, offsprings, ofs_change, ofs_id, num_offspring, \
                                contestant1_ind, contestant2_ind, \
                                fitness_values, \
                                vis, file, src_files, num_src_files, \
                                cache, cache_file, cache_id, g, \
                                all_indiv_ptr, num_runs, fitness_with_var);
        //printf("after select_offspring\n");
        //printf("before update_generation\n");
        update_generation(ofs_best[0], ofs_best[1], \
                                best_id[0], best_id[1], \
                                current_generation, current_gen_id, \
                                pop_size, num_elites, num_new_random, itr);
        //printf("after update_generation\n");
    }
    //printf("Done creating mutants\n");
}

void log_all_indiv_info(bool cache, DataNode** all_indiv, char* main_folder, int num_runs, int max_id) {
    if (cache) {
        char indiv_info_file[300];
        strcpy(indiv_info_file, main_folder);
        strcat(indiv_info_file, "/indiv_info.csv");
        FILE* indiv_info_file_ptr = fopen(indiv_info_file, "a+");;
        fprintf(indiv_info_file_ptr, "ID,num_eval,tot_gen,gen_#,avg_time,var,success_runs,");
		for (int k = 0; k < num_runs-1; k++) {
            fprintf(indiv_info_file_ptr, "run_%d,", k+1);
        }
        fprintf(indiv_info_file_ptr, "run_%d\n", num_runs);
        fclose(indiv_info_file_ptr);
        char indiv_info_dir[300];
        strcpy(indiv_info_dir, "");
        strcat(indiv_info_dir, main_folder);
        strcat(indiv_info_dir, "/all_individuals");
        cache_create_new_folder(indiv_info_dir);
        for (int i = 0; i < max_id; i++) {
            DataNode* indiv = all_indiv[i];
            node_log(indiv_info_dir, indiv_info_file, indiv);
            //node_print(indiv, i);
        }
    }
    //printf("Done logging generation\n");
}

void log_redo_basic(char* main_folder, char* file, bool cache, const char *cache_id, double best_fitness, uint32_t num_runs, bool fitness_with_var, int g, const char** levels, const int num_levels) {
    if (!cache) {
        return;
    }
    if ((g+1) % 5 == 0) {
        printf("\n-----------------------------Redo Basic LLVM opt Levels-----------------------------\n");
        double temp_track[num_levels];
        fitness_redo_basic(main_folder, file, cache, temp_track, cache_id, num_runs, fitness_with_var, levels, num_levels);
        char test_compare[200];
        strcpy(test_compare, main_folder);
        strcat(test_compare, "/test_compare.csv");
        FILE* test_compare_ptr = fopen(test_compare, "a+");

        fprintf(test_compare_ptr, "%d,", g+1);
        for (int i = 0; i < num_levels; i++) {
            fprintf(test_compare_ptr, "%lf,", temp_track[i]);
        }
        fprintf(test_compare_ptr, "%lf\n", best_fitness);
        fclose(test_compare_ptr);
    }
}

bool check_termination(double best_fitness, double* lowest_ptr, int* stale_counter_ptr, const int stale_limit) {
    //printf("stale_counter=%d\n", *stale_counter_ptr);
    if (best_fitness < *lowest_ptr) {
        *lowest_ptr = best_fitness;
        *stale_counter_ptr = 0;
    } else {
        (*stale_counter_ptr)++;
    }
    if (*stale_counter_ptr >= stale_limit) {
        printf("Number of stale generations: %d reaches stale_limit=%d, evolution terminates\n", *stale_counter_ptr, stale_limit);
        return true;
    }
    return false;
}

int evolution_clean_up(int num_elites, node_str** current_generation, uint32_t pop_size, \
                                bool vis, char* main_folder, char* file, const char* cache_id, bool cache, \
                                DataNode** all_indiv, int num_runs, int max_id, int g, \
                                osaka_object_typ ot, double* fitness_values, int* current_gen_id) {
    // is currently a dummy decision, will be replaces later with better logic
    if (vis) {
        printf("Evolution complete -------------------------------------------------------------------\n\n");
    }
    
    // find best fitness
    int winner_index = find_best(fitness_values, pop_size, ot);
    int best_node_id = current_gen_id[winner_index];
    double best_fitness = fitness_values[winner_index];
    node_str* best_node = current_generation[winner_index];
    node_str* final_node = osaka_copylist(best_node);
    vis_best_node(vis, final_node);

    if (cache) {
        // log information to cache
        char final_file[300];
        strcpy(final_file, main_folder);
        strcat(final_file, "/final_node.txt");
        node_cache_llvm_pass(final_file, final_node, best_fitness, best_node_id);
        //log_all_indiv_info(cache, all_indiv, main_folder, num_runs, max_id);
    }
    

    // free allocated space
    free_all_nodes(all_indiv, max_id);
    free(all_indiv);
    generate_free_generation(current_generation, pop_size);
    if (ot == 3) {
        llvm_clean_up(file, cache_id, cache);
    }
    generate_free_individual(final_node);
    return g;
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

int evolution_basic_crossover_and_mutation_with_replacement(uint32_t num_gens, uint32_t pop_size, uint32_t indiv_size, uint32_t tourn_size, uint32_t mut_perc, uint32_t cross_perc, uint32_t elite_perc, osaka_object_typ ot, bool vis, char* file, char** src_files, uint32_t num_src_files, bool cache, double *track_fitness, const char *cache_id, const char** levels, const int num_levels, bool gi) {
    if (vis) {
        printf("Performing basic tournament/crossover/mutation evolution with replacement --------\n\n");
    }
    
    // indexes and temporary values to keep track of information
    uint32_t num_elites = elite_perc * pop_size / 100;
    uint32_t num_new_random = num_elites;
    int elite_indx[num_elites];
    int elite_id[num_elites];
    for (uint32_t e = 0; e < num_elites; e++) {
        elite_indx[e] = -1;
        elite_id[e] = -1;
    }
    double lowest = UINT32_MAX; //Lowest runtime encountered, for termination criteria only
    int stale_counter = 0;      //Number of generations without new low, for termination criteria only
    const int stale_limit = 10;

    double fitness_values[pop_size];
    node_str* current_generation[pop_size];
    node_str* copy_gen[pop_size];
    int current_gen_id[pop_size];
    int copy_gen_id[pop_size];
    int max_id = 0;
    /* number of positions that generation fitness from shackleton is offset in the track_fitness vector 
       because fitness for basic optimization levels and initial generation are recorded before them */
    int offset = num_levels + 1;  

    // variables used for caching
    int hash_cap = pop_size * 5;
    DataNode** all_indiv = calloc(hash_cap, sizeof(DataNode*));
    DataNode* indiv_data = NULL;
    
    char main_folder[200];
    char cache_file[300];

    // variables used for selecting offspring
    int num_offspring = 6;  // HAS TO BE GREATER THAN 2: 2 offsprings will be identical to parents, and num_offspring-2 new individuals
    uint32_t num_runs = 40;
    bool fitness_with_var = false;

    cache_create_new_run_folder(cache, main_folder, cache_id);
    cache_params(cache, main_folder, num_gens, pop_size, cross_perc, mut_perc, elite_perc, tourn_size);
    fitness_pre_cache(main_folder, file, src_files, num_src_files, ot, cache, track_fitness, cache_id, num_runs, fitness_with_var, levels, num_levels);

    // create the initial population
    generate_new_generation(current_generation, pop_size, indiv_size, ot, gi, levels, num_levels);
    node_add_group(current_generation, current_gen_id, pop_size, &max_id, &hash_cap, &all_indiv, ot);
    for (int i = 0; i < pop_size; i++) {
        printf("%s%d%s", i==0? "current_gen_id=[":"", current_gen_id[i], i==pop_size-1?"]\n":", ");
    }
    // calculate initial fitness values for the current generation
    //cache_create_new_gen_folder(cache, main_folder, -1);
    cache_create_best_indiv_folder(cache, main_folder);
    printf("\n----------------------------------- Initial Population -----------------------------------\n");
    int generation_num = -1;
    for (uint32_t k = 0; k < pop_size; k++) {
        //printf("-----------------------------------------------------------------------------\n");
        //printf("Calculate initial fitness - individual #%d out of %d, ID=%d (max_id=%d)\n", k+1, pop_size, current_gen_id[k], max_id);
        //printf("-----------------------------------------------------------------------------\n");
        cache_file_name(cache, main_folder, cache_file, -1, k);
        //indiv_data = all_indiv[k];  // Added7/7/2021
        indiv_data = all_indiv[current_gen_id[k]];
        fitness_values[k] = fitness_top(current_generation[k], vis, file, src_files, num_src_files, cache, cache_file, cache_id, indiv_data, num_runs, generation_num, fitness_with_var); // Added 6/24/2021
        node_increment_gen(indiv_data);
        //=%lf\n", fitness_values[k]);
    }
    // if cache, record generation information
    //evolution_cache_generation(cache, main_folder, -1, pop_size, current_generation, vis, file, src_files, num_src_files, fitness_values, ot, track_fitness);
    // update elite list as the best N individuals in the generation
    select_elites(pop_size, num_elites, fitness_values, current_gen_id, elite_indx, elite_id);
    // print out and export the ID and fitness information
    evolution_cache_gen(cache, main_folder, current_generation, fitness_values, current_gen_id, track_fitness, pop_size, num_gens, generation_num, offset, ot);
    vis_print_gen(vis, false, current_generation, -1, pop_size);

    for (uint32_t g = 0; g < num_gens; g++) {
        printf("----------------------------------- Generation %d -----------------------------------\n\n", g + 1);
        //printf("start of generation, cache_id: %s\n", cache_id);
        //cache_create_new_gen_folder(cache, main_folder, g);
        // at the start of every generation, copy over the last generation
        generate_copy_generation(current_generation, copy_gen, pop_size);
        generate_copy_gen_id(current_gen_id, copy_gen_id, pop_size);
        
        // evolution and selection
        //printf("before create_elites\n");
        create_elites(num_elites, elite_indx, \
                        copy_gen, current_generation, \
                        copy_gen_id, current_gen_id, \
                        fitness_values);
        print_elites(num_elites, elite_indx, fitness_values, elite_id, current_generation);
        //printf("after create_elites\n");

        //printf("before create_randoms\n");
        create_randoms(num_elites, num_new_random, &max_id, \
                        current_generation, current_gen_id, \
                        indiv_size, ot, \
                        &all_indiv, &hash_cap);
        print_random(num_new_random, num_elites, current_gen_id);
        //printf("after create_randoms\n");

        //printf("before create_mutants\n");
        create_mutants(copy_gen, current_generation, fitness_values,\
                        copy_gen_id, current_gen_id, &max_id, \
                        tourn_size, pop_size, cross_perc, mut_perc, \
                        num_elites, num_new_random, pop_size, \
                        num_runs, num_offspring, \
                        file, src_files, num_src_files, \
                        vis, g, ot,\
                        cache, cache_file, cache_id, \
                        &all_indiv, &hash_cap, fitness_with_var);
        //printf("after create_mutants\n");
        
        printf("old generation ID: [");
        for (int i = 0; i < pop_size; i++) {
            printf("%d%s", copy_gen_id[i], i==pop_size-1? "]\n":",");
        }
        printf("new generation ID: [");
        for (int i = 0; i < pop_size; i++) {
            printf("%d%s", current_gen_id[i], i==pop_size-1? "]\n":",");
        }
        generate_free_generation(copy_gen, pop_size);

        // refresh fitness values for the current_generation
        for (uint32_t k = 0; k < pop_size; k++) {
            /*
            printf("-------------------------------------------------------------------------------\n");
            printf("Refresh fitness for individual %d of %d in generation %d of %d, ID=%d (max_id=%d)\n", k+1, pop_size, g+1, num_gens, current_gen_id[k], max_id);
            printf("-------------------------------------------------------------------------------\n");
            */
            cache_file_name(cache, main_folder, cache_file, g, k);
            indiv_data = all_indiv[current_gen_id[k]];
            fitness_values[k] = fitness_top(current_generation[k], vis, file, src_files, num_src_files, cache, cache_file, cache_id, indiv_data, num_runs, g, fitness_with_var); // Added 6/18/2021
            node_increment_gen(indiv_data);
            //printf("Fitness=%lf\n", fitness_values[k]);
        }
        select_elites(pop_size, num_elites, fitness_values, current_gen_id, elite_indx, elite_id);
        // print out and export the ID and fitness information
        
        evolution_cache_gen(cache, main_folder, \
                        current_generation, fitness_values, current_gen_id, \
                        track_fitness, \
                        pop_size, num_gens, g, offset, ot);

        vis_print_gen(vis, true, current_generation, g, pop_size);
        printf("-------------------------------- End of Generation %d --------------------------------\n\n", g + 1);
        log_redo_basic(main_folder, file, cache, cache_id, track_fitness[g + offset], num_runs, fitness_with_var, g, levels, num_levels);
        //bool terminate = check_termination(track_fitness[g + offset], &lowest, &stale_counter, stale_limit);
        bool terminate = false;
        if (terminate) {
            return evolution_clean_up(num_elites, current_generation, pop_size, \
                                        vis, main_folder, file, cache_id, cache, \
                                        all_indiv, num_runs, max_id, g, \
                                        ot, fitness_values, current_gen_id);
        }
    }
    //TODO: FIX THIS
    /*double temp_track[num_levels];
    fitness_redo_basic(main_folder, file, cache, temp_track, cache_id, num_runs, fitness_with_var, levels, num_levels);
    char test_compare[200];*/

    return evolution_clean_up(num_elites, current_generation, pop_size, \
                                vis, main_folder, file, cache_id, cache, \
                                all_indiv, num_runs, max_id, num_gens, \
                                ot, fitness_values, current_gen_id);
}
