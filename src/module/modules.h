/*
 ============================================================================
 Name        : modules.h
 Author      : Andrew Sloss, edited by Hannah Peeler
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
    
 Description : Top-level file for choosing object types for the Framework
 ============================================================================
 */

#ifndef MODULE_MODULES_H_
#define MODULE_MODULES_H_

/*
 * IMPORT ...
 */

#include "simple.h"
#include "assembler.h"
#include "osaka_string.h"
#include "llvm_pass.h"
#include "binary_up_to_512.h"

/*
 * DATATYPE
 */

typedef struct object_functions_str {
    uint32_t object_type;
    char name[25];
    object_simple_str *(*osaka_createobject)(void);
    void *(*osaka_randomizeobject)(void *);
    void (*osaka_deleteobject)(void *);
    void (*osaka_printobject)(void *);     
    void (*osaka_writeobject)(FILE *stream,void *);
    void *(*osaka_readobject)(FILE *stream);
    void *(*osaka_copyobject)(void *);
    //void (*osaka_describeobject)(char *, void *);         // Will be used for caching functionality, WIP
} object_functions_str;

/*
 * EXTERNS
 */

extern object_functions_str object_table_function[];
extern uint32_t MAXTYPE;

#endif /* MODULE_MODULES_H_ */