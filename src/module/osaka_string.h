/*
 ============================================================================
 Name        : osaka_string.h
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
    
 Description : Test type that is a simple string from a nursery rhyme
 ============================================================================
 */

#ifndef MODULE_OSAKA_STRING_H_
#define MODULE_OSAKA_STRING_H_

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

typedef struct my_string_struct {
    char* value;
    bool constrained;
    char** valid_values;
    int num_values;
} my_string_struct;

typedef struct object_osaka_string_str {
    my_string_struct* item;
} object_osaka_string_str;

/*
 * MACROS
 */

#define MY_STRING_STRUCT(s) s->item
#define MY_STRING(s) s->item->value
#define CONSTRAINED(s) s->item->constrained
#define MY_STRING_VALID_VALUES(s) s->item->valid_values
#define NUM_VALID_VALUES(s) s->item->num_values

/*
 * ROUTINES
 */

void osaka_string_set_valid_values(object_osaka_string_str* o);

object_osaka_string_str *osaka_string_createobject(void);

void osaka_string_randomizeobject(object_osaka_string_str *o);
void osaka_string_setobject(object_osaka_string_str* o, char* pass);

void osaka_string_printobject(object_osaka_string_str *o);

void osaka_string_describeobject(char* desc, object_osaka_string_str *o);

void osaka_string_deleteobject(object_osaka_string_str *o);

void osaka_string_writeobject(FILE *stream,object_osaka_string_str *o);

void *osaka_string_readobject(FILE *stream);

void *osaka_string_copyobject(object_osaka_string_str *o);

//uint32_t osaka_string_fitnessobject(node_str *n);

#endif /* MODULE_OSAKA_STRING_H_ */
