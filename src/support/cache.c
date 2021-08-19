#include "cache.h"

void cache_file_name(bool cache, char* main_folder, char* cache_file, int gen, int indiv_idx) {
    if (cache) {
        //printf("Creating cache file for individual %d\n", k+1);
        char directory_name[300];
        char generation_name[100];
        char individual_num[100];
        strcpy(generation_name, "");
        if (gen == -1) {
            strcat(generation_name, "/initial_fitness");
        } else {
            sprintf(generation_name, "/generation_%d", gen+1);
        }
        strcpy(directory_name, "");
        strcat(directory_name, main_folder);
        strcat(directory_name, generation_name);
        //printf("directory name: %s\n", directory_name);
        sprintf(individual_num, "%d", indiv_idx+1);
        strcpy(cache_file, directory_name);
        strcat(cache_file, "/individual");
        strcat(cache_file, individual_num);
        strcat(cache_file, ".txt");
    }
}

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

void cache_create_new_run_folder(bool cache, char* main_folder, const char *cache_id) {   // Added 6/21/2021
//void evolution_create_new_run_folder(char* main_folder) { 
    if (!cache) {
        return;
    }
    //printf("evolution.c:155 evolution_create_new_run_folder, cache_id = %s\n", cache_id);
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
    strcat(main_folder, "_");  // Added 6/21/2021
    strcat(main_folder, cache_id); // Added 6/21/2021

    // create and run the command for making the new directory
    char create_dir[200];
    strcpy(create_dir, "mkdir ");
    strcat(create_dir, main_folder);
    system(create_dir);

    printf("Created main folder: %s\n", main_folder);

}

void cache_params(bool cache, char* main_folder, uint32_t num_gens, uint32_t pop_size, uint32_t cross_perc, uint32_t mut_perc, uint32_t elite_perc, uint32_t tourn_size) {
    if (!cache) {
        return;
    }
    char param_file[300];
    strcpy(param_file, main_folder);
    strcat(param_file, "/parameters.txt");
    FILE* param_file_ptr = fopen(param_file, "w");
    fprintf(param_file_ptr, "num_generations: %d\nnum_population_size: %d\npercent_crossover: %d\npercent_mutation: %d\npercent_elite: %d\ntournament_size: %d\n", num_gens, pop_size, cross_perc, mut_perc, elite_perc, tourn_size);
    fclose(param_file_ptr);
    printf("Saved params to cache\n");
}

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

void cache_create_new_gen_folder(bool cache, char* main_folder, uint32_t gen) {
    if (!cache) {
        return;
    }

    char new_directory_name[300];
    char new_directory[300];
    char generation_name[50];

    strcpy(generation_name, "");
    if (gen == -1) {
        strcat(generation_name, "/initial_fitness");
    } else {
        sprintf(generation_name, "/generation_%d", gen+1);
    }

    strcpy(new_directory_name, main_folder);
    strcat(new_directory_name, generation_name);

    cache_create_new_folder(new_directory_name);

}

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

void cache_create_new_folder(char* new_directory_name) {

    char new_directory[300];

    // we are only making the directory, not adding anything to it
    strcpy(new_directory, "mkdir ");
    strcat(new_directory, new_directory_name);

    system(new_directory);

}

void cache_create_best_indiv_folder(bool cache, char* main_folder) {
    if (!cache) {
        return;
    }

    char new_directory_name[300];
    char new_directory[300];
    char generation_name[50];

    strcpy(new_directory_name, main_folder);
    strcat(new_directory_name, "/best");

    cache_create_new_folder(new_directory_name);

}

void cache_create_baseline_folder(bool cache, char* main_folder) {
    if (!cache) {
        return;
    }

    char new_directory_name[300];
    char new_directory[300];
    char generation_name[50];

    strcpy(new_directory_name, main_folder);
    strcat(new_directory_name, "/baseline");

    cache_create_new_folder(new_directory_name);

}