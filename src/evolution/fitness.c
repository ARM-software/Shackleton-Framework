/*
 ============================================================================
 Name        : fitness.c
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

/*
 * IMPORT
 */

#include "fitness.h"
#define BILLION  1000000000L;
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

void fitness_pre_cache_simple(char* folder, bool cache) {

    // do nothing, default for now
}

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

void fitness_cache_simple(double fitness, node_str* indiv, char* cache_file) {

    // do nothing, default for now

}

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

uint32_t fitness_simple(node_str* indiv, bool vis) {
    
    return 100 * (rand() / (RAND_MAX + 1.0)); 

}

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

void fitness_pre_cache_assembler(char* folder, bool cache) {

    // do nothing, default for now

}

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

void fitness_cache_assembler(double fitness, node_str* indiv, char* cache_file) {

    // do nothing, default for now

}

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

uint32_t fitness_assembler(node_str* indiv, bool vis) {

    return 100 * (rand() / (RAND_MAX + 1.0)); 

}

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

void fitness_pre_cache_osaka_string(char* folder, bool cache) {

    // do nothing, default for now

}

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

void fitness_cache_osaka_string(double fitness, node_str* indiv, char* cache_file) {

    // do nothing, default for now

}

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

uint32_t fitness_osaka_string(node_str* indiv, bool vis) {

    return 100 * (rand() / (RAND_MAX + 1.0)); 

}

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

void fitness_pre_cache_llvm_pass(char* folder, char* test_file, char** src_files, uint32_t num_src_files, bool cache, double* track_fitness, const char *cache_id, uint32_t num_runs, bool fitness_with_var, const char** levels, const int num_levels) { //added 6/8/2021
    char build_command[20000];
    strcpy(build_command, "");
    FILE *track_fitness_file_ptr;
    double tol = 0.95;

    llvm_form_build_ll_command(src_files, num_src_files, test_file, build_command, cache_id);
    
    llvm_run_command(build_command);

    if (!cache) {
        return;
    }

    cache_create_baseline_folder(cache, folder);
    struct timeval start, end; 
    //clock_t start, end;
    //struct timespec start, end;
    
    uint32_t result = 0;
    uint32_t success_runs = 0;
    int counter = 0;

    double total_time = 0.0;
    double time_taken = 0.0;
    double fitness = 0.0;

    char test_file_name[100];
    char test_file_name_no_path[100];
    char junk_dir[200];
    char opt_file[200];
    char base_file[200];

    char opt_command[1000];
    char bc_command[1000];
    char run_command[1000];

    strcpy(test_file_name, test_file);
    char* p = strchr(test_file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(test_file_name_no_path, "");
    char *t = strrchr(test_file_name, '/'); 
    if (!t) {
        strcpy(test_file_name_no_path, test_file_name);
    } else strcpy(test_file_name_no_path, t+1);

    strcpy(junk_dir, "src/files/llvm/junk_output/");
    strcpy(base_file, junk_dir);
    strcat(base_file, test_file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, cache_id);

    for (int i = 0; i < num_levels; i++) {
        total_time = 0.0;
        time_taken = 0.0;
        fitness = 0.0;
        if (strlen(levels[i]) == 0) {
            strcpy(opt_command, "");

            strcpy(bc_command, "llvm-as ");
            strcat(bc_command, base_file);
            strcat(bc_command, "_linked");
            strcat(bc_command, ".ll");

            strcpy(run_command, "lli ");
            strcat(run_command, base_file);
            strcat(run_command, "_linked");
            strcat(run_command, ".bc");
        }
        else {
            strcpy(opt_file, "");
            strcat(opt_file, base_file);
            strcat(opt_file, "_opt_");
            strcat(opt_file, levels[i]);

            strcpy(opt_command, "");
            strcat(opt_command, "opt -");
            strcat(opt_command, levels[i]);
            strcat(opt_command, " ");
            strcat(opt_command, base_file);
            strcat(opt_command, "_linked.ll -S -o ");
            strcat(opt_command, opt_file);
            strcat(opt_command, ".ll");

            strcpy(bc_command, "");
            strcat(bc_command, "llvm-as ");
            strcat(bc_command, opt_file);
            strcat(bc_command, ".ll");

            strcpy(run_command, "");
            strcat(run_command, "lli ");
            strcat(run_command, opt_file);
            strcat(run_command, ".bc");
        }
        
        /*printf("\n--------------------LLVM opt level: %s, ALL COMMANDS GENERATED---------------------\n", strlen(levels[i])==0?"no_opt":levels[i]);
        printf("opt_command: %s\n", opt_command);
        printf("bc_command: %s\n", bc_command);
        printf("run_command: %s\n", run_command);*/
        
        llvm_run_command(opt_command);
        llvm_run_command(bc_command);

        double all_runtime[num_runs]; //Added 7/7/2021
        success_runs = 0;
        time_taken = 0.0;
        total_time = 0.0;
        counter = 0;

        for (uint32_t runs = 0; runs < num_runs; runs++) {

            gettimeofday(&start, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            result = llvm_run_command(run_command);
            gettimeofday(&end, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            time_taken = (end.tv_sec - start.tv_sec) * 1e6;
            time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
            //time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) / BILLION;
            //time_taken = (double)( end.tv_sec - start.tv_sec )*1000000.0 + ( end.tv_nsec - start.tv_nsec ) / 1000.0;
            //printf("line 728 time_taken=%lf, start=%lf, end=%lf\n", time_taken, (double)start.tv_sec, (double)end.tv_sec);
            //printf("line 728 time_taken=%f, start=%lf, end=%lf\n", time_taken, (double)start, (double)end);

            //printf("LLVM opt level: %s, run #%d, time taken: %lf\n", strlen(levels[i])==0?"no_opt":levels[i], runs+1, time_taken);
            if (result == 0) {
                success_runs++;
                total_time = total_time + time_taken;
                all_runtime[counter++] = time_taken;
                //printf("Time taken: %lf sec.\n", time_taken);
            }
            else {
                //printf("Run exited with code %d (time taken: %lf sec.)\n", result, time_taken);
            }
        }
        // Added 6/21/2021
        if (success_runs < num_runs * tol) {
            //printf("success_runs < num_runs * %f, fitness set to max.\n", tol);
            time_taken = UINT32_MAX;
        } else {
            time_taken = total_time / success_runs;
        }
        //time_taken = total_time / success_runs;
        if (fitness_with_var) {
            fitness = time_taken + calc_var(all_runtime, time_taken, success_runs);
        } else {
            fitness = time_taken;
        }
        //printf("LLVM opt level: %s, average time=%lf over %d success runs, fitness=%lf\n", strlen(levels[i])==0?"no_opt":levels[i], time_taken, success_runs, fitness);
        track_fitness[i] = fitness;  //Added 6/8/2021
        /*for (int k = 0; k <= i; k++) {
            printf("%s%lf%s", k==0?"track_fitness=[":"", track_fitness[k], k==i?"]\n":",");
        }*/

        fitness_pre_cache_log_to_summary(i, folder, levels, num_levels, fitness);


    }
    return;
}

void fitness_pre_cache_log_to_summary(int level_ind, char* folder, const char** levels, const int num_levels, double fitness) {
    // record precache information to /main_folder/track_fitness.csv file
    char track_fitness_file[300];
    strcpy(track_fitness_file, folder);
    strcat(track_fitness_file, "/track_fitness.csv");
    FILE* track_fitness_file_ptr = fopen(track_fitness_file, "a");
    if (level_ind == 0) {
        fprintf(track_fitness_file_ptr, "no_opt,");
        for (int l = 1; l < num_levels; l++) {
            fprintf(track_fitness_file_ptr, "%s,", levels[l]);
        }
        fprintf(track_fitness_file_ptr, "initial,gen1,gen2,gen3\n");
    }
    fprintf(track_fitness_file_ptr, "%lf,", fitness);
    fclose(track_fitness_file_ptr);

    // record precache information to /main_folder/track_fitness.csv file
    char test_compare_file[300];
    strcpy(test_compare_file, folder);
    strcat(test_compare_file, "/test_compare.csv");
    FILE* test_compare_ptr = fopen(test_compare_file, "a+");
    if (level_ind == 0) {
        fprintf(test_compare_ptr, "gen, no_opt,");
        for (int l = 1; l < num_levels; l++) {
            fprintf(test_compare_ptr, "%s,", levels[l]);
        }
        fprintf(test_compare_ptr, "shackleton\n0,");
    }
    fprintf(test_compare_ptr, "%lf,", fitness);
    fclose(test_compare_ptr);

    // write each baseline optimization level to its own file inside /main_folder/baseline folder
    char out_file[300];
    char out_file_str[5000];
    char time_str[50];
    strcpy(out_file, folder);
    strcat(out_file, "/baseline");
    if (level_ind == 0) {
        strcat(out_file, "/original_no_optimization.txt");
    } else {
        strcat(out_file, "/default_opt_");
        strcat(out_file, levels[level_ind]);
        strcat(out_file, ".txt");
    }
    strcpy(out_file_str, "");
    sprintf(out_file_str, "Level of default LLVM optimization is: %s\n\nThe fitness of the individual is the time it takes to complete the testing script provided in seconds. Lower fitness is better.\n\nFitness of this individual: ", strlen(levels[level_ind])==0?"no optimization":levels[level_ind]);
    sprintf(time_str, "%f", fitness);
    strcat(out_file_str, time_str);
    strcat(out_file_str, " sec");

    FILE* out_file_ptr = fopen(out_file, "w");
    fputs(out_file_str, out_file_ptr);
    fclose(out_file_ptr);
}


void fitness_redo_basic(char* folder, char* test_file, bool cache, double* track_fitness, const char *cache_id, uint32_t num_runs, bool fitness_with_var, const char** levels, const int num_levels) {
    if (!cache) {
        return;
    }

    struct timeval start, end; 
    //clock_t start, end;
    //struct timespec start, end;

    uint32_t result = 0;
    uint32_t success_runs = 0;
    int counter = 0;
    double total_time = 0.0;
    double time_taken = 0.0;
    double fitness = 0.0;
    double tol = 0.95;

    char test_file_name[100];
    char test_file_name_no_path[100];
    char junk_dir[200];
    char opt_file[200];
    char base_file[200];

    char opt_command[1000];
    char bc_command[1000];
    char run_command[1000];

    strcpy(test_file_name, test_file);
    char* p = strchr(test_file_name, '.');
    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(test_file_name_no_path, "");
    char *t = strrchr(test_file_name, '/'); 
    if (!t) {
        strcpy(test_file_name_no_path, test_file_name);
    } else strcpy(test_file_name_no_path, t+1);

    strcpy(junk_dir, "src/files/llvm/junk_output/");
    strcpy(base_file, junk_dir);
    strcat(base_file, test_file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, cache_id);

    for (int i = 0; i < num_levels; i++) {
        total_time = 0.0;
        time_taken = 0.0;
        fitness = 0.0;
        if (strlen(levels[i]) == 0) {
            strcpy(opt_command, "");

            strcpy(bc_command, "llvm-as ");
            strcat(bc_command, base_file);
            strcat(bc_command, "_linked");
            strcat(bc_command, ".ll");

            strcpy(run_command, "lli ");
            strcat(run_command, base_file);
            strcat(run_command, "_linked");
            strcat(run_command, ".bc");
        }
        else {
            strcpy(opt_file, "");
            strcat(opt_file, base_file);
            strcat(opt_file, "_opt_");
            strcat(opt_file, levels[i]);

            strcpy(opt_command, "");
            strcat(opt_command, "opt -");
            strcat(opt_command, levels[i]);
            strcat(opt_command, " ");
            strcat(opt_command, base_file);
            strcat(opt_command, "_linked.ll -S -o ");
            strcat(opt_command, opt_file);
            strcat(opt_command, ".ll");

            strcpy(bc_command, "");
            strcat(bc_command, "llvm-as ");
            strcat(bc_command, opt_file);
            strcat(bc_command, ".ll");

            strcpy(run_command, "");
            strcat(run_command, "lli ");
            strcat(run_command, opt_file);
            strcat(run_command, ".bc");
        }
        
        //printf("\n--------------------LLVM opt level: %s, ALL COMMANDS GENERATED---------------------\n", strlen(levels[i])==0?"no_opt":levels[i]);
        //printf("opt_command: %s\n", opt_command);
        //printf("bc_command: %s\n", bc_command);
        //printf("run_command: %s\n", run_command);
        
        llvm_run_command(opt_command);
        llvm_run_command(bc_command);

        double all_runtime[num_runs]; //Added 7/7/2021
        success_runs = 0;
        time_taken = 0.0;
        total_time = 0.0;
        counter = 0;

        for (uint32_t runs = 0; runs < num_runs; runs++) {

            gettimeofday(&start, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            result = llvm_run_command(run_command);
            gettimeofday(&end, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            time_taken = (end.tv_sec - start.tv_sec) * 1e6;
            time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
            //time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) / BILLION;
            //time_taken = (double)( end.tv_sec - start.tv_sec )*1000000.0 + ( end.tv_nsec - start.tv_nsec ) / 1000.0;

            //printf("line 735 time_taken=%lf, start=%lf, end=%lf\n", time_taken, (double)start.tv_sec, (double)end.tv_sec);
            //printf("line 728 time_taken=%f, start=%lf, end=%lf\n", time_taken, (double)start, (double)end);
            //printf("LLVM opt level: %s, run #%d, time taken: %lf\n", strlen(levels[i])==0?"no_opt":levels[i], runs+1, time_taken);
            if (result == 0) {
                success_runs++;
                total_time = total_time + time_taken;
                all_runtime[counter++] = time_taken;
            }
        }
        if (success_runs < num_runs * tol) {
            //printf("success_runs < num_runs * %f, fitness set to max.\n", tol);
            time_taken = UINT32_MAX;
        } else {
            time_taken = total_time / success_runs;
        }
        //time_taken = total_time / success_runs;
        if (fitness_with_var) {
            fitness = time_taken + calc_var(all_runtime, time_taken, success_runs);
        } else {
            fitness = time_taken;
        }
        printf("LLVM opt level: %s, average time=%lf over %d success runs, fitness=%lf\n", strlen(levels[i])==0?"no_opt":levels[i], time_taken, success_runs, fitness);
        track_fitness[i] = fitness;  //Added 6/8/2021
    }
    return;
}

/*
 * NAME
 *
 *   fitness_cache_llvm_pass
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
 *     fitness_cache_llvm_pass(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_llvm_pass(double fitness, node_str* indiv, char* cache_file) {
    //printf("fitness.c:682, fitness_cache, cache_file: %s\n", cache_file);
    char string[30000];
    char fitness_num[100];
    char input_str[10000];
    char output_str[10000];

    strcpy(string, "Description file for Individual 1\n\nHere are the passes in this individual, in order:\n\n");
    sprintf(fitness_num, "%f", fitness);
    strcpy(input_str, "");
    strcpy(output_str, "");

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
    strcat(string, " sec\n\n");

    int seq_len = 0;
    if (indiv->objtype == 5) {
        char* opt_seq_str = gen_seq_str(indiv, &seq_len);
        strcat(string, opt_seq_str);
    }

    //printf("fitness.c:737, fitness_cache, cache_file: %s\n", cache_file);

    FILE* file_ptr = fopen(cache_file, "w+");
    fputs(string, file_ptr);
    //fclose(input);
    //fclose(output);
    fclose(file_ptr);
    //printf("Done writing to cache file.\n");

    //free(line);
    //printf("fitness.c:747, fitness_cache, cache_file: %s\n", cache_file);
}

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

double fitness_llvm_pass(node_str* indiv, char* file, char** src_files, uint32_t num_src_files, bool vis, bool cache, char* cache_file, const char *cache_id, DataNode* indiv_data, uint32_t num_runs, int gen, bool fitness_with_var) {
    
    double fitness;
    fitness = indiv_data->fitness;
    if (!node_reeval_by_chance(indiv_data, gen)) {
        //printf("----skipped re-evaluation for individual id=%d\n", indiv_data->seq_id);
        return indiv_data->fitness;
    }
    uint32_t success_runs = 0; //Added 6/21/2021

    char file_name[300];
    char base_name[300];
    char input_file[300];
    char output_file[300];
    char base_file[300];

    struct timeval start, end; 
    //clock_t start, end;
    //struct timespec start, end;
    
    uint32_t result = 0;
    double tol = 0.95;

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    char file_name_no_path[100];
    strcpy(file_name_no_path, "");
    char *t = strrchr(file_name, '/'); 
    if (!t) {
        strcpy(file_name_no_path, file_name);
    } else strcpy(file_name_no_path, t+1);

    strcpy(base_file, "");
    strcat(base_file, "src/files/llvm/junk_output/");
    strcat(base_file, file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, cache_id);

    strcpy(input_file, base_file);
    strcat(input_file, "_linked.ll");

    strcpy(output_file, base_file);
    strcat(output_file, "_shackleton.ll");

    if (vis) {
        printf("Calculating fitness of individual\n");
    }

    char opt_command[5000];
    char run_command[5000];
    strcpy(opt_command, "");
    strcpy(run_command, "");

    //printf("building opt command with input_file=%s, output_file=%s\n\n", input_file, output_file);
    //printf("input_file: %s\n", input_file);
    //printf("output_file: %s\n", output_file);
    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file, opt_command);
    llvm_form_exec_code_command_from_ll(output_file, run_command);
    
    //printf("\nShackleton opt command: %s\n", opt_command);
    //printf("run command: %s\n", run_command);

    llvm_run_command(opt_command);

    double total_time = 0.0;
    double time_taken = 0.0;
    double all_runtime[num_runs]; //Added 7/7/2021
    int counter = 0; //Added 7/7/2021

    for (uint32_t runs = 0; runs < num_runs; runs++) {

        //printf("\n-----------------------------------------------------------------------------\n");
        //printf("Shackleton optimization run %d\n\n", runs+1);

        gettimeofday(&start, NULL);
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        result = llvm_run_command(run_command);
        gettimeofday(&end, NULL);
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        //time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) / BILLION;
        //time_taken = (double)( end.tv_sec - start.tv_sec )*1000000.0 + ( end.tv_nsec - start.tv_nsec ) / 1000.0;

        //printf("line 962 time_taken=%lf, start=%lf, end=%lf\n", time_taken, (double)start.tv_sec, (double)end.tv_sec);
        //printf("line 952 time_taken=%f, start=%lf, end=%lf\n", time_taken, (double)start, (double)end);
        //printf("Shackleton opt run #%d, time taken: %lf\n", runs+1, time_taken);
        if (result == 0) {
            success_runs++;
            total_time += time_taken;
            //printf("Time taken in current run: %lf sec.\n", time_taken);
            all_runtime[counter++] = time_taken; //Added 7/7/2021
        }
        else {
            //printf("Run exited with code %d (time taken: %lf sec.)\n", result, time_taken);
        }
    }

    // Added 6/21/2021
    if (success_runs < num_runs * tol) {
        //printf("success_runs < num_runs*%f, fitness set to max.\n", tol);
        time_taken = UINT32_MAX;
    } else {
        time_taken = total_time / success_runs;
        //printf("average time taken: %lf\n", time_taken);
    }

    fitness = node_record_data(indiv_data, indiv, all_runtime, time_taken, success_runs, gen, fitness_with_var);
    //fitness = node_look_up_fitness(indiv_data, indiv, all_runtime, time_taken, success_runs);
    //printf("Average time: %lf over %d success runs, fitness=%lf\n", time_taken, success_runs, fitness);
    
    /*if (cache) {
        fitness_cache_llvm_pass(fitness, indiv, cache_file);
    }*/
    return fitness;

}

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

void fitness_pre_cache_binary_up_to_512(char* folder, bool cache) {

    // do nothing, default for now

}

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

void fitness_cache_binary_up_to_512(double fitness, node_str* indiv, char* cache_file) {

    // do nothing, default for now

}

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

uint32_t fitness_binary_up_to_512(node_str* indiv, bool vis) {

	return 100 * (rand() / (RAND_MAX + 1.0)); 

}

/*
 * NAME
 *
 *   fitness_pre_cache_gi_llvm_pass
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
 * if (object_type == GI_LLVM_PASS) {
 *     fitness_pre_cache_gi_llvm_pass(main_folder, test_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_pre_cache_gi_llvm_pass(char* folder, char* test_file, char** src_files, uint32_t num_src_files, bool cache, double* track_fitness, const char *cache_id, uint32_t num_runs, bool fitness_with_var, const char** levels, const int num_levels) { //added 6/8/2021
    char build_command[20000];
    strcpy(build_command, "");
    FILE *track_fitness_file_ptr;
    double tol = 0.95;

    llvm_form_build_ll_command(src_files, num_src_files, test_file, build_command, cache_id);
    
    llvm_run_command(build_command);

    if (!cache) {
        return;
    }

    cache_create_baseline_folder(cache, folder);
    struct timeval start, end;
    //clock_t start, end;
    //struct timespec start, end;

    uint32_t result = 0;
    uint32_t success_runs = 0;
    int counter = 0;

    double total_time = 0.0;
    double time_taken = 0.0;
    double fitness = 0.0;

    char test_file_name[100];
    char test_file_name_no_path[100];
    char junk_dir[200];
    char opt_file[200];
    char base_file[200];

    char opt_command[1000];
    char bc_command[1000];
    char run_command[1000];

    strcpy(test_file_name, test_file);
    char* p = strchr(test_file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(test_file_name_no_path, "");
    char *t = strrchr(test_file_name, '/'); 
    if (!t) {
        strcpy(test_file_name_no_path, test_file_name);
    } else strcpy(test_file_name_no_path, t+1);

    strcpy(junk_dir, "src/files/llvm/junk_output/");
    strcpy(base_file, junk_dir);
    strcat(base_file, test_file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, cache_id);

    for (int i = 0; i < num_levels; i++) {
        total_time = 0.0;
        time_taken = 0.0;
        fitness = 0.0;
        if (strlen(levels[i]) == 0) {
            strcpy(opt_command, "");

            strcpy(bc_command, "llvm-as ");
            strcat(bc_command, base_file);
            strcat(bc_command, "_linked");
            strcat(bc_command, ".ll");

            strcpy(run_command, "lli ");
            strcat(run_command, base_file);
            strcat(run_command, "_linked");
            strcat(run_command, ".bc");
        }
        else {
            strcpy(opt_file, "");
            strcat(opt_file, base_file);
            strcat(opt_file, "_opt_");
            strcat(opt_file, levels[i]);

            strcpy(opt_command, "");
            strcat(opt_command, "opt -");
            strcat(opt_command, levels[i]);
            strcat(opt_command, " ");
            strcat(opt_command, base_file);
            strcat(opt_command, "_linked.ll -S -o ");
            strcat(opt_command, opt_file);
            strcat(opt_command, ".ll");

            strcpy(bc_command, "");
            strcat(bc_command, "llvm-as ");
            strcat(bc_command, opt_file);
            strcat(bc_command, ".ll");

            strcpy(run_command, "");
            strcat(run_command, "lli ");
            strcat(run_command, opt_file);
            strcat(run_command, ".bc");
        }
        
        llvm_run_command(opt_command);
        llvm_run_command(bc_command);

        double all_runtime[num_runs]; //Added 7/7/2021
        success_runs = 0;
        time_taken = 0.0;
        total_time = 0.0;
        counter = 0;

        for (uint32_t runs = 0; runs < num_runs; runs++) {

            gettimeofday(&start, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            result = llvm_run_command(run_command);
            gettimeofday(&end, NULL);
            //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            //time_taken = (end.tv_sec - start.tv_sec);
            //time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
            //time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) / BILLION;
            //time_taken = (double)( end.tv_sec - start.tv_sec )*1000000.0 + ( end.tv_nsec - start.tv_nsec ) / 1000.0;
            time_taken = (end.tv_sec - start.tv_sec) * 1e6;
            time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

            //printf("line 1254 time_taken=%lf, start=%lf, end=%lf\n", time_taken, (double)start.tv_sec, (double)end.tv_sec);
            //printf("LLVM opt level: %s, run #%d, time taken: %lf\n", strlen(levels[i])==0?"no_opt":levels[i], runs+1, time_taken);
            if (result == 0) {
                success_runs++;
                total_time = total_time + time_taken;
                all_runtime[counter++] = time_taken;
                //printf("Time taken: %lf sec.\n", time_taken);
            }
            else {
                //printf("Run exited with code %d (time taken: %lf sec.)\n", result, time_taken);
            }
        }
        time_taken = total_time / success_runs;
        if (fitness_with_var) {
            fitness = time_taken + calc_var(all_runtime, time_taken, success_runs);
        } else {
            fitness = time_taken;
        }
        //printf("LLVM opt level: %s, average time=%lf over %d success runs, fitness=%lf\n", strlen(levels[i])==0?"no_opt":levels[i], time_taken, success_runs, fitness);
        track_fitness[i] = fitness;  //Added 6/8/2021
        /*for (int k = 0; k <= i; k++) {
            printf("%s%lf%s", k==0?"track_fitness=[":"", track_fitness[k], k==i?"]\n":",");
        }*/

        fitness_pre_cache_log_to_summary(i, folder, levels, num_levels, fitness);


    }
    return;
}

/*
 * NAME
 *
 *   fitness_cache_gi_llvm_pass
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
 *     fitness_cache_gi_llvm_pass(fit, indiv, cache_file);   
 * }
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

void fitness_cache_gi_llvm_pass(double fitness, node_str* indiv, char* cache_file) {

    // do nothing, default for now

}

/*
 * NAME
 *
 *   fitness_gi_llvm_pass
 *
 * DESCRIPTION
 *
 *  Calculates the fitness value specifically for a GI LLVM PASS
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
 * uint32_t gi_llvm_pass_fit = fitness_gi_llvm_pass(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */


double fitness_gi_llvm_pass(node_str* indiv, char* file, char** src_files, uint32_t num_src_files, bool vis, bool cache, char* cache_file, const char *cache_id, DataNode* indiv_data, uint32_t num_runs, int gen, bool fitness_with_var) {
    //visualization_print_individual_concise_details(indiv);
    char* sequence = malloc(sizeof(char) * 2000);
    sequence = seq_str_fitness(indiv);

    
	double fitness;
    fitness = indiv_data->fitness;
    if (!node_reeval_by_chance(indiv_data, gen)) {
        return indiv_data->fitness;
    }
    uint32_t success_runs = 0;

    char file_name[300];
    char base_name[300];
    char input_file[300];
    char output_file[300];
    char base_file[300];

    struct timeval start, end; 
    //clock_t start, end;
    //struct timespec start, end;

    uint32_t result = 0;
    double tol = 0.95;

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    char file_name_no_path[100];
    strcpy(file_name_no_path, "");
    char *t = strrchr(file_name, '/'); 
    if (!t) {
        strcpy(file_name_no_path, file_name);
    } else strcpy(file_name_no_path, t+1);

    strcpy(base_file, "");
    strcat(base_file, "src/files/llvm/junk_output/");
    strcat(base_file, file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, cache_id);

    strcpy(input_file, base_file);
    strcat(input_file, "_linked.ll");

    strcpy(output_file, base_file);
    strcat(output_file, "_shackleton.ll");

    if (vis) {
        printf("Calculating fitness of individual\n");
    }

    char opt_command[5000];
    char run_command[5000];
    strcpy(opt_command, "");
    strcat(opt_command, "opt ");
    strcat(opt_command, sequence);
    strcat(opt_command, "-S ");
    strcat(opt_command, input_file);
    strcat(opt_command, " -o ");
    strcat(opt_command, output_file);

    free(sequence);

    strcpy(run_command, "");
    llvm_form_exec_code_command_from_ll(output_file, run_command);

    llvm_run_command(opt_command);

    double total_time = 0.0;
    double time_taken = 0.0;
    double all_runtime[num_runs]; //Added 7/7/2021
    int counter = 0; //Added 7/7/2021

    //printf("run command: %s\n", run_command);
    for (uint32_t runs = 0; runs < num_runs; runs++) {

        gettimeofday(&start, NULL);
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        result = llvm_run_command(run_command);
        gettimeofday(&end, NULL);
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        //time_taken = (end.tv_sec - start.tv_sec);
        //time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        //time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) / BILLION;
        //time_taken = (double)( end.tv_sec - start.tv_sec )*1000000.0 + ( end.tv_nsec - start.tv_nsec ) / 1000.0;

        //printf("line 1443 time_taken=%lf, nsec_diff=%lf, sec_diff=%lf\n", time_taken, (double)end.tv_nsec-(double)start.tv_nsec, (double)end.tv_sec-(double)start.tv_sec);
        if (result == 0) {
            success_runs++;
            total_time = total_time + time_taken;
            all_runtime[counter++] = time_taken; //Added 7/7/2021
        }

    }
    if (success_runs < num_runs * tol) {
        time_taken = UINT32_MAX;
    } else {
        time_taken = total_time / success_runs;
    }
    //printf("reevaluate fitness, before: %lf, ", fitness);
    fitness = node_record_data(indiv_data, indiv, all_runtime, time_taken, success_runs, gen, fitness_with_var);
    //printf("after: %lf\n", fitness);
    return fitness;

}

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

void fitness_pre_cache(char* folder, char* test_file, char** src_files, uint32_t num_src_files, osaka_object_typ type, bool cache, double* track_fitness, const char *cache_id, uint32_t num_runs, bool fitness_with_var, const char** levels, const int num_levels) { //added 6/8/2021
//double fitness_pre_cache(char* folder, char* test_file, char** src_files, uint32_t num_src_files, osaka_object_typ type, bool cache) { //added 6/2/2021
//void fitness_pre_cache(char* folder, char* test_file, char** src_files, uint32_t num_src_files, osaka_object_typ type, bool cache) {
    if (type == 0) {    // SIMPLE
        fitness_pre_cache_simple(folder, cache);
    }
    else if (type == 1) {   // ASSEMBLER
        fitness_pre_cache_assembler(folder, cache);
    }
    else if (type == 2) {   // OSAKA_STRING
        fitness_pre_cache_osaka_string(folder, cache);
    }
    else if (type == 3) { // LLVM_PASS
        fitness_pre_cache_llvm_pass(folder, test_file, src_files, num_src_files, cache, track_fitness, cache_id, num_runs, fitness_with_var, levels, num_levels); //added 6/8/2021
        //return fitness_pre_cache_llvm_pass(folder, test_file, src_files, num_src_files, cache);  //added 6/2/2021
    }
    else if (type == 4) { // BINARY_UP_TO_512
        fitness_pre_cache_binary_up_to_512(folder, cache);
    }
    else if (type == 5) { // GI_LLVM_PASS
        fitness_pre_cache_gi_llvm_pass(folder, test_file, src_files, num_src_files, cache, track_fitness, cache_id, num_runs, fitness_with_var, levels, num_levels);
        //fitness_pre_cache_gi_llvm_pass(folder, cache);
    }

}

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

void fitness_cache(double fitness_value, node_str* indiv, char* cache_file) {
    //printf("fitness.c:1101, fitness_cache, cache_id: %s\n", cache_id);
    osaka_object_typ type = OBJECT_TYPE(indiv);

    if (type == 0) {    // SIMPLE
        return fitness_cache_simple(fitness_value, indiv, cache_file);
    }
    else if (type == 1) {   // ASSEMBLER
        return fitness_cache_assembler(fitness_value, indiv, cache_file);
    }
    else if (type == 2) {   // OSAKA_STRING
        return fitness_cache_osaka_string(fitness_value, indiv, cache_file);
    }
    else if (type == 3) {   // LLVM_PASS
        return fitness_cache_llvm_pass(fitness_value, indiv, cache_file);
    }
	else if (type == 4) {   // BINARY_UP_TO_512
		return fitness_cache_binary_up_to_512(fitness_value, indiv, cache_file);
	}
    else if (type == 5) {   // GI_LLVM_PASS
		return fitness_cache_gi_llvm_pass(fitness_value, indiv, cache_file);
	}

}

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

double fitness_top(node_str* indiv, bool vis, char* test_file, char** src_files, uint32_t num_src_files, bool cache, char* cache_file, const char *cache_id, DataNode* indiv_data, uint32_t num_runs, int gen, bool fitness_with_var) {

    osaka_object_typ type = OBJECT_TYPE(indiv);

    // the fitness function depends on the object type
    if (type == 0) {    // SIMPLE
        return fitness_simple(indiv, vis);
    }
    else if (type == 1) {   // ASSEMBLER
        return fitness_assembler(indiv, vis);
    }
    else if (type == 2) {   // OSAKA_STRING
        return fitness_osaka_string(indiv, vis);
    }
    else if (type == 3) {   // LLVM_PASS
        return fitness_llvm_pass(indiv, test_file, src_files, num_src_files, vis, cache, cache_file, cache_id, indiv_data, num_runs, gen, fitness_with_var);
    }
	else if (type == 4) {   // BINARY_UP_TO_512
		return fitness_binary_up_to_512(indiv, vis);
	}
    else if (type == 5) {   // GI_LLVM_PASS
		return fitness_gi_llvm_pass(indiv, test_file, src_files, num_src_files, vis, cache, cache_file, cache_id, indiv_data, num_runs, gen, fitness_with_var);
    }
    else {
        return 100;
    }

}

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

void fitness_setup() {

    fpfitness_simple = &fitness_simple;
    fpfitness_assembler = &fitness_assembler;
    fpfitness_osaka_string = &fitness_osaka_string;
    fpfitness_llvm_pass = &fitness_llvm_pass;
	fpfitness_binary_up_to_512 = &fitness_binary_up_to_512;
    fpfitness_gi_llvm_pass = &fitness_gi_llvm_pass;

}


