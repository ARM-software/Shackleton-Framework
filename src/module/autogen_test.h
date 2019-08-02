/*
 ============================================================================
 Name        : autogen_test.h
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
    
 Description : Test type for the editor tool
 ============================================================================
 */

#ifndef MODULE_AUTOGEN_TEST_H_
#define MODULE_AUTOGEN_TEST_H_

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

typedef struct test_test_params_number {
	uint32_t value;
	bool constrained;
	uint32_t* valid_values;
	int num_values;
} test_test_params_number;

typedef struct test_test_params_binary {
	uint32_t value;
	bool constrained;
	uint32_t* valid_values;
	int num_values;
} test_test_params_binary;

typedef struct object_autogen_test_str {
	test_test_params_number* item0;
	test_test_params_binary* item1;
} object_autogen_test_str;

/*
 * MACROS
 */

// Auto-generated macros: ----------------------------------------------

#define TEST_NUMBER_STRUCT(s) s->item0
#define TEST_NUMBER_MY_NUMBER(s) s->item0->value
#define TEST_NUMBER_CONSTRAINED(s) s->item0->constrained
#define TEST_NUMBER_VALID_VALUES(s) s->item0->valid_values
#define TEST_NUMBER_NUM_VALUES(s) s->item0->num_values

#define TEST_BINARY_STRUCT(s) s->item1
#define TEST_BINARY_MY_BINARY(s) s->item1->value
#define TEST_BINARY_CONSTRAINED(s) s->item1->constrained
#define TEST_BINARY_VALID_VALUES(s) s->item1->valid_values
#define TEST_BINARY_NUM_VALUES(s) s->item1->num_values

// ----------------------------------------------------------------------

/*
 * ROUTINES
 */

object_autogen_test_str *autogen_test_createobject(void);

void autogen_test_randomizeobject(object_autogen_test_str *o);

void autogen_test_printobject(object_autogen_test_str *o);

void autogen_test_describeobject(char* desc, object_autogen_test_str *o);

void autogen_test_deleteobject(object_autogen_test_str *o);

void autogen_test_writeobject(FILE *stream, object_autogen_test_str *o);

void *autogen_test_readobject(FILE *stream);

void *autogen_test_copyobject(object_autogen_test_str *o);

#endif /* MODULE_AUTOGEN_TEST_H_ */