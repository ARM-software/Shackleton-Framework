/*
 ============================================================================
 Name        : utility.c
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
    
 Description : File for any functions that can be used
               across the project for making code more
               reusable
 ============================================================================
 */

#ifndef SUPPORT_UTILITY_H_
#define SUPPORT_UTILITY_H_

/*
 * IMPORT ...
 */

#include "cJSON.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*
 * DATATYPES
 */

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   str2int
 *
 * DESCRIPTION
 *
 *  Takes in a string and outputs the same value
 *  but now as an int
 *
 * PARAMETERS
 *
 *  uint32_t* out
 *  char* s
 *  uint32_t base
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * hstr2int(out, s, 10)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

str2int_errno str2int(uint32_t *out, char *s, uint32_t base);

/*
 * NAME
 *
 *   swap
 *
 * DESCRIPTION
 *
 *  Reverses a string
 *
 * PARAMETERS
 *
 *  char* temp1
 *  char* temp2
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * swap(temp, temp1)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void swap(char* temp1, char* temp2);

/*
 * NAME
 *
 *   reverse
 *
 * DESCRIPTION
 *
 *  Reverses a string
 *
 * PARAMETERS
 *
 *  char str[]
 *  uint32_t length
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * reverse(str, len)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void reverse(char str[], uint32_t length);

/*
 * NAME
 *
 *   itoa
 *
 * DESCRIPTION
 *
 *  Converts an uint32_t to a string
 *
 * PARAMETERS
 *
 *  uint32_t num
 *  char* str
 *  uint32_t base
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * itoa(3, number, 10)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

char* itoa(uint32_t num, char* str, uint32_t base);

/*
 * NAME
 *
 *   strupr
 *
 * DESCRIPTION
 *
 *  Converts a string to all upper case
 *
 * PARAMETERS
 *
 *  char* orig
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * strupr(orig)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void strupr(char* orig);

/*
 * NAME
 *
 *  getJSON
 *
 * DESCRIPTION
 *
 *  Creates a cJSON item from a filename given
 *
 * PARAMETERS
 *
 *  char* filename
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * cJSON *json = getJSON(filename);
 *
 * SIDE-EFFECT
 *
 *  mallocs, must be freed
 *
 */

cJSON* getJSON(char* filename);

/*
 * NAME
 *
 *  randomString
 *
 * DESCRIPTION
 *
 *  Creates a random string given a target length
 *
 * PARAMETERS
 *
 *  uint32_t length
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * char* new_string = randomString(10);
 *
 * SIDE-EFFECT
 *
 *  mallocs a new string that must be freed at some point
 *
 */

char *randomString(uint32_t length);

/*
 * NAME
 *
 *  set_params_from_file
 *
 * DESCRIPTION
 *
 *  Given a parameters file that is predetermined to be in 
 *  src/files/, will use the parameter values in that file
 *  to be the parameters for 
 *
 * PARAMETERS
 *
 *  uint32_t num_gen
 *  uint32_t pop_size
 *  uint32_t perc_cross
 *  uint32_t perc_mut
 *  uint32_t tourn_size
 *  bool vis
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * set_params_from_file(num_generations, num_population_size, percent_crossover, percent_mutation, tournament_size, visualization);
 *
 * SIDE-EFFECT
 *
 *  Resets all params within main based on the values in params file
 *
 */

void set_params_from_file(uint32_t *num_gen, uint32_t *pop_size, uint32_t *perc_cross, uint32_t *perc_mut, uint32_t *tourn_size, bool *vis);

#endif /* SUPPORT_UTILITY_H_ */