/*
 ============================================================================
 Name        : modules.c
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

/*
 * IMPORT ...
 */

#include "modules.h"

/*
 * STATIC
 */

object_functions_str object_table_function[] =  {
    {
        0,
        "SIMPLE",
        simple_createobject,
        simple_randomizeobject,
        simple_deleteobject,
        simple_printobject,
        simple_writeobject,
        simple_readobject,
        simple_copyobject,
        //simple_describeobject,            // will be used in cache update, WIP
    },
    {
        1,
        "ASSEMBLER",
        assembler_createobject,
        assembler_randomizeobject,
        assembler_deleteobject,
        assembler_printobject,
        assembler_writeobject,
        assembler_readobject,
        assembler_copyobject,
        //assembler_describeobject,         // will be used in cache update, WIP
    },
    {
        2,
        "OSAKA_STRING",
        osaka_string_createobject,
        osaka_string_randomizeobject,
        osaka_string_deleteobject,
        osaka_string_printobject,
        osaka_string_writeobject,
        osaka_string_readobject,
        osaka_string_copyobject,
        //osaka_string_describeobject,      // will be used in cache update, WIP
    },
    {
        3,
        "LLVM_PASS",
        llvm_pass_createobject,
        llvm_pass_randomizeobject,
        llvm_pass_deleteobject,
        llvm_pass_printobject,
        llvm_pass_writeobject,
        llvm_pass_readobject,
        llvm_pass_copyobject,
        //llvm_pass_describeobject,         // will be used in cache update, WIP
    },
	{
		4,
		"BINARY_UP_TO_512",
		binary_up_to_512_createobject,
		binary_up_to_512_randomizeobject,
		binary_up_to_512_deleteobject,
		binary_up_to_512_printobject,
		binary_up_to_512_writeobject,
		binary_up_to_512_readobject,
		binary_up_to_512_copyobject,
        //binary_up_to_512_describeobject,  // will be used in cache update, WIP
	},
    {
        -1,
        "TERMINATOR",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        //NULL,                             // will be used in cache update, WIP
    }
};

uint32_t MAXTYPE=5;