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
        strcpy(command, "");
        strcat(command, "opt ");
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

    //printf("input_file: %s\n", input_file);
    //printf("output_file: %s\n", output_file);

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

    char file_name[300];
    char base_name[300];

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

// This function removes all the chars
// used in the string passed and will leave
// only the alphanumeric characters
int RemoveNonChars(char *string) {
	int length=0,i=0,j=0,k=0;

	length = strlen(string);

	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			if(!(string[j]>='a' && string[j]<='z') || (string[j]>='A' && string[j]<='Z'))
			{
				for(k=j;k<length;k++)
				{
					string[k] = string[k+1];
				}
				length--;
			}
		}
	}
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

void llvm_form_build_ll_command(char** src_files, uint32_t num_src_files, char* test_file, char* command, const char *id) {

    char src_file_name[100];
    char test_file_name[100];
    char base_name[100];
    char compiler[100];
    char junk_folder[100];
    char test_file_name_no_path[100];
    char src_file_name_no_path[100];

    strcpy(test_file_name, test_file);
    char* p = strchr(test_file_name, '.');

    strcpy(base_name, "src/files/llvm/");
    strcpy(junk_folder, "src/files/llvm/junk_output/");

    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(test_file_name_no_path, "");
    char *temp = strrchr(test_file_name, '/'); 
    if (!temp) {
        strcpy(test_file_name_no_path, test_file_name);
    } else strcpy(test_file_name_no_path, temp+1);

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
    strcat(command, " -o ");
    strcat(command, junk_folder);
    strcat(command, test_file_name_no_path);
    strcat(command, ".ll ");


    //printf("After adding the test file, the build command is this: %s\n", command);
    //printf("We now need to add %d source code files\n", num_src_files);

    /*for (int i = 0; i < num_src_files; i++) {
        //printf("Now adding each source file in turn\n");
        strcpy(src_file_name, src_files[i]);
        //printf("Here is what is being added: %s\n", src_file_name);
        strcat(command, " && ");
        strcat(command, compiler);
        strcat(command, " -S -emit-llvm ");
        strcat(command, base_name);
        //printf("Got this far. Gonna add: %s\n", src_file_name);
        strcat(command, src_file_name);
        printf("The command is now this: %s\n", command);
        printf("length of command is: %ld\n", strlen(command));
    }*/

    // Added 6/10/2021
    for (int i = 0; i < num_src_files; i++) {
        strcpy(src_file_name, src_files[i]);
        //printf("Here is what is being added: %s\n", src_file_name);
        char* p = strchr(src_file_name, '.');
        *p = 0;
        strcpy(src_file_name_no_path, "");
        char *t = strrchr(src_file_name, '/'); 
        if (!t) {
            strcpy(src_file_name_no_path, src_file_name);
        } else strcpy(src_file_name_no_path, t+1);

        strcat(command, "&& ");
        strcat(command, compiler);
        strcat(command, " -S -emit-llvm ");
        strcat(command, base_name);
        strcat(command, src_file_name);
        strcat(command, strstr(test_file, "."));
        strcat(command, " -o ");
        strcat(command, junk_folder);
        strcat(command, src_file_name_no_path);
        strcat(command, ".ll ");
        //printf("The command is now this: %s\n", command);
    }
    //printf("After adding all source files, the command is now this: %s\n", command);

    //printf("Starting the link part\n");
    strcat(command, " && llvm-link ");
    strcat(command, junk_folder);
    strcat(command, test_file_name_no_path);
    strcat(command, ".ll ");
    //printf("Done with the base link part\n");

    for (int i = 0; i < num_src_files; i++) {
        //printf("Now adding each source file to link in turn\n");
        strcpy(src_file_name, src_files[i]);
        char* p = strchr(src_file_name, '.');
        *p = 0;
        strcpy(src_file_name_no_path, "");
        char *t = strrchr(src_file_name, '/'); 
        if (!t) {
            strcpy(src_file_name_no_path, src_file_name);
        } else strcpy(src_file_name_no_path, t+1);

        strcat(command, junk_folder);
        strcat(command, src_file_name_no_path);
        strcat(command, ".ll ");
        //printf("Added to link file %s\n", src_files[i]);
    }


    strcat(command, "-S -o ");
    strcat(command, junk_folder);
    strcat(command, test_file_name_no_path);
    strcat(command, "_");
    strcat(command, id);
    strcat(command, "_linked"); //added 6/10/2021
    strcat(command, ".ll");
    /*strcat(command, "_linked.ll && mv ");
    strcat(command, base_name);
    strcat(command, test_file_name);
    strcat(command, "_linked.ll ");
    strcat(command, base_name);
    strcat(command, "junk_output/");*/

    /*printf("Adding removals\n");
    strcat(command, " && rm ");
    strcat(command, junk_folder);
    strcat(command, test_file_name_no_path);
    strcat(command, ".ll ");

    for (int i = 0; i < num_src_files; i++) {
        //printf("Added removals for src files one at a time\n");
        strcpy(src_file_name, src_files[i]);
        char* p = strchr(src_file_name, '.');
        *p = 0;
        strcpy(src_file_name_no_path, "");
        char *t = strrchr(src_file_name, '/'); 
        if (!t) {
            strcpy(src_file_name_no_path, src_file_name);
        } else strcpy(src_file_name_no_path, t+1);

        strcat(command, junk_folder);
        strcat(command, src_file_name_no_path);
        strcat(command, ".ll ");
        //printf("Added removal for src file: %s\n", src_files[i]);
    }*/

    printf("\n\nFinal build command: %s\n", command);

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

    char file_name[300];
    char base_name[300];
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

    char file_name[300];
    char base_name[300];
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

void llvm_form_test_command(char** src_files, uint32_t num_src_files, char* test_file, char* build_command, char* run_command, const char *id) {

    llvm_form_build_ll_command(src_files, num_src_files, test_file, build_command, id);
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

    return system(command); //>> 8; // shift by 8 to get the correct error number

}

/*
 * NAME
 *
 *   llvm_clean_up
 *
 * DESCRIPTION
 *
 *  clean up after a run by deleting generated files with unique id
 *
 * PARAMETERS
 *
 *  char* id - unique id of that run
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 *  uint32_t result = llvm_clean_up(command);
 *
 * SIDE-EFFECT
 *
 *  Interfaces with some terminal
 *
 */

uint32_t llvm_clean_up(char *file, const char* id, bool cache) {

    char clean_up_command[1000];
    char junk_dir[200];
    char file_name[200];
    char file_name_no_path[200];
    char base_file[300];
    
    strcpy(file_name, file);
    char* p = strchr(file_name, '.');
    if (!p) {
        printf("File must have valid extension such as .c or .cpp.\n\nAborting code\n\n");
        exit(0);
    }
    *p = 0;

    strcpy(file_name_no_path, "");
    char *temp = strrchr(file_name, '/'); 
    if (!temp) {
        strcpy(file_name_no_path, file_name);
    } else strcpy(file_name_no_path, temp+1);

    strcpy(junk_dir, "src/files/llvm/junk_output/");

    strcpy(base_file, junk_dir);
    strcat(base_file, file_name_no_path);
    strcat(base_file, "_");
    strcat(base_file, id);

    strcpy(clean_up_command, "");
    strcpy(clean_up_command, "rm ");
    strcat(clean_up_command, base_file);
    strcat(clean_up_command, "_linked.ll ");
    strcat(clean_up_command, base_file);
    strcat(clean_up_command, "_shackleton.ll ");
    strcat(clean_up_command, base_file);
    strcat(clean_up_command, "_shackleton.bc ");
    if (cache) {
        strcat(clean_up_command, base_file);
        strcat(clean_up_command, "_linked.bc ");
        strcat(clean_up_command, base_file);
        strcat(clean_up_command, "_opt_O*.ll ");
        strcat(clean_up_command, base_file);
        strcat(clean_up_command, "_opt_O*.bc ");
    }
    printf("Running clean up command: %s\n", clean_up_command);

    return system(clean_up_command); //>> 8; // shift by 8 to get the correct error number

}

