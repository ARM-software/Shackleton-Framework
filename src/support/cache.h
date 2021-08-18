#ifndef SUPPORT_CACHE_H_
#define SUPPORT_CACHE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../osaka/osaka.h"

void cache_file_name(bool cache, char* main_folder, char* cache_file, int gen, int indiv_idx);
void cache_create_new_run_folder(bool cache, char* main_folder, const char *cache_id);
void cache_params(bool cache, char* main_folder, uint32_t num_gens, uint32_t pop_size, uint32_t cross_perc, uint32_t mut_perc, uint32_t elite_perc, uint32_t tourn_size);
void cache_create_new_gen_folder(bool cache, char* main_folder, uint32_t gen);
void cache_create_new_folder(char* new_directory_name);
void cache_create_best_indiv_folder(bool cache, char* main_folder);
void cache_create_baseline_folder(bool cache, char* main_folder);

#endif /* SUPPORT_CACHE_H_ */