/*
 ============================================================================
 Name        : binary_up_to_512.c
 Author      : Autogenereted
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
    
 Description : Test binary type for the editor tool
 ============================================================================
 */

#ifndef MODULE_BINARY_UP_TO_512_H_
#define MODULE_BINARY_UP_TO_512_H_

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

typedef struct binary_up_to_512_number {
	uint32_t value;
	uint32_t value_index;
	bool constrained;
	uint32_t* valid_values;
	int num_values;
} binary_up_to_512_number;

typedef struct binary_up_to_512_binary {
	uint32_t value;
	uint32_t value_index;
	bool constrained;
	uint32_t* valid_values;
	int num_values;
} binary_up_to_512_binary;

typedef struct object_binary_up_to_512_str {
	binary_up_to_512_number* item0;
	binary_up_to_512_binary* item1;
} object_binary_up_to_512_str;

/*
 * MACROS
 */

// Auto-generated macros: ----------------------------------------------

#define BINARY_UP_TO_512_NUMBER_STRUCT(s) s->item0
#define BINARY_UP_TO_512_NUMBER_MY_NUMBER(s) s->item0->value
#define BINARY_UP_TO_512_NUMBER_MY_NUMBER_INDEX(s) s->item0->value_index
#define BINARY_UP_TO_512_NUMBER_CONSTRAINED(s) s->item0->constrained
#define BINARY_UP_TO_512_NUMBER_VALID_VALUES(s) s->item0->valid_values
#define BINARY_UP_TO_512_NUMBER_NUM_VALID_VALUES(s) s->item0->num_values

#define BINARY_UP_TO_512_BINARY_STRUCT(s) s->item1
#define BINARY_UP_TO_512_BINARY_MY_BINARY(s) s->item1->value
#define BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(s) s->item1->value_index
#define BINARY_UP_TO_512_BINARY_CONSTRAINED(s) s->item1->constrained
#define BINARY_UP_TO_512_BINARY_VALID_VALUES(s) s->item1->valid_values
#define BINARY_UP_TO_512_BINARY_NUM_VALID_VALUES(s) s->item1->num_values

// ----------------------------------------------------------------------

/*
 * ROUTINES
 */

void binary_up_to_512_binary_set_valid_values(object_binary_up_to_512_str* o);

object_binary_up_to_512_str *binary_up_to_512_createobject(void);

void binary_up_to_512_randomizeobject(object_binary_up_to_512_str *o);

void binary_up_to_512_printobject(object_binary_up_to_512_str *o);

void binary_up_to_512_describeobject(char* desc, object_binary_up_to_512_str *o);

void binary_up_to_512_deleteobject(object_binary_up_to_512_str *o);

void binary_up_to_512_writeobject(FILE *stream, object_binary_up_to_512_str *o);

void *binary_up_to_512_readobject(FILE *stream);

void *binary_up_to_512_copyobject(object_binary_up_to_512_str *o);

#endif /* MODULE_BINARY_UP_TO_512_H_ */