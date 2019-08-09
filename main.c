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

#include "src/support/test.h"

int main(uint32_t argc, char* argv[]) {

    // parameters for the evolution itself
    uint32_t num_generations = 10;
    uint32_t num_population_size = 20;
    uint32_t percent_crossover = 75;
    uint32_t percent_mutation = 20;
    uint32_t tournament_size = 2;
    bool visualization = false;
    osaka_object_typ curr_type = NOTSET;

    // variables that are only used for llvm optimization
    char** src_files;
    char test_file[50];
    char answer[5];
    char num_src_files_str[10];
    uint32_t num_src_files = 0;

    // flag variables
    bool test = false;
    bool llvm_optimizing = false;
    bool using_params_file = false;
    bool caching = false;

    // Arg parsing to see if the help flag was triggered, overrides all other flags

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
                printf("\t[5] tournament_size = %d\t\t\t-- The number of individuals in each tournament for selection\n", tournament_size);
                printf("\t[6] visualization = %s\t\t-- Whether or not visualization of the evolution process is enabled\n\n", visualization ? "true" : "false");
                printf("These are all the options that are built into the command line interface for the Shackleton tool. If you have more questions about the inner"
                            " workings of the tool and everything that goes into the implemention, please refer to the README documents contained in the github"
                            " repository which can be found at: https://github.com/ARM-software/Shackleton-Framework. \n\n");
                exit(0);
            }
        }
    }

    // Parsing and interaction with users begin

    printf("\n--------------------------------------------------------- Launching Project Shackleton ---------------------------------------------------------\n\n\n");

    printf("Welcome to the Shackleton Framework tool, a generic genetic programming framework that enables easier experimentation for linear genetic programming\n" 
                 "for a large range of different use cases. This framework's goal is to be a valuable tool for both established researchers in the genetic algorithms\n"
                 "field and for novices exploring the area for the first time. Before launching fully, here are the default parameters for evolution:\n\n");

    printf("\t[1] num_generations = %d\t\t-- Maximum number of generations for an evolutionary run\n", num_generations);
    printf("\t[2] num_population_size = %d\t\t-- The number of individuals in the population per generation\n", num_population_size);
    printf("\t[3] percent_crossover = %d\t\t-- The percent chance that any one individual will have crossover applied to it\n", percent_crossover);
    printf("\t[4] percent_mutation = %d\t\t-- The percent chance that any one individual will have mutation applied to it\n", percent_mutation);
    printf("\t[5] tournament_size = %d\t\t\t-- The number of individuals in each tournament for selection\n", tournament_size);
    printf("\t[6] visualization = %s\t\t-- Whether or not visualization of the evolution process is enabled\n\n", visualization ? "true" : "false");

    // Core arg parsing ---------------------------------------------------------------

    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-parameters_file") == 0) {
                printf("Using a parameters file has been chosen, any changes to parameters will be taken from the src/files/parameters.txt\n\n");
                set_params_from_file(&num_generations, &num_population_size, &percent_crossover, &percent_mutation, &tournament_size, &visualization);
                printf("\nHere are the values being used for this evolutionary run:\n");
                printf("\t[1] num_generations = %d\n", num_generations);
                printf("\t[2] num_population_size = %d\n", num_population_size);
                printf("\t[3] percent_crossover = %d\n", percent_crossover);
                printf("\t[4] percent_mutation = %d\n", percent_mutation);
                printf("\t[5] tournament_size = %d\n", tournament_size);
                printf("\t[6] visualization = %s\n\n", visualization ? "true" : "false");

                using_params_file = true;
            }
        }
    }
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-llvm_optimize") == 0) {

                strcpy(test_file, "");

                printf("You are using the llvm-integrated optimization tool in Shackleton. Please provide a main .c or .cpp test file to use for fitness calculations, with extension: ");
                scanf("%s", test_file);
                printf("\nYou have chosen %s as your test file. How many source files will this file be testing?: ", test_file);

                scanf("%s", num_src_files_str);
                str2int(&num_src_files, num_src_files_str, 10);

                src_files = malloc(num_src_files * sizeof(char*));
                for (int j = 0; j < num_src_files; j++) {
                    src_files[j] = (char *)malloc(50);
                }

                printf("%d file(s) will be tested. ", num_src_files);
                
                for (int i = 0; i < num_src_files; i++) {
                    printf("Please provide source file number %d: ", i+1);
                    scanf("%s", src_files[i]);
                }

                llvm_optimizing = true;

            }
        }
    }
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-test") == 0) {
                test = true;
            }
        }
    }
    if (argc >= 2) {
        for (uint32_t curr = 1; curr < argc; curr++) {
            if (strcmp(argv[curr], "-cache") == 0) {
                caching = true;
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
                    str2int(&num_generations, answer, 10);
                    printf("\nnum_generations has been set to the requested value of %d\n\n", num_generations);
                }
                else if (strcmp(answer, "2") == 0) {
                    printf("\nPlease specify the population size to be used (int number): ");
                    scanf("%s", answer);
                    str2int(&num_population_size, answer, 10);
                    printf("\nnum_population_size has been set to the requested value of %d\n\n", num_population_size);
                }
                else if (strcmp(answer, "3") == 0) {
                    printf("\nPlease specify the percent crossover to be used (int number)/100: ");
                    scanf("%s", answer);
                    str2int(&percent_crossover, answer, 10);
                    printf("\npercent_crossover has been set to the requested value of %d\n\n", percent_crossover);
                }
                else if (strcmp(answer, "4") == 0) {
                    printf("\nPlease specify the percent mutation to be used (int number)/100: ");
                    scanf("%s", answer);
                    str2int(&percent_mutation, answer, 10);
                    printf("\npercent_mutation has been set to the requested value of %d\n\n", percent_mutation);
                }
                else if (strcmp(answer, "5") == 0) {
                    printf("\nPlease specify the tournament size to be used (int number): ");
                    scanf("%s", answer);
                    str2int(&tournament_size, answer, 10);
                    printf("\nTournament size has been set to the requested value of %d\n\n", tournament_size);
                }
                else if (strcmp(answer, "6") == 0) {
                    printf("\nPlease specify if visualization should be enabled (y/n): ");
                    scanf("%s", answer);
                    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
                        visualization = true;
                    }
                    else {
                        visualization = false;
                    }
                    printf("\nVisualization has been set to the requested value of %s\n\n", visualization ? "true" : "false");
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

    if (!llvm_optimizing) {
        char type[5];
        uint32_t type_num;
        osaka_print_available_object_types();
        printf("\nWhich object type will you be using? 1/2/3/4/5: ");
        scanf("%s", type);
        printf("\n");
        str2int(&type_num, type, 10);
        curr_type = type_num - 1;

        if (curr_type == 3) {
            strcpy(test_file, "");

            printf("You are using the llvm-integrated optimization tool in Shackleton. Please provide a main .c or .cpp test file to use for fitness calculations, with extension: ");
            scanf("%s", test_file);
            printf("\nYou have chosen %s as your test file. How many source files will this file be testing?: ", test_file);

            scanf("%s", num_src_files_str);
            str2int(&num_src_files, num_src_files_str, 10);

            src_files = malloc(num_src_files * sizeof(char*));
            for (int j = 0; j < num_src_files; j++) {
                src_files[j] = (char *)malloc(50);
            }

            printf("%d file(s) will be tested. ", num_src_files);
            
            for (int i = 0; i < num_src_files; i++) {
                printf("Please provide source file number %d: ", i+1);
                scanf("%s", src_files[i]);
            }

            llvm_optimizing = true;
        }

    }
    else {
        curr_type = 3; // set to LLVM_PASS, required when optimizing llvm
    }

    // --------------------------------------------------------------------------------

    // Initializing vars --------------------------------------------------------------

    uint32_t temp = 0;
    srand(time(0));

    // --------------------------------------------------------------------------------

    // Executing Code -----------------------------------------------------------------

    evolution_basic_crossover_and_mutation_with_replacement(num_generations, num_population_size, 10, tournament_size, percent_mutation, percent_crossover, curr_type, visualization, test_file, caching);
    
    // --------------------------------------------------------------------------------

    // Tests --------------------------------------------------------------------------

    if (test) {
        test_master(num_generations, num_population_size, 10, tournament_size, percent_mutation, percent_crossover, curr_type, visualization, test_file, caching);
    }

    // --------------------------------------------------------------------------------

    // Free anything that needs to be freed -------------------------------------------

    if (llvm_optimizing) {
        for (int i = 0; i < num_src_files; i++) {
            free(src_files[i]);
        }
        free(src_files);
    }

    // --------------------------------------------------------------------------------

    printf("\n------------------------------------------------------ Run of Project Shackleton complete ------------------------------------------------------\n\n");

    return 0;

}