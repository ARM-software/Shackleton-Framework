/*
 ============================================================================
 Name        : assembler.c
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

/*
 * IMPORT ...
 */

#include "assembler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <time.h>

/*
 * ROUTINES
 */

uint32_t assembler_uid(void)    {

    static uint32_t uid=0;

    return ++uid;

}

char *instruction_string[] =    {

    "add",
    "sub",
    "mul",
    "sdiv",
    "mov"

};

char *register_string[] =   {

    "r0",
    "r1",
    "r2",
    "r3"

};

char *assembler_instruction_string(instruction_typ i)    {

    assert(i<MAXINSTRUCTIONS);
    return instruction_string[i];

}

char *assembler_register_string(register_name r) {

    assert(r<PCSUSERREGS);
    return register_string[r];

}

object_assembler_str *assembler_createobject(void) {

    object_assembler_str *o;

    o = malloc(sizeof(object_assembler_str));

    assert(o!=NULL);

    ASSEMBLER_INSTRUCTION(o) = (int) (MAXINSTRUCTIONS * (rand() / (RAND_MAX + 1.0)));
    printf( "FORMING ASSEMBLER INSTRUCTION %s\n", assembler_instruction_string(ASSEMBLER_INSTRUCTION(o)));

    return o;

}

void assembler_randomizeobject(object_assembler_str *o) {

    int new_instr = (int) (MAXINSTRUCTIONS * (rand() / (RAND_MAX + 1.0)));
    ASSEMBLER_INSTRUCTION(o) = new_instr;

}

// NOTE: still random
void assembler_setobject(object_assembler_str *o, char* pass) {

    int new_instr = (int) (MAXINSTRUCTIONS * (rand() / (RAND_MAX + 1.0)));
    ASSEMBLER_INSTRUCTION(o) = new_instr;

}

void assembler_printobject(object_assembler_str *o)    {

    printf("instr : %s", assembler_instruction_string(ASSEMBLER_INSTRUCTION(o)));

}

void assembler_describeobject(char* desc, object_assembler_str *o) {

    strcpy(desc, "instr : ");
    strcat(desc, assembler_instruction_string(ASSEMBLER_INSTRUCTION(o)));

}

void assembler_deleteobject(object_assembler_str *s)   {

    assert(s!=NULL);
    free(s);

}

void assembler_writeobject(FILE *stream,object_assembler_str *o)   {

    assert(stream!=NULL);
    fwrite(o,sizeof(object_assembler_str),1,stream);

}

void *assembler_readobject(FILE *stream)    {

    object_assembler_str *o;
    assert(stream!=NULL);

    o=malloc(sizeof(object_assembler_str));
    assert(o!=NULL);

    fread(o,sizeof(object_assembler_str),1,stream);

    return o;

}

void *assembler_copyobject(object_assembler_str *o)    {

    object_assembler_str *c;

    c=malloc(sizeof(object_assembler_str));
    assert(c!=NULL);

    memcpy((void *)c,(void *)o,sizeof(object_assembler_str));

    return c;

}

void assembler_test_cycle(void) {}