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

/*
 * IMPORT ...
 */

 #include "../osaka/osaka.h"
 #include "binary_up_to_512.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <assert.h>
 #include <string.h>

/*
 * ROUTINES
 */

uint32_t binary_up_to_512_uid(void) {

    static uint32_t uid=0;
    return ++uid;

}

void binary_up_to_512_binary_set_valid_values(object_binary_up_to_512_str* o) {

	uint32_t* values = malloc(sizeof(uint32_t) * 11);
	values[0] = 0;
	values[1] = 1;
	values[2] = 2;
	values[3] = 4;
	values[4] = 8;
	values[5] = 16;
	values[6] = 32;
	values[7] = 64;
	values[8] = 128;
	values[9] = 256;
	values[10] = 512;

	BINARY_UP_TO_512_BINARY_VALID_VALUES(o) = values;
	BINARY_UP_TO_512_BINARY_CONSTRAINED(o) = true;
	BINARY_UP_TO_512_BINARY_NUM_VALID_VALUES(o) = 11;

	return;

}

object_binary_up_to_512_str *binary_up_to_512_createobject(void) {

    object_binary_up_to_512_str *o;
	binary_up_to_512_number *binary_up_to_512_number_o;
	binary_up_to_512_binary *binary_up_to_512_binary_o;

    o = malloc(sizeof(object_binary_up_to_512_str));
	binary_up_to_512_number_o = malloc(sizeof(binary_up_to_512_number));
	binary_up_to_512_binary_o = malloc(sizeof(binary_up_to_512_binary));

	assert(o!=NULL);
	assert(binary_up_to_512_number_o!=NULL);
	assert(binary_up_to_512_binary_o!=NULL);

	BINARY_UP_TO_512_NUMBER_STRUCT(o) = binary_up_to_512_number_o;
	BINARY_UP_TO_512_BINARY_STRUCT(o) = binary_up_to_512_binary_o;

	BINARY_UP_TO_512_NUMBER_MY_NUMBER(o) = -1;
	BINARY_UP_TO_512_NUMBER_CONSTRAINED(o) = false;
	BINARY_UP_TO_512_NUMBER_VALID_VALUES(o) = NULL;
	BINARY_UP_TO_512_NUMBER_NUM_VALID_VALUES(o) = 0;

	BINARY_UP_TO_512_BINARY_MY_BINARY(o) = -1;
	BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(o) = -1;
	binary_up_to_512_binary_set_valid_values(o);

	return o;

}

void binary_up_to_512_randomizeobject(object_binary_up_to_512_str *o) {

	BINARY_UP_TO_512_NUMBER_MY_NUMBER(o) = rand() / (RAND_MAX + 1.0);

	uint32_t num_valid_values1 = BINARY_UP_TO_512_BINARY_NUM_VALID_VALUES(o);
	uint32_t new_index1 = (uint32_t) (num_valid_values1 * (rand() / (RAND_MAX + 1.0)));
	BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(o) = new_index1;
	BINARY_UP_TO_512_BINARY_MY_BINARY(o) = BINARY_UP_TO_512_BINARY_VALID_VALUES(o)[new_index1];

}

// NOTE: still random
void binary_up_to_512_setobject(object_binary_up_to_512_str *o, char* pass) {

	BINARY_UP_TO_512_NUMBER_MY_NUMBER(o) = rand() / (RAND_MAX + 1.0);

	uint32_t num_valid_values1 = BINARY_UP_TO_512_BINARY_NUM_VALID_VALUES(o);
	uint32_t new_index1 = (uint32_t) (num_valid_values1 * (rand() / (RAND_MAX + 1.0)));
	BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(o) = new_index1;
	BINARY_UP_TO_512_BINARY_MY_BINARY(o) = BINARY_UP_TO_512_BINARY_VALID_VALUES(o)[new_index1];

}

void binary_up_to_512_printobject(object_binary_up_to_512_str *o) {

	printf("MY_NUMBER : %d ; ", BINARY_UP_TO_512_NUMBER_MY_NUMBER(o));
	printf("MY_BINARY : %d", BINARY_UP_TO_512_BINARY_MY_BINARY(o));

}

void binary_up_to_512_describeobject(char* desc, object_binary_up_to_512_str *o) {

    char my_number[5];
    char my_binary[5];

    itoa(BINARY_UP_TO_512_NUMBER_MY_NUMBER(o), my_number, 10);
    itoa(BINARY_UP_TO_512_BINARY_MY_BINARY(o), my_binary, 10);

    strcpy(desc, "MY_NUMBER : ");
    strcat(desc, my_number);
    strcat(desc, " ; MY_BINARY : ");
    strcat(desc, my_binary);

}

void binary_up_to_512_deleteobject(object_binary_up_to_512_str *s) {

	assert(s!=NULL);

	free(BINARY_UP_TO_512_NUMBER_STRUCT(s));
	free(BINARY_UP_TO_512_BINARY_VALID_VALUES(s));
	free(BINARY_UP_TO_512_BINARY_STRUCT(s));

	free(s);

}

void binary_up_to_512_writeobject(FILE *stream, object_binary_up_to_512_str *o) {

    assert(stream!=NULL);
    fwrite(o, sizeof(object_binary_up_to_512_str), 1, stream);

}

void *binary_up_to_512_readobject(FILE *stream) {

    object_binary_up_to_512_str *o;
	binary_up_to_512_number *binary_up_to_512_number_o;
	binary_up_to_512_binary *binary_up_to_512_binary_o;

	assert(stream!=NULL);

	o = malloc(sizeof(object_binary_up_to_512_str));
	binary_up_to_512_number_o = malloc(sizeof(binary_up_to_512_number));
	binary_up_to_512_binary_o = malloc(sizeof(binary_up_to_512_binary));

	assert(o!=NULL);
	assert(binary_up_to_512_number_o!=NULL);
	assert(binary_up_to_512_binary_o!=NULL);

	BINARY_UP_TO_512_NUMBER_STRUCT(o) = binary_up_to_512_number_o;
	BINARY_UP_TO_512_BINARY_STRUCT(o) = binary_up_to_512_binary_o;

	fread(o, sizeof(object_binary_up_to_512_str), 1, stream);

	return o;

}

void *binary_up_to_512_copyobject(object_binary_up_to_512_str *o) {

    object_binary_up_to_512_str *c = binary_up_to_512_createobject();

	BINARY_UP_TO_512_NUMBER_MY_NUMBER(c) = BINARY_UP_TO_512_NUMBER_MY_NUMBER(o);

	BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(c) = BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(o);
	BINARY_UP_TO_512_BINARY_MY_BINARY(c) = BINARY_UP_TO_512_BINARY_VALID_VALUES(c)[BINARY_UP_TO_512_BINARY_MY_BINARY_INDEX(o)];

	return c;

}
