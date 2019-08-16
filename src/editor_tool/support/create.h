/*
 ============================================================================
 Name        : editor_tool/support/create.h
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
    
 Description : Main file for creating the new .c and .h files
               required for adding a new object type to Shackleton
 ============================================================================
 */

#ifndef EDITOR_TOOL_SUPPORT_CREATE_H_
#define EDITOR_TOOL_SUPPORT_CREATE_H_

/*
 * IMPORT
 */

#include "edit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   header_module_h
 *
 * DESCRIPTION
 *
 *  This function creates the header for use in new
 *  module .h files created for additional object types
 *
 * PARAMETERS
 *
 *  char* name
 *  char* header
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * header_module_h("test", header);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void header_module_h(char* name, char* header);

/*
 * NAME
 *
 *   header_module_c
 *
 * DESCRIPTION
 *
 *  This function creates the header for use in new
 *  module .c files created for additional object types
 *
 * PARAMETERS
 *
 *  char* name
 *  char* c_header
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * header_module_c("test", header);
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void header_module_c(char* name, char* c_header);

/*
 * NAME
 *
 *   create_includes_c
 *
 * DESCRIPTION
 *
 *  Creates the include blocks for a new
 *  module c file
 *
 * PARAMETERS
 *
 *  char* name
 *  char* includes
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_includes_c(name, includes)
 *
 * SIDE-EFFECT
 *
 *  alters the "includes" parameter
 *
 */



void create_includes_c(char* name, char* includes);

/*
 * NAME
 *
 *   create_includes_h
 *
 * DESCRIPTION
 *
 *  Creates the include blocks for a new
 *  module h file
 *
 * PARAMETERS
 *
 *  char* name
 *  char* includes
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_includes_h(includes)
 *
 * SIDE-EFFECT
 *
 *  alters the "includes" parameter
 *
 */

void create_includes_h(char* name, char* includes);

/*
 * NAME
 *
 *   create_new_structs
 *
 * DESCRIPTION
 *
 *  Creates supporting structs for any new parameters that are
 *  added by a user
 *
 * PARAMETERS
 *
 *  char* name
 *  char* new_structs
 *  cJSON* root
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_new_structs(name, new_structs, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "new_structs" parameter
 *
 */

void create_new_structs(char* name, char* new_structs, cJSON* root);

/*
 * NAME
 *
 *   create_new_type
 *
 * DESCRIPTION
 *
 *  Creates the new object type that will be used by
 *  this new module
 *
 * PARAMETERS
 *
 *  char* name
 *  char* object
 *  cJSON* root
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_new_type(name, object, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "object" parameter
 *
 */

void create_new_type(char* name, char* object, cJSON* root);

/*
 * NAME
 *
 *   create_macros
 *
 * DESCRIPTION
 *
 *  Creates the new macros for getting and setting
 *  each of the parameters in the new object
 *
 * PARAMETERS
 *
 *  char* name
 *  char* macros
 *  cJSON* root
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_new_type(name, macros, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "macros" parameter
 *
 */

void create_macros(char* name, char* macros, cJSON* root);

/*
 * NAME
 *
 *   create_uid
 *
 * DESCRIPTION
 *
 *  Helper to create a new uid method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_uid(name, methods)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_uid(char* name, char* methods);

/*
 * NAME
 *
 *   create_valid_value_methods
 *
 * DESCRIPTION
 *
 *  For any new param that has a set list of valid values,
 *  it creates and initializes that list within the method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* root
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_valid_value_methods(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_valid_value_methods(char* name, char* methods, cJSON* root);

/*
 * NAME
 *
 *   create_createobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new createobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_createobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_createobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_randomizeobject
 *
 * DESCRIPTION
 *
 *  Changes all parameters in an object to random values,
 *  either from the list of valid values or in a completely
 *  random way if that list does not apply
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_randomizeobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_randomizeobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_printobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new printobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_printobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_printobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_deleteobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new deleteobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_deleteobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_deleteobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_writeobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new writeobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_writeobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_writeobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_readobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new readobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_readobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_readobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_copyobject
 *
 * DESCRIPTION
 *
 *  Helper to create a new copyobject method
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_copyobject(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_copyobject(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_methods_c
 *
 * DESCRIPTION
 *
 *  Creates the method bodies for the .c file of
 *  a new object type
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_methods_c(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_methods_c(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_methods_end_h
 *
 * DESCRIPTION
 *
 *  Creates the method declarations for the .h file
 *  for a new module object type
 *
 * PARAMETERS
 *
 *  char* name
 *  char* methods
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_methods_end_h(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_methods_end_h(char* name, char* methods, cJSON* params_json);

/*
 * NAME
 *
 *   create_c_file
 *
 * DESCRIPTION
 *
 *  This function creates the new .c file for 
 *  a new object type
 *
 * PARAMETERS
 *
 *  char* name
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_c_file(name, params_json);
 *
 * SIDE-EFFECT
 *
 *  creates new .c file in the module/ directory
 *
 */

void create_c_file(char* name, cJSON* params_json);

/*
 * NAME
 *
 *   create_h_file
 *
 * DESCRIPTION
 *
 *  This function creates the new .h file for 
 *  a new object type
 *
 * PARAMETERS
 *
 *  char* name
 *  cJSON* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_h_file(name, params_json);
 *
 * SIDE-EFFECT
 *
 *  creates new .h file in the module/ directory
 *
 */

void create_h_file(char* name, cJSON* params_json);

/*
 * NAME
 *
 *   create_new_module
 *
 * DESCRIPTION
 *
 *  This function creates a new module for a given
 *  new object type
 *
 * PARAMETERS
 *
 *  char* name
 *  char* params_json
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * create_new_module(name, params_json);
 *
 * SIDE-EFFECT
 *
 *  creates new .c and .h file in the module/ directory
 *
 */

void create_new_module(char* name, char* params_json);

#endif /* EDITOR_TOOL_SUPPORT_CREATE_H_ */