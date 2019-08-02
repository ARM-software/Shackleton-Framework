/*
 ============================================================================
 Name        : osaka_string.c
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

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"
#include "osaka_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*
 * ROUTINES
 */

uint32_t osaka_string_uid(void)  {
    
    static uint32_t uid=0;
    return ++uid;

}

void osaka_string_set_valid_values(object_osaka_string_str* o) {

    char** values = malloc(sizeof(char*) * 11);
    values[0] = "Mary";
    values[1] = "had";
    values[2] = "a";
    values[3] = "little";
    values[4] = "lamb";
    values[5] = "whose";
    values[6] = "fleece";
    values[7] = "was";
    values[8] = "white";
    values[9] = "as";
    values[10] = "snow";

    MY_STRING_VALID_VALUES(o) = values;
    CONSTRAINED(o) = true;
    NUM_VALID_VALUES(o) = 11;

    return;

}

object_osaka_string_str *osaka_string_createobject(void)    {

    object_osaka_string_str *o;
    my_string_struct *s;

    o = malloc(sizeof(object_osaka_string_str));
    s = malloc(sizeof(my_string_struct));

    assert(o!=NULL);
    assert(s!=NULL);

    MY_STRING_STRUCT(o) = s;
    //MY_STRING(o) = (char*)malloc(1024);
    MY_STRING(o) = "not set";
    
    osaka_string_set_valid_values(o);

    return o;

}

void osaka_string_randomizeobject(object_osaka_string_str* o) {
    
    if (CONSTRAINED(o)) {

        int num_valid_values = NUM_VALID_VALUES(o);
        int new_item = (int) (num_valid_values * (rand() / (RAND_MAX + 1.0)));
        MY_STRING(o) = MY_STRING_VALID_VALUES(o)[new_item];

    }
    else {
        
        int rand_length = (int) (20 * (rand() / (RAND_MAX + 1.0)));
        MY_STRING(o) = randomString(rand_length);

    }

}

void osaka_string_printobject(object_osaka_string_str *o)   {

    printf("string : %s", MY_STRING(o));

}

void osaka_string_describeobject(char* desc, object_osaka_string_str *o)   {

    strcpy(desc, "string : ");
    strcat(desc, MY_STRING(o));

}

void osaka_string_deleteobject(object_osaka_string_str *s)  {

    assert(s!=NULL);

    free(MY_STRING_VALID_VALUES(s));
    free(MY_STRING_STRUCT(s));
    free(s);

}

void osaka_string_writeobject(FILE *stream,object_osaka_string_str *o)  {

    assert(stream!=NULL);

    fwrite(o,sizeof(object_osaka_string_str) + sizeof(my_string_struct) + 1024,1,stream);

}

void *osaka_string_readobject(FILE *stream)   {

    object_osaka_string_str *o;
    my_string_struct *s;
    char* c;

    assert(stream!=NULL);


    o=malloc(sizeof(object_osaka_string_str));
    s=malloc(sizeof(my_string_struct));
    c=malloc(1024);
    assert(o!=NULL);
    assert(s!=NULL);
    assert(c!=NULL);

    fread(o,sizeof(object_osaka_string_str) + sizeof(my_string_struct) + 1024,1,stream);

    return o;

}

void *osaka_string_copyobject(object_osaka_string_str *o)   {

    object_osaka_string_str *c = osaka_string_createobject();

    MY_STRING(c) = MY_STRING(o);

    return c;

}