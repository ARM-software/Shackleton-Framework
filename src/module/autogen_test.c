/*
 ============================================================================
 Name        : autogen_test.c
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

 /*
 * IMPORT
 */

 #include "../osaka/osaka.h"
 #include "autogen_test.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <assert.h>
 #include <string.h>

/*
 * ROUTINES
 */

uint32_t autogen_test_uid(void) {

    static uint32_t uid=0;
    return ++uid;

}

object_autogen_test_str *autogen_test_createobject(void) {

    object_autogen_test_str *o;

    o = malloc(sizeof(object_autogen_test_str));

    assert(o!=NULL);

    return o;

}

void autogen_test_randomizeobject(object_autogen_test_str *o) {

    // just a test class, please ignore;

}

void autogen_test_printobject(object_autogen_test_str *o) {

    printf("Just a test");

}

void autogen_test_describeobject(char* desc, object_autogen_test_str *o) {

    strcpy(desc, "Just a test");

}

void autogen_test_deleteobject(object_autogen_test_str *s) {

    assert(s!=NULL);
    free(s);

}

void autogen_test_writeobject(FILE *stream, object_autogen_test_str *o) {

    assert(stream!=NULL);
    fwrite(o, sizeof(object_autogen_test_str), 1, stream);

}

void *autogen_test_readobject(FILE *stream) {

    object_autogen_test_str *o;

    assert(stream!=NULL);

    o=malloc(sizeof(object_autogen_test_str));

    assert(o!=NULL);

    fread(o, sizeof(object_autogen_test_str), 1, stream);

    return o;

}

void *autogen_test_copyobject(object_autogen_test_str *o) {

    object_autogen_test_str *c;

    c=malloc(sizeof(object_autogen_test_str));

    assert(c!=NULL);

    memcpy((void *)c,(void *)o,sizeof(object_autogen_test_str));

    return c;

}