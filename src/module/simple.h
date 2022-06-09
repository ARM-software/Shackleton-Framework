/*
 ============================================================================
 Name        : simple.c
 Author      : Andrew Sloss
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
    
 Description : Simple type, used as a test for verification
 ============================================================================
 */

#ifndef MODULE_SIMPLE_H_
#define MODULE_SIMPLE_H_

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

typedef struct object_simple_str    {
    uint32_t subtype;
    uint32_t i;
} object_simple_str;

/*
 * MACROS
 */

#define SUBTYPE(s) s->subtype
#define INTEGER(s) s->i

/*
 * ROUTINES
 */

object_simple_str *simple_createobject(void);

void simple_randomizeobject(object_simple_str *o);
void simple_setobject(object_simple_str *o, char* pass);

void simple_printobject(object_simple_str *o);

void simple_describeobject(char* desc, object_simple_str *o);

void simple_deleteobject(object_simple_str *o);

void simple_writeobject(FILE *stream,object_simple_str *o);

void *simple_readobject(FILE *stream);

void *simple_copyobject(object_simple_str *o);

//uint32_t simple_fitnessobject(node_str *n);

#endif /* MODULE_SIMPLE_H_ */
