#ifndef EVOLUTION_INDIVDATA_H_
#define EVOLUTION_INDIVDATA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../osaka/osaka.h"
#include "../support/visualization.h"
#include "../support/utility.h"
#include "generation.h"
#include "optsequence.h"


typedef struct DataNode {
    struct node_str *seq;   //Osaka pass sequence
    uint32_t osaka_type;    //Osaka type
    int seq_len;            //Length of the Osaka structure
    int seq_id;             //Unique ID for the individual, starting at 0
    double fitness;         //Fitness for the individual
    int num_eval;           //Number of times that this pass sequence is being run / num_runs
    double** time_arrs;     //Runtime for every time the sequence is run, dimension: num_eval x num_runs(40)
    int* success_cts;       //Number of success_runs for each evaluation, dimension: num_eval x 1
    double* avg_time;       //Average runtime for each evaluation, dimension: num_eval x 1
    double* var;            //Variance over num_runs(40) for each evaluation, dimension: num_eval x 1
    int* gens;              //Generations that it's in, -1 if individual is produced but not selected
    int tot_gen;            //Total number of generations this individual appeared in
    int capacity;           //Counter variable for allocating space for arrays
} DataNode;

DataNode* node_new_allele(node_str* seq, int id, osaka_object_typ ot);
double node_record_data(DataNode* d, node_str* sequence, double* all_runtime, double avg_runtime, int success_runs, int gen, bool fitness_with_var);
void node_check_overflow(DataNode* d);
bool node_match(DataNode* d, node_str* sequence);
int node_find(DataNode** all_indiv, int max_id, node_str* sequence);
void node_increment_gen(DataNode* d);
void node_log(char* main_folder, char* file, DataNode* d);
void node_print(DataNode* d, int id);
void node_add_new_generation(node_str** gen, uint32_t population_size, int* gen_id, int* max_id, int* hash_cap, DataNode*** all_indiv_ptr, osaka_object_typ ot);
void node_add_group(node_str** gen, int* current_gen_id, uint32_t group_size, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr, osaka_object_typ ot);
int node_add(node_str* sequence, int* max_id_ptr, int* hash_cap_ptr, DataNode*** all_indiv_ptr, osaka_object_typ ot);
void node_add_indiv(node_str* sequence, int new_indiv_id, int* hash_cap_ptr, DataNode*** all_indiv_ptr, osaka_object_typ ot);
int node_find_by_id(DataNode*** all_indiv_ptr, int* hash_cap_ptr, node_str* sequence, int new_indiv_id);
void node_check_overflow_array(int new_indiv_id, int* hash_cap_ptr, DataNode*** all_indiv_ptr);
double node_calculate_var(double* all_runtime, double avg_runtime, int success_runs);
bool node_reeval_by_chance(DataNode* d, int gen);
double node_update_fitness(DataNode* d, bool fitness_with_var);
void node_cache_llvm_pass(char* file_name, node_str* indiv, double fitness, int unique_id);
void node_cache_best(bool cache, char* main_folder, uint32_t gen, uint32_t pop_size, node_str** current_gen, double* fitness_values, int* current_gen_id, double* track_fitness);
void free_node(DataNode* d);
void free_all_nodes(DataNode** all_indiv, int max_id);

#endif /* EVOLUTION_INDIVDATA_H_ */