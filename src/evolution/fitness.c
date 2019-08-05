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

/*
 * ROUTINES
 */

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
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t llvm_pass_fit = fitness_llvm_pass(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_llvm_pass(node_str* indiv, char* file, bool vis, bool cache, char* cache_file) {

    double fitness = 100.0;

    char file_name[30];
    char base_name[60];
    char input_file[60];
    char output_file[60];

    struct timeval start, end; 
    uint32_t result = 0;

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    strcpy(base_name, "src/files/llvm/");

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(input_file, base_name);
    strcat(input_file, file_name);
    strcat(input_file, "_linked.ll");

    strcpy(output_file, base_name);
    strcat(output_file, "junk_output/");
    strcat(output_file, file_name);
    strcat(output_file, "_linked_temp.ll");

    if (vis) {

        printf("Calculating fitness of individual\n");

    }

    char opt_command[5000];
    char run_command[5000];
    strcpy(opt_command, "");
    strcpy(run_command, "");

    llvm_form_opt_command(indiv, NULL, 0, input_file, output_file, opt_command);
    llvm_form_exec_code_command_from_ll(output_file, run_command);

    printf("opt command: %s\n\nrun command: %s\n\n", opt_command, run_command);

    llvm_run_command(opt_command);

    gettimeofday(&start, NULL);
    result = llvm_run_command(run_command);
    gettimeofday(&end, NULL);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Run command took %f seconds to run\n\n", time_taken);
    fitness = time_taken;
    if (result > 0) {

        fitness = UINT32_MAX;
    
    }

    if (cache) {

        char string[30000];
        char fitness_num[100];
        char input_str[10000];
        char output_str[10000];
        
        strcpy(string, "Description file for Individual 1\n\nHere are the passes in this individual, in order:\n\n");
        sprintf(fitness_num, "%f", fitness);
        strcpy(input_str, "");
        strcpy(output_str, "");

        FILE *input;
        FILE *output;
        char* line = NULL;
        size_t len = 0;
        size_t read;
        input = fopen(input_file, "r");
        if (input == NULL) {
            exit(EXIT_FAILURE);
        }
        while ((read = getline(&line, &len, input)) != -1) {
            strcat(input_str, line);
        }
        output = fopen(output_file, "r");
        if (output == NULL) {
            exit(EXIT_FAILURE);
        }
        while ((read = getline(&line, &len, output)) != -1) {
            strcat(output_str, line);
        }

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
        strcat(string, "\n\nHere is the input file before optimization was applied: \n\n###########################################################################################################################\n\n");
        strcat(string, input_str);
        strcat(string, "\n\n###########################################################################################################################\n\n");
        strcat(string, "And here is the file after optimization: \n\n###########################################################################################################################\n\n");
        strcat(string, output_str);
        strcat(string, "\n\n###########################################################################################################################\n\n");
        strcat(string, "The fitness of the individual is the time it takes to complete the testing script provided in seconds after the specified optimization passes are applied. Lower fitness is better.\n\nFitness of this individual: ");
        strcat(string, fitness_num);

        FILE* file_ptr = fopen(cache_file, "w");
        fputs(string, file_ptr);

        fclose(input);
        fclose(output);
        fclose(file_ptr);

        free(line);

    }

    return fitness;

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
 *  uint32_t - the fitness value for indiv
 *
 * EXAMPLE
 *
 * uint32_t fitness = fitness_top(node, true);
 *
 * SIDE-EFFECT
 *
 * none
 *
 */

uint32_t fitness_top(node_str* indiv, bool vis, char* test_file, bool cache, char* cache_file) {

    osaka_object_typ type = OBJECT_TYPE(indiv);

    if (type == 0) {
        return fitness_simple(indiv, vis);
    }
    else if (type == 1) {
        return fitness_assembler(indiv, vis);
    }
    else if (type == 2) {
        return fitness_osaka_string(indiv, vis);
    }
    else if (type == 3) {
        return fitness_llvm_pass(indiv, test_file, vis, cache, cache_file);
    }
	else if (type == 4) {
		return fitness_binary_up_to_512(indiv, vis);
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

}