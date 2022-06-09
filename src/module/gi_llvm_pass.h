/*
 * gi_llvm_pass.h
 *
 * Created on: <created_date>
 * Author: Auto-generated .h file using Shackleton tool
 */

#ifndef MODULE_gi_llvm_pass_H_
#define MODULE_gi_llvm_pass_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "../osaka/osaka.h"

typedef struct gi_llvm_pass_patch_type {
	char* value;
	uint32_t value_index;
	bool constrained;
	char** valid_values;
	int num_values;
} gi_llvm_pass_patch_type;

typedef struct gi_llvm_pass_location {
	double value;
	uint32_t value_index;
	bool constrained;
	double* valid_values;
	int num_values;
} gi_llvm_pass_location;

typedef struct gi_llvm_pass_new_pass {
	char* value;
	uint32_t value_index;
	bool constrained;
	char** valid_values;
	int num_values;
} gi_llvm_pass_new_pass;

typedef struct object_gi_llvm_pass_str {
	gi_llvm_pass_patch_type* pass_type;
	gi_llvm_pass_location* location;
	gi_llvm_pass_new_pass* pass;
} object_gi_llvm_pass_str;

// Auto-generated macros: ----------------------------------------------

#define GI_LLVM_PASS_PATCH_TYPE_STRUCT(s) s->pass_type
#define GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(s) s->pass_type->value
#define GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(s) s->pass_type->value_index
#define GI_LLVM_PASS_PATCH_TYPE_CONSTRAINED(s) s->pass_type->constrained
#define GI_LLVM_PASS_PATCH_TYPE_VALID_VALUES(s) s->pass_type->valid_values
#define GI_LLVM_PASS_PATCH_TYPE_NUM_VALID_VALUES(s) s->pass_type->num_values

#define GI_LLVM_PASS_LOCATION_STRUCT(s) s->location
#define GI_LLVM_PASS_LOCATION_MY_LOCATION(s) s->location->value
#define GI_LLVM_PASS_LOCATION_MY_LOCATION_INDEX(s) s->location->value_index
#define GI_LLVM_PASS_LOCATION_CONSTRAINED(s) s->location->constrained
#define GI_LLVM_PASS_LOCATION_VALID_VALUES(s) s->location->valid_values
#define GI_LLVM_PASS_LOCATION_NUM_VALID_VALUES(s) s->location->num_values

#define GI_LLVM_PASS_NEW_PASS_STRUCT(s) s->pass
#define GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(s) s->pass->value
#define GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(s) s->pass->value_index
#define GI_LLVM_PASS_NEW_PASS_CONSTRAINED(s) s->pass->constrained
#define GI_LLVM_PASS_NEW_PASS_VALID_VALUES(s) s->pass->valid_values
#define GI_LLVM_PASS_NEW_PASS_NUM_VALID_VALUES(s) s->pass->num_values

// ----------------------------------------------------------------------

void gi_llvm_pass_patch_type_set_valid_values(object_gi_llvm_pass_str* o);

void gi_llvm_pass_new_pass_set_valid_values(object_gi_llvm_pass_str* o);

object_gi_llvm_pass_str *gi_llvm_pass_createobject(void);

void gi_llvm_pass_randomizeobject(object_gi_llvm_pass_str *o);

void gi_llvm_pass_setobject(object_gi_llvm_pass_str* o, char* pass);

void gi_llvm_pass_printobject(object_gi_llvm_pass_str *o);

void *gi_llvm_pass_describeobject(char* desc, object_gi_llvm_pass_str *o);

void gi_llvm_pass_deleteobject(object_gi_llvm_pass_str *o);

void gi_llvm_pass_writeobject(FILE *stream, object_gi_llvm_pass_str *o);

void *gi_llvm_pass_readobject(FILE *stream);

void *gi_llvm_pass_copyobject(object_gi_llvm_pass_str *o);

bool gi_llvm_pass_compareobject(object_gi_llvm_pass_str *o1, object_gi_llvm_pass_str *o2); 

char* gi_llvm_pass_get_type(object_gi_llvm_pass_str *o);
double gi_llvm_pass_get_loc(object_gi_llvm_pass_str *o);
char* gi_llvm_pass_get_pass(object_gi_llvm_pass_str *o);

char*** gi_llvm_set_default_level_strings(int* default_string_lengths, const int num_levels);
int* gi_llvm_default_level_string_lengths(const int num_levels);

#endif /* MODULE_gi_llvm_pass_H_ */