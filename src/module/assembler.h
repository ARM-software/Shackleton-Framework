/*
 ============================================================================
 Name        : assembler.h
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
    
 Description : Base type for simple Assembler Objects
 ============================================================================
 */

#ifndef MODULE_ASSEMBLER_H_
#define MODULE_ASSEMBLER_H_

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"
#include "modules.h"
#include "simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/*
 * DATATYPES
 */

typedef enum    {
    ADD = 0,
    SUB,
    MUL,
    SDIV,
    MOV = 4
} instruction_typ;

typedef enum    {
    R0 = 0,
    R1,
    R2,
    R3
} register_name;

typedef struct object_assembler_str    {
    instruction_typ instr;
} object_assembler_str;

/*
 * MACROS
 */

#define MAXINSTRUCTIONS 4
#define PCSUSERREGS 3
#define ASSEMBLER_INSTRUCTION(s) s->instr

/*
 * ROUTINES
 */

object_assembler_str *assembler_createobject(void);

void assembler_randomizeobject(object_assembler_str *o);
void assembler_setobject(object_assembler_str *o, char* pass);

void assembler_printobject(object_assembler_str *o);

void assembler_describeobject(char* desc, object_assembler_str *o);

void assembler_deleteobject(object_assembler_str *o);

void assembler_writeobject(FILE *stream, object_assembler_str *o);

void *assembler_readobject(FILE *stream);

void *assembler_copyobject(object_assembler_str *o);

#endif /* MODULE_ASSEMBLER_H_ */
