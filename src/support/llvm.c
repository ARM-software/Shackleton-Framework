/*
 ============================================================================
 Name        : llvm.c
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
    
 Description : Integration and use with LLVM is a main goal of this
               project. This file contains helper functions for using
               some of the main LLVM capabilities and for the fitness
               functions that will interface with LLVM

               Note: This file features use of the "system()" method,
               which presents a security risk when users can interact
               with the input to this method. Please use at your own risk
 ============================================================================
 */

/*
 * IMPORT ...
 */

#include "llvm.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   llvm_form_opt_command
 *
 * DESCRIPTION
 *
 *  Forms an optimization command of a set sequence of llvm optimization passes.
 *  The outputted command is ready to be run using the system() method or when
 *  copied into a terminal. There is an option of using an llvm_passes individual
 *  or to use a string array manually. The default is an osaka individual if it
 *  is specified
 *
 * PARAMETERS
 *
 *  node_str* indiv - if applicable, a link to the head of an individual of llvm_passes
 *  char** passes - alternatively, passes can be set manually in a string array and passed over
 *  uint32_t passes_size - size of string array if the array is being used
 *  char* file - the .ll file that the passes will be applied to
 *  char* command - the variable in the which the fully formed command will be stored
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_opt_command(my_indiv, NULL, 0, "hello.ll", command);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_opt_command(node_str* indiv, char** passes, uint32_t passes_size, char* input_file, char* output_file, char* command) {

    char* used_passes[100];

    if (indiv == NULL) {
        if (passes == NULL) {
            printf("No passes specified, return default call\n");
            //strcpy(command, "opt -print-before-all -print-after-all -S ");
            strcpy(command, "opt -S ");
        }
        else {
            if (passes_size == 0) {
                printf("No size set for passes array, please correctly set this value. Aborting code.\n");
                exit(0);
            }
            strcpy(command, "opt ");
            for (int i = 0; i < passes_size; i++) {
                used_passes[i] = passes[i];
            }
        }
    }
    else {
        if (OBJECT_TYPE(indiv) != LLVM_PASS) {
            printf("Object type used was incompatible with this function. Aborting code.");
            exit(0);
        }
        strcpy(command, "opt ");
        while(indiv != NULL) {
            object_llvm_pass_str* pass = (object_llvm_pass_str*)OBJECT(indiv);
            char* value = PASS(pass);
            strcat(command, value);
            strcat(command, " ");
            indiv = NEXT(indiv);
        }
        //strcat(command, "-print-before-all -print-after-all -S ");
        strcat(command, "-S ");
    }

    strcat(command, input_file);
    strcat(command, " -o ");
    strcat(command, output_file);

}

/*
 * NAME
 *
 *   llvm_form_run_command
 *
 * DESCRIPTION
 *
 *  Given a certain file, takes it in and creates a command
 *  that (when run) will execute that file directly. This specific method
 *  expects a .ll file
 *
 * PARAMETERS
 *
 *  char* file - the .c or .cpp file that we need to execute
 *  char* command - the variable that will hold the final command
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_run_command("hello.c", command);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_run_command(char* file, char* command) {

    char file_name[30];
    char base_name[60];

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    strcpy(base_name, "src/files/llvm/");

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(command, "llvm-as ");
    strcat(command, base_name);
    strcat(command, file_name);
    strcat(command, "_linked.ll && lli ");
    strcat(command, base_name);
    strcat(command, file_name);
    strcat(command, "_linked.bc");

}

/*
 * NAME
 *
 *   llvm_form_build_ll_command
 *
 * DESCRIPTION
 *
 *  Given a certain file, takes it in and creates a command
 *  that (when run) will execute that file directly. This specific method
 *  expects a .ll file
 *
 * PARAMETERS
 *
 *  char** src_files - array of files that are to be run
 *  char* file - the .c or .cpp file that we need to execute
 *  char* command - the variable that will hold the final command
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_build_ll_command(src_files, 2, test.cpp, command);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_build_ll_command(char** src_files, uint32_t num_src_files, char* test_file, char* command) {

    char src_file_name[30];
    char test_file_name[30];
    char base_name[60];
    char compiler[20];

    strcpy(test_file_name, test_file);
    char* p = strchr(test_file_name, '.');

    strcpy(base_name, "src/files/llvm/");

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    if (strstr(test_file, ".cpp") != NULL) {
        strcpy(compiler, "clang++");
    }
    else if (strstr(test_file, ".c") != NULL) {
        strcpy(compiler, "clang");
    }
    else {
        printf("File type of %s used with llvm is not supported.\n\nAborting code\n\n", test_file);
        exit(0);
    }

    strcpy(command, compiler);
    strcat(command, " -S -emit-llvm ");
    strcat(command, base_name);
    strcat(command, test_file);

    for (int i = 0; i < num_src_files; i++) {
        strcat(command, " && ");
        strcat(command, compiler);
        strcat(command, " -S -emit-llvm ");
        strcat(command, base_name);
        strcat(command, src_files[i]);
    }

    strcat(command, " && llvm-link ");
    strcat(command, test_file_name);
    strcat(command, ".ll ");

    for (int i = 0; i < num_src_files; i++) {
        strcpy(src_file_name, src_files[i]);
        char* p = strchr(src_file_name, '.');
        *p = 0;

        strcat(command, src_file_name);
        strcat(command, ".ll ");
    }

    strcat(command, "-S -o ");
    strcat(command, test_file_name);
    strcat(command, "_linked.ll && mv ");
    strcat(command, test_file_name);
    strcat(command, "_linked.ll ");
    strcat(command, base_name);

    strcat(command, " && rm ");
    strcat(command, test_file_name);
    strcat(command, ".ll ");

    for (int i = 0; i < num_src_files; i++) {
        strcpy(src_file_name, src_files[i]);
        char* p = strchr(src_file_name, '.');
        *p = 0;

        strcat(command, src_file_name);
        strcat(command, ".ll ");
    }

}

/*
 * NAME
 *
 *   llvm_form_exec_code_command
 *
 * DESCRIPTION
 *
 *  Given a certain .c or .cpp file, takes it in and creates a command
 *  that (when run) will execute that file directly. This specific method
 *  expects a single file, it does not link any files together
 *
 * PARAMETERS
 *
 *  char* file - the .c or .cpp file that we need to execute
 *  char* command - the variable that will hold the final command
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_exec_code_command("hello.c", command);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_exec_code_command(char* file, char* command) {

    char file_name[30];
    char base_name[60];
    char compiler[20];

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    strcpy(base_name, "src/files/llvm/");

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    if (strstr(file, ".cpp") != NULL) {
        strcpy(compiler, "clang++");
    }
    else if (strstr(file, ".c") != NULL) {
        strcpy(compiler, "clang");
    }
    else {
        printf("File type of %s used with llvm is not supported.\n\nAborting code\n\n", file);
        exit(0);
    }

    strcpy(command, compiler);
    strcat(command, " -S -emit-llvm ");
    strcat(command, base_name);
    strcat(command, file);
    strcat(command, " && mv ");
    strcat(command, file_name);
    strcat(command, ".ll ");
    strcat(command, base_name);
    strcat(command, " && llvm-as ");
    strcat(command, base_name);
    strcat(command, file_name);
    strcat(command, ".ll && lli ");
    strcat(command, base_name);
    strcat(command, file_name);
    strcat(command, ".bc");

}

/*
 * NAME
 *
 *   llvm_form_exec_code_command_from_ll
 *
 * DESCRIPTION
 *
 *  Given a certain .ll file, takes it in and creates a command
 *  that (when run) will execute that file directly. This specific method
 *  expects a single file, it does not link any files together. It also expects
 *  the full path to the .ll file to be provided as the input
 *
 * PARAMETERS
 *
 *  char* file - the .ll file that we need to execute
 *  char* command - the variable that will hold the final command
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_exec_code_command_from_ll("test.ll", command);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_exec_code_command_from_ll(char* file, char* command) {

    char file_name[30];
    char base_name[60];
    char compiler[20];

    strcpy(file_name, file);
    char* p = strchr(file_name, '.');

    if (!p) {
        printf("File must have valid extension such as .ll.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    if (strstr(file, ".ll") == NULL) {
        printf("File type of %s used with llvm is not supported.\n\nAborting code\n\n", file);
        exit(0);
    }

    strcpy(command, "llvm-as ");
    strcat(command, file);
    strcat(command, " && lli ");
    strcat(command, file_name);
    strcat(command, ".bc");

}

/*
 * NAME
 *
 *   llvm_form_test_command
 *
 * DESCRIPTION
 *
 *  Given an array of source files (.c or .cpp files) and a test
 *  file, it will create a terminal command that builds these files and 
 *  then runs the resulting executable bitcode
 *
 * PARAMETERS
 *
 *  char** src_files - the .c or .cpp files that we are testing
 *  uint32_t num_src_files - the number of files included in the source
 *  char* test_file - the file that contains the tests to be run
 *  char* build_command - the variable that will hold the final command for building/compiling
 *  char* run_command - the variable that will hold the final command for running the code
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  llvm_form_test_command(my_files, 3, "hello.c", bcommand, rcommand);
 *
 * SIDE-EFFECT
 *
 *  Alters the command variable with the final result
 *
 */

void llvm_form_test_command(char** src_files, uint32_t num_src_files, char* test_file, char* build_command, char* run_command) {

    llvm_form_build_ll_command(src_files, num_src_files, test_file, build_command);
    llvm_form_run_command(test_file, run_command);

}

/*
 * NAME
 *
 *   llvm_run_command
 *
 * DESCRIPTION
 *
 *  When given a single command, will run that command
 *
 * PARAMETERS
 *
 *  char* command - The command to be run
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  uint32_t result = llvm_run_command(command);
 *
 * SIDE-EFFECT
 *
 *  Interfaces with some terminal
 *
 */

uint32_t llvm_run_command(char* command) {

    return system(command) >> 8; // shift by 8 to get the correct error number

}