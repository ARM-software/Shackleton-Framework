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

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"
#include "simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*
 * ROUTINES
 */

uint32_t simple_uid(void)  {
    
    static uint32_t uid=0;
    return ++uid;

}

object_simple_str *simple_createobject(void)    {

    object_simple_str *o;

    o = malloc(sizeof(object_simple_str));

    assert(o!=NULL);

    SUBTYPE(o) = 1;
    INTEGER(o) = simple_uid();

    return o;

}

void simple_randomizeobject(object_simple_str *o) {

    SUBTYPE(o) = (int) rand();
    INTEGER(o) = (int) rand();

}

void simple_printobject(object_simple_str *o)   {

    printf("subtype : %d ; ",SUBTYPE(o));
    printf("integer : %d",INTEGER(o));

}

void simple_describeobject(char* desc, object_simple_str *o) {

    char subtype[5];
    char integer[5];

    itoa(SUBTYPE(o), subtype, 10);
    itoa(INTEGER(o), integer, 10);

    strcpy(desc, "subtype : ");
    strcat(desc, subtype);
    strcat(desc, " ; integer : ");
    strcat(desc, integer);

}

void simple_deleteobject(object_simple_str *s)  {

    assert(s!=NULL);

    free(s);

}

void simple_writeobject(FILE *stream,object_simple_str *o)  {

    assert(stream!=NULL);

    fwrite(o,sizeof(object_simple_str),1,stream);

}

void *simple_readobject(FILE *stream)   {

    object_simple_str *o;

    assert(stream!=NULL);

    o=malloc(sizeof(object_simple_str));
    assert(o!=NULL);

    fread(o,sizeof(object_simple_str),1,stream);

    return o;

}

void *simple_copyobject(object_simple_str *o)   {

    object_simple_str *c;

    c=malloc(sizeof(object_simple_str));
    assert(c!=NULL);

    memcpy((void *)c,(void *)o,sizeof(object_simple_str));

    return c;

}