/*
 ============================================================================
 Name        : llvm_pass.h
 Author      : Hannah Peeler
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
    
 Description : LLVM optimization pass object type for use with the LLVM
                    integrated portion of the Shackleton Framework
 ============================================================================
 */

#ifndef MODULE_LLVM_PASS_H_
#define MODULE_LLVM_PASS_H_

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/*
 * DATATYPES
 */

typedef struct pass_struct {
    char* value;
    uint32_t value_index;
    bool constrained;
    char** valid_values;
    int num_values;
} pass_struct;

typedef struct object_llvm_pass_str {
    pass_struct* pass;
} object_llvm_pass_str;

/*
 * MACROS
 */

#define PASS_STRUCT(s) s->pass
#define PASS(s) s->pass->value
#define PASS_INDEX(s) s->pass->value_index
#define PASS_CONSTRAINED(s) s->pass->constrained
#define PASS_VALID_VALUES(s) s->pass->valid_values
#define PASS_NUM_VALID_VALUES(s) s->pass->num_values

/*
 * ROUTINES
 */
//void llvm_init_from_list();

void llvm_init_valid_values();

char*** llvm_set_default_level_strings(int* default_string_lengths, const int num_levels);  //added 8/13/21
int* llvm_default_level_string_lengths(const int num_levels);  //added 8/13/21

void llvm_pass_set_valid_values(object_llvm_pass_str* o);

object_llvm_pass_str *llvm_pass_createobject(void);

void llvm_pass_randomizeobject(object_llvm_pass_str *o);
void llvm_pass_setobject(object_llvm_pass_str* o, char* pass);  //added 8/13/21
int llvm_find_pass(char** values, int num_valid_values, char* pass);   //added 8/13/21

void llvm_pass_printobject(object_llvm_pass_str *o);

void llvm_pass_describeobject(char* desc, object_llvm_pass_str *o);

void llvm_pass_deleteobject(object_llvm_pass_str *o);

void llvm_pass_writeobject(FILE *stream,object_llvm_pass_str *o);

void *llvm_pass_readobject(FILE *stream);

void *llvm_pass_copyobject(object_llvm_pass_str *o);

bool llvm_pass_compareobject(object_llvm_pass_str *o1, object_llvm_pass_str *o2);

#endif /* MODULE_LLVM_PASS_H_ */
