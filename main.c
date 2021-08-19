/*
 ================================================================================
 Name        : main.c
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

 Description : Rough framework for inputting evolutionary
                             parameters for genetic programming
 ================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //Added 6/8/2021, for checking whether file exists
#include "src/support/test.h"
#include "src/module/llvm_pass.h"

void print_help_msg(uint32_t argc, char* argv[], uint32_t num_generations, uint32_t num_population_size, uint32_t percent_crossover, uint32_t percent_mutation, uint32_t percent_elite, uint32_t tournament_size, bool visualization);
void print_launch_msg(uint32_t num_generations, uint32_t num_population_size, uint32_t percent_crossover, uint32_t percent_mutation, uint32_t percent_elite, uint32_t tournament_size, bool visualization);
void process_params(uint32_t argc, char* argv[], uint32_t *num_generations, uint32_t *num_population_size, uint32_t *percent_crossover, uint32_t *percent_mutation, uint32_t *percent_elite, uint32_t *tournament_size, bool *visualization);
char** set_llvm_optimize(uint32_t argc, char* argv[], char test_file[], uint32_t* num_src_files_ptr);
void set_test_file(uint32_t argc, char* argv[], char test_file[]);
char** set_src_file(uint32_t argc, char* argv[], uint32_t* num_src_files_ptr);
char** read_src_files(char source_code_inputs[], uint32_t* num_src_files_ptr);
char** set_test_src_files(uint32_t argc, char* argv[], char test_file[], bool* llvm_optimizing_ptr, osaka_object_typ* curr_type_ptr, uint32_t* num_src_files_ptr);
osaka_object_typ set_obj_type(uint32_t argc, char* argv[]);
bool check_test(uint32_t argc, char* argv[]);
bool check_caching(uint32_t argc, char* argv[]);
char* set_cache_id(uint32_t argc, char* argv[], char* temp);
void log_results_to_summary(uint32_t argc, char* argv[], const char* cache_id, uint32_t num_generations, uint32_t num_population_size, uint32_t percent_crossover, uint32_t percent_mutation, uint32_t percent_elite, uint32_t tournament_size, bool visualization, double shackleton_time, double* track_fitness, const char** levels, const int num_levels, int gen_evolved);
void free_all(bool llvm_optimizing, char** src_files, uint32_t num_src_files, double* track_fitness, const char** levels);

int num_passes;
char** values;

int main(uint32_t argc, char* argv[]) {

    // parameters for the evolution itself
    uint32_t num_generations = 10;
    uint32_t num_population_size = 20;
    uint32_t percent_crossover = 75;
    uint32_t percent_mutation = 20;
    uint32_t percent_elite = 20;
    uint32_t tournament_size = 2;
    bool visualization = false;
    osaka_object_typ curr_type = NOTSET;

    // variables that are only used for llvm optimization
    char** src_files;
    char test_file[100];
    char answer[5];
    //char num_src_files_str[10]; //uncomment again if we go back to asking for all source files individually
    uint32_t num_src_files = 0;

    // flag variables
    bool test = false;
    bool llvm_optimizing = false;
    bool caching = false;
    char temp[100];
    const char* cache_id;

    uint32_t indiv_size = 0;
    // variables for pre_cache
    const int num_levels = 7;
    const char** levels = malloc(num_levels * sizeof(char*));
    levels[0] = "";
    levels[1] = "O0";
    levels[2] = "O1";
    levels[3] = "O2";
    levels[4] = "O3";
    levels[5] = "Os";
    levels[6] = "Oz";

    // variables used for logging results
    struct timeval shackleton_start, shackleton_end;   // Added 6/14/2021
    //int hash_cap = num_population_size * 5;  // Added 7/7/2021
    //DataNode** all_indiv = (DataNode**) malloc(sizeof(DataNode*) * hash_cap);  // Added 7/7/2021

    // --------------------------------------------------------------------------------
    // Arg parsing to see if the help flag was triggered, overrides all other flags ---
    print_help_msg(argc, argv, num_generations, num_population_size, percent_crossover, percent_mutation, percent_elite, tournament_size, visualization);

    // --------------------------------------------------------------------------------
    // Parsing and interaction with users begin ---------------------------------------
    print_launch_msg(num_generations, num_population_size, percent_crossover, percent_mutation, percent_elite, tournament_size, visualization);

    // --------------------------------------------------------------------------------
    // Parameteres_file parsing, added option to specify name of parameter file - 6/4/2021
    process_params(argc, argv, &num_generations, &num_population_size, &percent_crossover, &percent_mutation, &percent_elite, &tournament_size, &visualization);
    // this array contains runtime for: no_opt, O0, O1, O2, O3, Os, Oz, initial population, gen1, gen2, etc.
    double *track_fitness = calloc(num_generations + num_levels + 1, sizeof(double)); // Added 6/8/2021
    
    test = check_test(argc, argv);
    caching = check_caching(argc, argv);
    cache_id = set_cache_id(argc, argv, temp);

    // --------------------------------------------------------------------------------
    // Reading test and source files --------------------------------------------------
    src_files = set_test_src_files(argc, argv, test_file, &llvm_optimizing, &curr_type, &num_src_files);
    //llvm_init_valid_values();
    //llvm_init_from_list();

    // --------------------------------------------------------------------------------
    // Executing Code -----------------------------------------------------------------
    gettimeofday(&shackleton_start, NULL);  //added 6/14/2021
    int gen_evolved = evolution_basic_crossover_and_mutation_with_replacement(num_generations, num_population_size, indiv_size, tournament_size, percent_mutation, percent_crossover, percent_elite, curr_type, visualization, test_file, src_files, num_src_files, caching, track_fitness, cache_id, levels, num_levels); // Added 6/21/2021
    //evolution_basic_crossover_and_mutation_with_replacement(num_generations, num_population_size, 10, tournament_size, percent_mutation, percent_crossover, curr_type, visualization, test_file, src_files, num_src_files, caching);
    gettimeofday(&shackleton_end, NULL);  //added 6/14/2021
    
    // --------------------------------------------------------------------------------
    // Tests --------------------------------------------------------------------------
    if (test) {
        test_master(num_generations, num_population_size, indiv_size, tournament_size, percent_mutation, percent_crossover, percent_elite, curr_type, visualization, test_file, src_files, num_src_files, caching, track_fitness);
    }

    // --------------------------------------------------------------------------------
    // Added 6/4/2021 for logging results from parameter tuning experiments -----------
    double shackleton_time = (shackleton_end.tv_sec - shackleton_start.tv_sec) * 1e6;
    shackleton_time = (shackleton_time + (shackleton_end.tv_usec - shackleton_start.tv_usec)) * 1e-6;
    log_results_to_summary(argc, argv, cache_id, num_generations, num_population_size, percent_crossover, percent_mutation, percent_elite, tournament_size, visualization, shackleton_time, track_fitness, levels, num_levels, gen_evolved);

    // --------------------------------------------------------------------------------
    // Free anything that needs to be freed -------------------------------------------
    free_all(llvm_optimizing, src_files, num_src_files, track_fitness, levels);
    // --------------------------------------------------------------------------------

    printf("\n------------------------------------------------------ Run of Project Shackleton complete ------------------------------------------------------\n\n");
    printf("Shackleton runtime: %fsec\n", shackleton_time);  //added 6/4/4021

    return 0;

}


void print_help_msg(uint32_t argc, char* argv[], uint32_t num_generations, uint32_t num_population_size, uint32_t percent_crossover, uint32_t percent_mutation, uint32_t percent_elite, uint32_t tournament_size, bool visualization) {
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-help") == 0) {
                printf("\nYou have elected to view the options for the Shackleton tool. The information given with this prompt is a quick guide to the important"
                            " aspects of the tool and its possible inputs and flags\n\nHere are the possible flags that can be given to the tool and a short description for each:\n\n");
                printf("\t-help\t\t\t: What got you to these statements! Offers information on inputs to the command line interface for this tool.\n");
                printf("\t-parameters_file\t: Specifies that an input file at src/files/parameters.txt will be used to change some of the parameters for evolution.\n");
                printf("\t-test\t\t\t: Enables the testing script for Shackleton to be run. Will be run regardless of other parameters specified.\n");
                printf("\t-llvm_optimize\t\t: Specifies that the LLVM integrated portion of the tool will be used to optimize LLVM using evolution.\n\t\t\t\t  This option automatically sets the object type needed to LLVM_PASS\n");
                printf("\t-cache\t\t\t: Caches information for each evolutionary run into files. This means something different depending on the object type being used.\n\n");
                printf("The Shackleton framework has a set number of object types available to evolve. If you would like to use different types than the ones listed below,"
                                        " you can use the Editor tool found at src/editor_tool to add new object types. Please follow the instructions for using that tool given in the"
                                        " README of the github repository in that subdirectory. Here are the currently available object types:\n\n");
                printf("\t[1] SIMPLE\n");
                printf("\t[2] ASSEMBLER\n");
                printf("\t[3] OSAKA_STRING\n");
                printf("\t[4] LLVM_PASS\n");
                printf("\t[5] BINARY_UP_TO_512\n\n");
                printf("In addition to changing the type of object that will have a sequence evolved for it, you can also change the parameters of the evolutionary process itself."
                                    " Here are the options available as well as a short description and their default values:\n\n");
                printf("\t[1] num_generations = %d\t\t-- Maximum number of generations for an evolutionary run\n", num_generations);
                printf("\t[2] num_population_size = %d\t\t-- The number of individuals in the population per generation\n", num_population_size);
                printf("\t[3] percent_crossover = %d\t\t-- The percent chance that any one individual will have crossover applied to it\n", percent_crossover);
                printf("\t[4] percent_mutation = %d\t\t-- The percent chance that any one individual will have mutation applied to it\n", percent_mutation);
                printf("\t[5] percent_elite = %d\t\t-- The percentage of best individuals in the population to stay the same in the next generation\n", percent_elite);  //Added 6/14/2021
                printf("\t[6] tournament_size = %d\t\t\t-- The number of individuals in each tournament for selection\n", tournament_size);
                printf("\t[7] visualization = %s\t\t-- Whether or not visualization of the evolution process is enabled\n\n", visualization ? "true" : "false");
                printf("These are all the options that are built into the command line interface for the Shackleton tool. If you have more questions about the inner"
                                        " workings of the tool and everything that goes into the implemention, please refer to the README documents contained in the github"
                                        " repository which can be found at: https://github.com/ARM-software/Shackleton-Framework. \n\n");
                exit(0);
            }
        }
    }
}

void print_launch_msg(uint32_t num_generations, uint32_t num_population_size, uint32_t percent_crossover, uint32_t percent_mutation, uint32_t percent_elite, uint32_t tournament_size, bool visualization) {
    printf("\n--------------------------------------------------------- Launching Project Shackleton ---------------------------------------------------------\n\n\n");

    printf("Welcome to the Shackleton Framework tool, a generic genetic programming framework that enables easier experimentation for linear genetic programming\n" 
                 "for a large range of different use cases. This framework's goal is to be a valuable tool for both established researchers in the genetic algorithms\n"
                 "field and for novices exploring the area for the first time. Before launching fully, here are the default parameters for evolution:\n\n");

    printf("\t[1] num_generations = %d\t\t-- Maximum number of generations for an evolutionary run\n", num_generations);
    printf("\t[2] num_population_size = %d\t\t-- The number of individuals in the population per generation\n", num_population_size);
    printf("\t[3] percent_crossover = %d\t\t-- The percent chance that any one individual will have crossover applied to it\n", percent_crossover);
    printf("\t[4] percent_mutation = %d\t\t-- The percent chance that any one individual will have mutation applied to it\n", percent_mutation);
    printf("\t[5] percent_elite = %d\t\t-- The percentage of best individuals in the population to stay the same in the next generation\n", percent_elite);
    printf("\t[6] tournament_size = %d\t\t\t-- The number of individuals in each tournament for selection\n", tournament_size);
    printf("\t[7] visualization = %s\t\t-- Whether or not visualization of the evolution process is enabled\n\n", visualization ? "true" : "false");

}

void process_params(uint32_t argc, char* argv[], uint32_t *num_generations, uint32_t *num_population_size, uint32_t *percent_crossover, uint32_t *percent_mutation, uint32_t *percent_elite, uint32_t *tournament_size, bool *visualization) {
    bool using_params_file = false;
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            char target[100];  
            int config_len = strlen("-parameters_file");
            strncpy(target, argv[curr], config_len);  
            target[config_len] = '\0';
            if (strcmp(target, "-parameters_file") == 0) {
                char param_file[500];
                if (strcmp(argv[curr], "-parameters_file") == 0) {
                    strcpy(param_file, "parameters.txt");
                } else {
                    char *equal;
                    int index;
                    equal = strchr(argv[curr], '=');
                    index = (int)(equal - argv[curr]);
                    int length = strlen(argv[curr]) - index;
                    char substr[100];
                    if(length >= 0) {
                        strncpy(substr, argv[curr]+index+1, length);
                        substr[length] = '\0';
                    }
                    strcpy(param_file, substr);
                }
                printf("Using a parameters file has been chosen, any changes to parameters will be taken from the src/files/params/%s\n\n", param_file);
                set_params_from_file(num_generations, num_population_size, percent_crossover, percent_mutation, percent_elite, tournament_size, visualization, param_file);
                printf("\nHere are the values being used for this evolutionary run:\n");
                printf("\t[1] num_generations = %d\n", *num_generations);
                printf("\t[2] num_population_size = %d\n", *num_population_size);
                printf("\t[3] percent_crossover = %d\n", *percent_crossover);
                printf("\t[4] percent_mutation = %d\n", *percent_mutation);
                printf("\t[5] percent_elite = %d\n", *percent_elite);
                printf("\t[6] tournament_size = %d\n", *tournament_size);
                printf("\t[7] visualization = %s\n\n", *visualization ? "true" : "false");
                using_params_file = true;
            }
        }
    }
    if (!using_params_file) {
        printf("Would you like to change any of these default settings? y/n: ");
        char answer[4];
        scanf("%s", answer);
        if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
            while (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                printf("\n\nWhich parameter from the above would you like to change? 1/2/3/4/5/6: ");
                scanf("%s", answer);

                if (strcmp(answer, "1") == 0) {
                    printf("\nPlease specify the number of generations to be used (int number): ");
                    scanf("%s", answer);
                    str2int(num_generations, answer, 10);
                    printf("\nnum_generations has been set to the requested value of %d\n\n", *num_generations);
                }
                else if (strcmp(answer, "2") == 0) {
                    printf("\nPlease specify the population size to be used (int number): ");
                    scanf("%s", answer);
                    str2int(num_population_size, answer, 10);
                    printf("\nnum_population_size has been set to the requested value of %d\n\n", *num_population_size);
                }
                else if (strcmp(answer, "3") == 0) {
                    printf("\nPlease specify the percent crossover to be used (int number)/100: ");
                    scanf("%s", answer);
                    str2int(percent_crossover, answer, 10);
                    printf("\npercent_crossover has been set to the requested value of %d\n\n", *percent_crossover);
                }
                else if (strcmp(answer, "4") == 0) {
                    printf("\nPlease specify the percent mutation to be used (int number)/100: ");
                    scanf("%s", answer);
                    str2int(percent_mutation, answer, 10);
                    printf("\npercent_mutation has been set to the requested value of %d\n\n", *percent_mutation);
                }
                else if (strcmp(answer, "5") == 0) {
                    printf("\nPlease specify the percent elite to be used (int number)/100: ");
                    scanf("%s", answer);
                    str2int(percent_elite, answer, 10);
                    printf("\npercent_elite has been set to the requested value of %d\n\n", *percent_elite);
                }
                else if (strcmp(answer, "6") == 0) {
                    printf("\nPlease specify the tournament size to be used (int number): ");
                    scanf("%s", answer);
                    str2int(tournament_size, answer, 10);
                    printf("\nTournament size has been set to the requested value of %d\n\n", *tournament_size);
                }
                else if (strcmp(answer, "7") == 0) {
                    printf("\nPlease specify if visualization should be enabled (y/n): ");
                    scanf("%s", answer);
                    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                        *visualization = true;
                    }
                    else {
                        *visualization = false;
                    }
                    printf("\nVisualization has been set to the requested value of %s\n\n", *visualization ? "true" : "false");
                }
                else {
                    printf("The input was not a valid option, please only choose a value between 1 and 6\n");
                }

                printf("Would you still like to change any settings? y/n: ");
                scanf("%s", answer);
            }
        }
        else {
            printf("\n\nNo additional arguments passed, default values used\n");
        }
    }
}

void set_test_file(uint32_t argc, char* argv[], char test_file[]) {
    strcpy(test_file, "");
    bool test_file_set = false;
    for (uint32_t curr = 1; curr < argc; curr++) {
        char target[100]; 
        int config_len = strlen("-test_file");
        strncpy(target, argv[curr], config_len);  
        target[config_len] = '\0';
        if (strcmp(target, "-test_file") == 0) {  
            if (strcmp(argv[curr], "-test_file") == 0) {
                strcpy(test_file, "");
            } else {
                char *equal;
                int index;
                equal = strchr(argv[curr], '=');
                index = (int)(equal - argv[curr]);
                int length = strlen(argv[curr]) - index;
                char substr[100];
		        if(length >= 0) {
                    strncpy(substr, argv[curr]+index+1, length);
                    substr[length] = '\0';
                }
                strcpy(test_file, substr);
                test_file_set = true;
            }
        }
    }
    if (!test_file_set) {
        printf("You are using the llvm-integrated optimization tool in Shackleton. Please provide a main .c or .cpp test file to use for fitness calculations, with extension: ");
        scanf("%s", test_file);
        test_file_set = true;
    }
    printf("You have chosen %s as your test file.\n", test_file);
}

char** set_src_file(uint32_t argc, char* argv[], uint32_t* num_src_files_ptr) {
    char source_code_inputs[200];
    char temp_source_code_inputs[200];
    bool source_file_set = false;
    for (uint32_t curr = 1; curr < argc; curr++) {
        char target[100];  
        int config_len = strlen("-source_file");
        strncpy(target, argv[curr], config_len);  
        target[config_len] = '\0';
        if (strcmp(target, "-source_file") == 0) {  
            if (strcmp(argv[curr], "-source_file") == 0) {
                strcpy(temp_source_code_inputs, "");
            } else {
                char *equal;
                int index;
                equal = strchr(argv[curr], '=');
                index = (int)(equal - argv[curr]);
                int length = strlen(argv[curr]) - index;
                char substr[100];
		if(length >= 0) {
                    strncpy(substr, argv[curr]+index+1, length);
                    substr[length] = '\0';
                }
                strcpy(temp_source_code_inputs, substr);
                source_file_set = true;
            }
        }
    }
    if (!source_file_set) {
        printf("Please provide a .txt containing line-by-line the source files to be used for your use case. The locations should be relative to the src/files/llvm/ folder, and the .txt file itself should be located in the src/files/llvm/inputs/ folder: ");
        scanf("%s", temp_source_code_inputs);
        source_file_set = true;
    }
    strcpy(source_code_inputs, "src/files/llvm/inputs/");
    strcat(source_code_inputs, temp_source_code_inputs);

    return read_src_files(source_code_inputs, num_src_files_ptr);
}

char** read_src_files(char source_code_inputs[], uint32_t* num_src_files_ptr) {
    char** src_files;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int curr_line_number = -1;
    char *pos;

    FILE * src_ptr = fopen(source_code_inputs, "r");
    if (src_ptr == NULL) {
        printf("Source file %s could not be opened\n", source_code_inputs);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, src_ptr)) != -1) {
        //printf("Retrieved line of length %zu: \n", read);
        if ((pos=strchr(line, '\n')) != NULL) {
            *pos = '\0';
        }
        if (curr_line_number == -1) {
            sscanf(line, "%d", num_src_files_ptr);
            printf("We have this many items in the file: %d\n", *num_src_files_ptr);
            src_files = malloc(((*num_src_files_ptr)+1) * sizeof(char*));
            for (int j = 0; j < ((*num_src_files_ptr)+1); j++) {
                src_files[j] = (char *)malloc(100);
            }
        }
        else {
            printf("Adding this file to the list of src files: %s\n",line);
            strcpy(src_files[curr_line_number], line);

        }
        curr_line_number = curr_line_number + 1;
    }
    fclose(src_ptr);
    free(line);
    return src_files;
}

char** set_llvm_optimize(uint32_t argc, char* argv[], char test_file[], uint32_t* num_src_files_ptr) {
    char** src_files;
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-llvm_optimize") == 0) {
                set_test_file(argc, argv, test_file);
                return set_src_file(argc, argv, num_src_files_ptr); 
            }
        }
    }
    return NULL;
}

char** set_test_src_files(uint32_t argc, char* argv[], char test_file[], bool* llvm_optimizing_ptr, osaka_object_typ* curr_type_ptr, uint32_t* num_src_files_ptr) {
    char** src_files = set_llvm_optimize(argc, argv, test_file, num_src_files_ptr);
    *llvm_optimizing_ptr = src_files == NULL ? false : true;
    if (!*llvm_optimizing_ptr) {
        *curr_type_ptr = set_obj_type(argc, argv);
        if (*curr_type_ptr == 3) {
            set_test_file(argc, argv, test_file);
            src_files = set_src_file(argc, argv, num_src_files_ptr);
            *llvm_optimizing_ptr = true;
        }
    } else {
        *curr_type_ptr = 3; // set to LLVM_PASS, required when optimizing llvm
    }
    return src_files;
}

osaka_object_typ set_obj_type(uint32_t argc, char* argv[]) {
    char type[5];
    uint32_t type_num;
    bool type_num_set = false;
    for (uint32_t curr = 1; curr < argc; curr++) {
        char target[100];
        int config_len = strlen("-obj_type");
        strncpy(target, argv[curr], config_len);  
        target[config_len] = '\0';
        if (strcmp(target, "-obj_type") == 0) {  
            if (strcmp(argv[curr], "-obj_type") == 0) {
                strcpy(type, "");
            } else {
                char *equal;
                int index;
                equal = strchr(argv[curr], '=');
                index = (int)(equal - argv[curr]);
                int length = strlen(argv[curr]) - index;
                char substr[100];
                if(length >= 0) {
                    strncpy(substr, argv[curr]+index+1, length);
                    substr[length] = '\0';
                }
                strcpy(type, substr);
                type_num_set = true;
                printf("You have chosen object type = %s.\n", type);
            }
        }
    }
    if (!type_num_set) {
        osaka_print_available_object_types();
        printf("\nWhich object type will you be using? 1/2/3/4/5: ");
        scanf("%s", type);
        printf("\n");
    }
    str2int(&type_num, type, 10);
    return type_num - 1;
}

bool check_test(uint32_t argc, char* argv[]) {
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-test") == 0) {
                return true;
            }
        }
    }
    return false;
}

bool check_caching(uint32_t argc, char* argv[]) {
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-cache") == 0) {
                return true;
            }
        }
    }
    return false;
}

char* set_cache_id(uint32_t argc, char* argv[], char* temp) {
    bool cache_id_set = false;
    char substr[100];
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            char target[100];
            int config_len = strlen("-id");
            strncpy(target, argv[curr], config_len);  
            target[config_len] = '\0';
            if (strcmp(target, "-id") == 0) {
                if (strcmp(argv[curr], "-id") != 0) {
                    char *equal;
                    int index;
                    equal = strchr(argv[curr], '=');
                    index = (int)(equal - argv[curr]);
                    int length = strlen(argv[curr]) - index;
                    if(length >= 0) {
                        strncpy(substr, argv[curr]+index+1, length);
                        substr[length] = '\0';
                    }
                    //strcpy(cache_id, substr);
                    printf("You have entered cache ID = %s.\n", substr);
                    cache_id_set = true;
                }
            }
        }
    }
    if (!cache_id_set) {
        strcpy(substr, "");
        srand(time(0));
        sprintf(substr, "%d", rand() % 1000);
    }
    //printf("inside main, substr=%s, cid=%s\n", substr, cid);
    strcpy(temp, substr);
    return temp;
}

void log_results_to_summary(uint32_t argc, char* argv[], const char* cache_id, \
                            uint32_t num_generations, uint32_t num_population_size, \
                            uint32_t percent_crossover, uint32_t percent_mutation, \
                            uint32_t percent_elite, uint32_t tournament_size, \
                            bool visualization, double shackleton_time, double* track_fitness,\
                            const char** levels, const int num_levels, int gen_evolved) {
    // --------------------------------------------------------------------------------
    // Added 6/4/2021 for logging results from parameter tuning experiments
    if (argc >= 2) {
        char log_file[500];
        bool log = false;
        for (uint32_t curr = 1; curr < argc; curr++) {
            char target[100];  
            int config_len = strlen("-log_results");
            strncpy(target, argv[curr], config_len);
            target[12] = '\0';
            if (strcmp(target, "-log_results") != 0) {
                continue;
            }
            if (strcmp(argv[curr], "-log_results") == 0) {
                printf("WARNING: -log_results chosen but log_file name wasn't provided; no results will be recorded.");
                continue;
            }
            char *equal;
            int index;
            equal = strchr(argv[curr], '=');
            index = (int)(equal - argv[curr]);
            int length = strlen(argv[curr]) - index - 1;
            char substr[500];
            strcpy(substr,"");
		    if(length >= 0) {
               strncpy(substr, argv[curr]+index+1, length);
               substr[length] = '\0';
            } else {
                printf("WARNING: -log_results chosen but reading log_file name failed; no results will be recorded.");
                continue;
            }
            strcpy(log_file, substr);
            log = true;
        }
        if (!log) {
            return;
        }
        // log_file name set, not writing results to the file
        strcat(log_file, ".csv");
        //printf("Logging results to %s\n", log_file);
        if( access( log_file, F_OK ) != 0 ) {
            FILE *csv_ptr = fopen(log_file, "w");
            fprintf(csv_ptr, "cache_id,gen_evolved,num_generations,num_population_size,percent_crossover,percent_mutation,percent_elite,tournament_size,shackleton_runtime,no_opt,");
            for (int l = 1; l < num_levels; l++) {
                fprintf(csv_ptr, "%s,", levels[l]);
            }
            fprintf(csv_ptr, "initial,");
		    for (int k = 1; k <= num_generations; k++) {
                fprintf(csv_ptr, "gen%d%s", k, k==num_generations?"\n":",");
            }
            fclose(csv_ptr);
        }
        FILE *csv_ptr = fopen(log_file, "a");
        fprintf(csv_ptr, "%s,%d,%d,%d,%d,%d,%d,%d,%lf,",
                          cache_id, 
                          gen_evolved,
                          num_generations, 
                          num_population_size, 
                          percent_crossover, 
                          percent_mutation, 
                          percent_elite,
                          tournament_size,
                          shackleton_time);
        for (int k = 0; k < num_generations + num_levels + 1; k++) {
            fprintf(csv_ptr, "%lf%s", track_fitness[k], k==num_generations+num_levels? "\n":",");
        }
		fclose(csv_ptr);
    }
}


void free_all(bool llvm_optimizing, char** src_files, uint32_t num_src_files, double* track_fitness, const char** levels) {
    if (llvm_optimizing) {
        for (int i = 0; i < num_src_files + 1; i++) {
            free(src_files[i]);
        }
        //printf("freed all source files\n");
        free(src_files);
        //free(values);
        //printf("freed src_files\n");
    }
    free(track_fitness);
    //printf("freed track_fitness\n");
    free(levels);
    //printf("freed levels\n");
}