#include "indivdata.h"

DataNode* node_new_allele(node_str* seq, int id) {
    DataNode* d = malloc(sizeof(DataNode));
    d->seq = osaka_copylist(seq);
    d->seq_len = osaka_listlength(seq);
    d->seq_id = id;
    d->fitness = -1;
    d->num_eval = 0;
    d->tot_gen = 0;
    d->capacity = 2;
    d->time_arrs = (double**) malloc(sizeof(double*) * d->capacity);
    d->success_cts = (int*) malloc(sizeof(int) * d->capacity);
    d->avg_time = (double*) malloc(sizeof(double) * d->capacity);
    d->var = (double*) malloc(sizeof(double) * d->capacity);
    d->gens = (int*) malloc(sizeof(int) * d->capacity);
    //printf("created new allele, ID=%d\n", d->seq_id);
    return d;
}

double node_record_data(DataNode* d, node_str* sequence, double* all_runtime, double avg_runtime, int success_runs, int gen, bool fitness_with_var) {
    //printf("inside node_record_data\n");
    //visualization_print_individual_concise_details(sequence);
    //printf("\n");
    if (d->seq == NULL) {
        printf("ATTENTION: (indivdata.c:node_record_data()) d->seq == NULL\n");
        exit(0);
    }
    //printf("after trying to access d->seq\n");
    //printf("d->num_eval=%d, d->capacity=%d\n", d->num_eval, d->capacity);
    if(!osaka_compare(d->seq, sequence)){
        printf("\n\nATTENTION: RECORD DATA SEQEUNCES DON'T MATCH (node_record_data)\n");
        printf("d->seq (id=%d): \n", d->seq_id);
        visualization_print_individual_concise_details(d->seq);
        printf("\nsequence evaluated:\n");
        visualization_print_individual_concise_details(sequence);
        printf("\n\n\n\n");
    }
    //printf("after osaka_compare\n");
    d->num_eval += 1;
    node_check_overflow(d);
    d->time_arrs[d->num_eval-1] = malloc(sizeof(double) * success_runs);
    for (int i = 0; i < success_runs; i++) {
        d->time_arrs[d->num_eval-1][i] = all_runtime[i];
    }
    d->avg_time[d->num_eval-1] = avg_runtime;
    d->success_cts[d->num_eval-1] = success_runs;
    if (fitness_with_var) {
        d->var[d->num_eval-1] = calc_var(all_runtime, avg_runtime, success_runs);
    } else {
        d->var[d->num_eval-1] = -1;
    }
    d->gens[d->num_eval-1] = gen+1;
    return node_update_fitness(d, fitness_with_var);
}

void node_check_overflow(DataNode* d) {
    if (d->num_eval >= d->capacity) {
        d->capacity *= 2;
        d->time_arrs = realloc(d->time_arrs, sizeof(double*) * d->capacity);
        d->success_cts = realloc(d->success_cts, sizeof(int) * d->capacity);
        d->avg_time = realloc(d->avg_time, sizeof(double) * d->capacity);
        d->var = realloc(d->var, sizeof(double) * d->capacity);
        d->gens = realloc(d->gens, sizeof(int) * d->capacity);
    }
}

double node_update_fitness(DataNode* d, bool fitness_with_var) {
    //printf("inside node_update_fitness, d->num_eval=%d\n", d->num_eval);
    int total_run = 0;
    double total_time = 0.0;
    double total_var = 0.0;
    double new_fitness = 0.0;
    for (uint32_t i = 0; i < d->num_eval; i++) {
        //printf("d->success_cts[%d]=%d, d->avg_time[%d]=%lf, d->var[%d]=%lf\n", i, d->success_cts[i], i, d->avg_time[i], i, d->var[i]);
        if (d->avg_time[i] != UINT32_MAX) {
            total_run += d->success_cts[i];
            total_time += d->avg_time[i] * d->success_cts[i];
            total_var += d->var[i];
            //printf("total_run=%d, total_time=%lf, total_var=%lf\n", total_run, total_time, total_var);
        }   
    }
    //d->fitness = total_time/total_run + total_var/d->num_eval;
    if (fitness_with_var) {
        //d->fitness = total_run==0 ? UINT32_MAX : total_time/total_run + total_var/d->num_eval;
        new_fitness = total_run==0 ? UINT32_MAX : total_time/total_run + total_var/d->num_eval;
    } else {
        //d->fitness = total_run==0 ? UINT32_MAX : total_time/total_run;
        new_fitness = total_run==0 ? UINT32_MAX : total_time/total_run;
    }
    //printf("ID: %d, old fitness: %lf, new fitness: %lf, ", d->seq_id, d->fitness, new_fitness);
    /*if (d->fitness < 0 || new_fitness < d->fitness) {
        d->fitness = new_fitness;
    }*/
    d->fitness = new_fitness;
    //printf("return fitness: %lf\n", d->fitness);
    return d->fitness;
}

void node_add_group(node_str** gen, int* current_gen_id, uint32_t group_size, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr) {
    //printf("\ninside node_add_group, max_id=%d\n", *max_id_ptr);
    for (int g = 0; g < group_size; g++) {
        int new_allele_id = node_add(gen[g], max_id_ptr, hash_cap_ptr, all_indiv_ptr);
        current_gen_id[g] = new_allele_id;
    }
}

int node_add(node_str* sequence, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr) {
    //printf("before node_find,  max_id=%d\n", *max_id_ptr);
    int new_allele_id = node_find(*all_indiv_ptr, *max_id_ptr, sequence);
    if (new_allele_id < 0) {
        new_allele_id = (*max_id_ptr)++;
        node_add_indiv(sequence, new_allele_id, hash_cap_ptr, all_indiv_ptr);
        //printf("node added to all_indiv at position %d\n", new_allele_id);
    }
    return new_allele_id;
}

int node_find(DataNode** all_indiv, int max_id, node_str* sequence) {
    for (int i = 0; i < max_id; i++) {
        if(all_indiv[i] == NULL) {
            printf("WARNING: all_indiv[%d]==NULL\n", i);
        }
        else if(all_indiv[i]->seq == NULL) {
            printf("WARNING: all_indiv[%d]->seq==NULL\n", i);
        }
        if (node_match(all_indiv[i], sequence)) {
            /*printf("\n\nFound match at individual #%d\n", i);
            printf("\nall_indiv[%d]->seq: (max_id = %d)\n", i, max_id);
            visualization_print_individual_concise_details(all_indiv[i]->seq);
            printf("\nsequence:\n");
            visualization_print_individual_concise_details(sequence);
            printf("\n\n");*/
            return i;
        }
    }
    return -1;
}

bool node_match(DataNode* d, node_str* sequence) {
    return d->seq? osaka_compare(d->seq, sequence) : false;
}

void node_add_indiv(node_str* sequence, int new_indiv_id, int* hash_cap_ptr, DataNode*** all_indiv_ptr) {
    DataNode* new_indiv = node_new_allele(sequence, new_indiv_id);
    node_check_overflow_array(new_indiv_id, hash_cap_ptr, all_indiv_ptr);
    (*all_indiv_ptr)[new_indiv_id] = new_indiv;
}

void node_check_overflow_array(int new_indiv_id, int* hash_cap_ptr, DataNode*** all_indiv_ptr) {
    if (new_indiv_id >= *hash_cap_ptr) {
        DataNode** temp = realloc(*all_indiv_ptr, 2 * (*hash_cap_ptr) * sizeof(DataNode*));
        if (!temp) {
            printf("reallocation failed inside generate_new_generation, exit\n");
        } else {
            *all_indiv_ptr = temp;
            memset(*all_indiv_ptr + *hash_cap_ptr, 0, *hash_cap_ptr);
        }
        (*hash_cap_ptr) *=2;
    }
}

bool node_reeval_by_chance(DataNode* d, int gen) {
    //return true;
    if (d->num_eval == 0) {
        return true;
    }
    for (int i = 0; i < d->num_eval; i++) {
        if (gen+1 == d->gens[i]) {
            return false;
        }
    }
    int random_number = rand() % 100;
    return random_number < 25;
}

void node_increment_gen(DataNode* d) {
    d->tot_gen += 1;
}

void node_log(char* indiv_info_dir, char* file, DataNode* d) {
    FILE* file_ptr = fopen(file, "a");
    for (int g = 0; g < d->num_eval; g++) {
        fprintf(file_ptr, "%d,%d,%d,%d,%lf,%lf,%d,", d->seq_id, d->num_eval, d->tot_gen, d->gens[g], d->avg_time[g], d->var[g], d->success_cts[g]);
        double* time_arr = d->time_arrs[g];
        for (int r = 0; r < d->success_cts[g]; r++) {
            fprintf(file_ptr, "%lf%s", d->time_arrs[g][r],(r<(d->success_cts[g]-1)?",":"\n"));
        }
        char cache_file[10000];
        strcpy(cache_file, indiv_info_dir);
        char id_num[100];
        sprintf(id_num, "/individual_%d.txt", d->seq_id);
        strcat(cache_file, id_num);
        node_cache_llvm_pass(cache_file, d->seq, d->fitness, d->seq_id);
    }
    fclose(file_ptr);
}
    
void node_cache_llvm_pass(char* file_name, node_str* indiv, double fitness, int unique_id) {
    char string[30000];
    char fitness_num[100];
    char input_str[10000];

    strcpy(string, "");
    sprintf(string, "Description file for Individual (unique ID: %d)\n\nIndividual Size: %d\n\nBelow are the passes in this individual, in order:\n\n", unique_id, osaka_listlength(indiv));

    sprintf(fitness_num, "%f", fitness);
    strcpy(input_str, "");

    while (NEXT(indiv) != NULL) {
        char desc[60];
        strcpy(desc, "");
        osaka_describenode(desc, indiv);
        strcat(string, desc);
        strcat(string, "\n");
        indiv = NEXT(indiv);
    }

    char desc[60];
    strcpy(desc, "");
    osaka_describenode(desc, indiv);
    strcat(string, desc);
    strcat(string, "\n\nThe fitness of the individual is the time it takes to complete the testing script provided in seconds after the specified optimization passes are applied. Lower fitness is better.\n\nFitness of this individual: ");
    strcat(string, fitness_num);
    strcat(string, " sec");
    
    FILE* file_ptr = fopen(file_name, "w+");
    fputs(string, file_ptr);
    //fclose(input);
    //fclose(output);
    fclose(file_ptr);
}

void node_cache_best(bool cache, char* main_folder, uint32_t gen, uint32_t pop_size, node_str** current_gen, double* fitness_values, int* current_gen_id, double* track_fitness) {
    if (!cache) {
        return;
    }
    // add additional file for best individual in the generation
    char best_file[300];
    strcpy(best_file, main_folder);
    strcat(best_file, "/best/best");

    char temp[50];
    strcpy(temp, "");
    if (gen == -1) {
        sprintf(temp, "_initial.txt");
    } else {
        sprintf(temp, "_generation_%d.txt", gen+1);
    }
    strcat(best_file, temp);

    // find best fitness
    uint32_t winner = 0;
    double winner_fitness = fitness_values[0];
    for (uint32_t j = 1; j < pop_size; j++) {
        if (fitness_values[j] < winner_fitness) {
            winner = j;
            winner_fitness = fitness_values[j];
        }
    }
    int winner_id = current_gen_id[winner];
    node_str* winner_seq = current_gen[winner];

    track_fitness[gen + 8] = winner_fitness;
    //printf("saved to track_fitness\n");
    node_cache_llvm_pass(best_file, winner_seq, winner_fitness, winner_id);
}

void node_print(DataNode* d, int id) {
    for (int g = 0; g < d->num_eval; g++) {
        printf("%d,%d,%d,%lf,%lf,%d,", id, d->tot_gen, d->gens[g], d->avg_time[g], d->var[g], d->success_cts[g]);
        //double* time_arr = d->time_arrs[g];
        for (int r = 0; r < d->success_cts[g]; r++) {
            printf("%lf%s", d->time_arrs[g][r],(r<(d->success_cts[g]-1)?",":"\n"));
        }
    }

}

void free_node(DataNode* d) {
    for (int i = 0; i < d->num_eval; i++) {
        free(d->time_arrs[i]);
    }
    generate_free_individual(d->seq);
    free(d->time_arrs);
    free(d->success_cts);
    free(d->avg_time);
    free(d->var);
    free(d->gens);
    free(d);
}

void free_all_nodes(DataNode** all_indiv, int max_id) {
    for (int i = 0; i < max_id; i++) {
        free_node(all_indiv[i]);
        //printf("Freed node #%d\n", i);
    }
    //printf("Freed all nodes\n");
}