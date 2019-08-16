/*
 ============================================================================
 Name        : editor_tool/support/create.c
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

/*
 * IMPORT
 */

#include "create.h"

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

void header_module_h(char* name, char* header) {

    char header_beginning[15], header_ending[97];

    // Header is always constant outside of the name, so you can
    // prepare the preceding and following sections to the name
    strcpy(header_beginning, "/*\n * ");
    strcpy(header_ending, ".h\n\
 *\n\
 * Created on: <created_date>\n\
 * Author: Auto-generated .h file using Shackleton tool\n\
 */\n");

    // concatenate them all together
    strcpy(header, header_beginning);
    strcat(header, name);
    strcat(header, header_ending);

}

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

void header_module_c(char* name, char* c_header) {

    char c_header_beginning[15], c_header_ending[97];

    // Header is always constant outside of the name, so you can
    // prepare the preceding and following sections to the name
    strcpy(c_header_beginning, "/*\n * ");
    strcpy(c_header_ending, ".c\n\
 *\n\
 * Created on: <created_date>\n\
 * Author: Auto-generated .c file using Shackleton tool\n\
 */\n");

    // concatenate them all together
    strcpy(c_header, c_header_beginning);
    strcat(c_header, name);
    strcat(c_header, c_header_ending);

}

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

void create_includes_c(char* name, char* includes) {

    // includes for .c files will always be of this form
    strcpy(includes, "\n\
 #include <stdio.h>\n\
 #include <stdlib.h>\n\
 #include <stdint.h>\n\
 #include <assert.h>\n\
 #include <string.h>\n\n\
 #include \"../osaka/osaka.h\"\n\
 #include \"");
    strcat(includes, name);
    strcat(includes, ".h\"\n\n");

}

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

void create_includes_h(char* name, char* includes) {

    // includes for .h files will always be of this form
    strcpy(includes, "\n#ifndef MODULE_");
    strcat(includes, name);
    strcat(includes, "_H_\n#define MODULE_");
    strcat(includes, name);
    strcat(includes, "_H_\n\n\
#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <stdint.h>\n\
#include <assert.h>\n\n\
#include \"../osaka/osaka.h\"\n\n");

}

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

void create_new_structs(char* name, char* new_structs, cJSON* root) {

    // get top-level cJSON items
    cJSON* new_object = cJSON_GetObjectItem(root, "object");
    cJSON *new_params = cJSON_GetObjectItem(root, "params");

    // get variables for use in for loop
    char* object_name = cJSON_GetObjectItem(new_object, "name")->valuestring;
    uint32_t params_count = cJSON_GetArraySize(new_params);

    // clear new_structs variable for manipulation
    strcpy(new_structs, "");

    for (uint32_t j = 0; j < params_count; j++) {

        // get other needed cJSON items
        cJSON *new_param = cJSON_GetArrayItem(new_params, j);

        // get and prepare new variables
        char struct_full[1000];
        char curr_num[2];
        itoa(j, curr_num, 10);
        char* param_name = cJSON_GetObjectItem(new_param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(new_param, "type")->valuestring;

        // opening text of the new struct
        strcpy(struct_full, "typedef struct ");
        strcat(struct_full, name);
        strcat(struct_full, "_");
        strcat(struct_full, param_name);
        strcat(struct_full, " {\n\t");

        // create the internal variables of the struct
        strcat(struct_full, param_type);
        strcat(struct_full, " value;\n\tuint32_t value_index;\n\tbool constrained;\n\t");
        strcat(struct_full, param_type);
        strcat(struct_full, "* valid_values;\n\tint num_values;\n} ");

        // closing text of the struct
        strcat(struct_full, name);
        strcat(struct_full, "_");
        strcat(struct_full, param_name);
        strcat(struct_full, ";\n\n");

        // append to master variable for his method
        strcat(new_structs, struct_full);

    }

}

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
 * create_new_type(name, object, params_json);
 *
 * SIDE-EFFECT
 *
 *  alters the "object" parameter
 *
 */

void create_new_type(char* name, char* object, cJSON* root) {

    // get top-level cJSON objects
    cJSON *new_object = cJSON_GetObjectItem(root, "object");
    cJSON *new_params = cJSON_GetObjectItem(root, "params");

    // create top-level variables for use in for loop
    char* object_name = cJSON_GetObjectItem(new_object, "name")->valuestring;
    uint32_t params_count = cJSON_GetArraySize(new_params);

    // initialize object string with starting text
    strcpy(object, "typedef struct object_");
    strcat(object, name);
    strcat(object, "_str {\n");

    for (uint32_t j = 0; j < params_count; j++) {

        // get cJSON object specific to this param
        cJSON *new_param = cJSON_GetArrayItem(new_params, j);

        // declare and initialize variables for this param
        char param_full[100];
        char curr_num[2];
        itoa(j, curr_num, 10);
        char* param_name = cJSON_GetObjectItem(new_param, "name")->valuestring;

        // form string for this single param
        strcpy(param_full, "\t");
        strcat(param_full, name);
        strcat(param_full, "_");
        strcat(param_full, param_name);
        strcat(param_full, "* item");
        strcat(param_full, curr_num);
        strcat(param_full, ";\n");

        // append this param string to the master string
        strcat(object, param_full);

    }
    
    // add closing text of the new struct type
    strcat(object, "} object_");
    strcat(object, name);
    strcat(object, "_str;\n\n");

}

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

void create_macros(char* name, char* macros, cJSON* root) {

    cJSON *object = cJSON_GetObjectItem(root, "object");
    cJSON *json_params = cJSON_GetObjectItem(root, "params");
    cJSON *object_name_var = cJSON_GetObjectItem(object, "name");

    char* object_name = object_name_var->valuestring;
    uint32_t params_count = cJSON_GetArraySize(json_params);

    strcpy(macros, "// Auto-generated macros: ----------------------------------------------\n\n");

    for (uint32_t i = 0; i < params_count; i++) {

        // get cJSON object for this param
        cJSON *param = cJSON_GetArrayItem(json_params, i);

        // create and prepare known values for sting manipulation
        char curr_num[3];
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(param, "type")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;
        char* param_has_valid_values = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;
        itoa(i, curr_num, 10);
        strupr(param_macro_name);

        // macro strings to be filled and added to the master string
        char full_macro_name[200];
        char new_struct_macro[200];
        char new_value_macro[200];
        char new_value_index_macro[200];
        char new_constrained_macro[200];
        char new_valid_values_macro[200];
        char new_num_values_macro[200];

        // create string for macro name
        strcpy(full_macro_name, "");
        strcat(full_macro_name, name);
        strcat(full_macro_name, "_");
        strcat(full_macro_name, param_name);
        strupr(full_macro_name);

        // new macro for accessing the struct in full
        strcpy(new_struct_macro, "#define ");
        strcat(new_struct_macro, full_macro_name);
        strcat(new_struct_macro, "_STRUCT(s) s->item");
        strcat(new_struct_macro, curr_num);
        strcat(new_struct_macro, "\n");

        // new macro for accessing the value of the item
        strcpy(new_value_macro, "#define ");
        strcat(new_value_macro, full_macro_name);
        strcat(new_value_macro, "_");
        strcat(new_value_macro, param_macro_name);
        strcat(new_value_macro, "(s) s->item");
        strcat(new_value_macro, curr_num);
        strcat(new_value_macro, "->value\n");

        // new macro for getting the index of the value being used
        strcpy(new_value_index_macro, "#define ");
        strcat(new_value_index_macro, full_macro_name);
        strcat(new_value_index_macro, "_");
        strcat(new_value_index_macro, param_macro_name);
        strcat(new_value_index_macro, "_INDEX(s) s->item");
        strcat(new_value_index_macro, curr_num);
        strcat(new_value_index_macro, "->value_index\n");

        // new macro for accessing whether or not the item has valid values
        strcpy(new_constrained_macro, "#define ");
        strcat(new_constrained_macro, full_macro_name);
        strcat(new_constrained_macro, "_CONSTRAINED(s) s->item");
        strcat(new_constrained_macro, curr_num);
        strcat(new_constrained_macro, "->constrained\n");

        // new macro for accessing the array of valid values
        strcpy(new_valid_values_macro, "#define ");
        strcat(new_valid_values_macro, full_macro_name);
        strcat(new_valid_values_macro, "_VALID_VALUES(s) s->item");
        strcat(new_valid_values_macro, curr_num);
        strcat(new_valid_values_macro, "->valid_values\n");

        // new macro for accessing the number of valid values
        strcpy(new_num_values_macro, "#define ");
        strcat(new_num_values_macro, full_macro_name);
        strcat(new_num_values_macro, "_NUM_VALID_VALUES(s) s->item");
        strcat(new_num_values_macro, curr_num);
        strcat(new_num_values_macro, "->num_values\n");

        // add all new macros to the master macros string
        strcat(macros, new_struct_macro);
        strcat(macros, new_value_macro);
        strcat(macros, new_value_index_macro);
        strcat(macros, new_constrained_macro);
        strcat(macros, new_valid_values_macro);
        strcat(macros, new_num_values_macro);
        strcat(macros, "\n");

    }

    // epilogue
    strcat(macros, "// ----------------------------------------------------------------------\n\n");

}

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

void create_uid(char* name, char* methods) {

    // create_uid is always of a constant form
    strcpy(methods, "uint32_t ");
    strcat(methods, name);
    strcat(methods, "_uid(void) {\n\n    static uint32_t uid=0;\n    return ++uid;\n\n}\n\n");

}

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

void create_valid_value_methods(char* name, char* methods, cJSON* root) {

    // create initial char variables and initialize
    char curr_num[2];
    char num_valid_values_str[3];
    char curr_num2[3];
    char valueint_str[3];
    strcpy(curr_num, "");
    strcpy(num_valid_values_str, "");
    strcpy(curr_num2, "");
    strcpy(valueint_str, "");

    // get top-level cJSON objects
    cJSON *new_object = cJSON_GetObjectItem(root, "object");
    cJSON *new_params = cJSON_GetObjectItem(root, "params");

    // declare other needed variables
    char* object_name = cJSON_GetObjectItem(new_object, "name")->valuestring;
    uint32_t params_count = cJSON_GetArraySize(new_params);

    for (uint32_t j = 0; j < params_count; j++) {

        cJSON *new_param = cJSON_GetArrayItem(new_params, j);

        char* param_name = cJSON_GetObjectItem(new_param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(new_param, "type")->valuestring;
        char* param_constrained = cJSON_GetObjectItem(new_param, "has_valid_values")->valuestring;

        if (strcmp(param_constrained, "true") == 0 ) {

            cJSON *valid_values = cJSON_GetObjectItem(new_param, "values");

            uint32_t num_valid_values = cJSON_GetArraySize(valid_values);
            sprintf(num_valid_values_str, "%d", num_valid_values);
            char method[20000];
            char temp[10000];
            strcpy(temp, "");
            char full_macro_name[200];
            char* macro_name = cJSON_GetObjectItem(new_param, "macro_name")->valuestring;
            strupr(macro_name);

            // create starting string for new valid values method
            strcpy(method, "void ");
            strcat(method, name);
            strcat(method, "_");
            strcat(method, param_name);
            strcat(method, "_set_valid_values(object_");
            strcat(method, name);
            strcat(method, "_str* o) {\n\n\t");
            strcat(method, param_type);
            strcat(method, "* values = malloc(sizeof(");
            strcat(method, param_type);
            strcat(method, ") * ");
            strcat(method, num_valid_values_str);
            strcat(method, ");\n");

            // for every valid value, create an assignment to a new index
            // in the valud values array
            for (uint32_t k = 0; k < num_valid_values; k++) {

                sprintf(curr_num2, "%d", k);
                strcat(temp, "\tvalues[");
                strcat(temp, curr_num2);

                // need to determine if the var is an int or string type
                if (strcmp(param_type, "uint32_t") == 0 || strcmp(param_type, "int") == 0) {

                    cJSON* single_value = cJSON_GetArrayItem(valid_values, k);

                    uint32_t single_valueint = cJSON_GetObjectItem(single_value, "value")->valueint;
                    sprintf(valueint_str, "%d", single_valueint);

                    strcat(temp, "] = ");
                    strcat(temp, valueint_str);
                    strcat(temp, ";\n");

                }
                else {

                    cJSON *single_str = cJSON_GetArrayItem(valid_values, k);

                    strcat(method, "] = \"");
                    strcat(method, cJSON_GetObjectItem(single_str, "value")->valuestring);
                    strcat(method, "\"\n");

                }

            }

            // prepare full macro name
            strcpy(full_macro_name, "");
            strcat(full_macro_name, name);
            strcat(full_macro_name, "_");
            strcat(full_macro_name, param_name);
            strupr(full_macro_name);

            // append final lines to new method, move on to next method
            strcat(method, temp);
            strcat(method, "\n\t");
            strcat(method, full_macro_name);
            strcat(method, "_VALID_VALUES(o) = values;\n\t");
            strcat(method, full_macro_name);
            strcat(method, "_CONSTRAINED(o) = true;\n\t");
            strcat(method, full_macro_name);
            strcat(method, "_NUM_VALID_VALUES(o) = ");
            strcat(method, num_valid_values_str);
            strcat(method, ";\n\n\treturn;\n\n}\n\n");
            strcat(methods, method);

        }

    }

}

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

void create_createobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // prepare other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    // append beginning of createobject method to master methods string
    strcat(methods, "object_");
    strcat(methods, name);
    strcat(methods, "_str *");
    strcat(methods, name);
    strcat(methods, "_createobject(void) {\n\n    object_");
    strcat(methods, name);
    strcat(methods, "_str *o;\n");
    
    // for each param, create a new variable declaration
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\t");
        strcat(methods, name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, " *");
        strcat(methods, name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o;\n");

    }

    // add malloc line for entire object
    strcat(methods, "\n    o = malloc(sizeof(object_");
    strcat(methods, name);
    strcat(methods, "_str));\n");

    // for each param, create a new malloc line
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\t");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o = malloc(sizeof(");
        strcat(methods, name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "));\n");

    }

    // need assert statement for the object itself
    strcat(methods, "\n\tassert(o!=NULL);\n");

    // for each param, create a new assert statment to check not NULL
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\tassert(");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o!=NULL);\n");

    }

    // newline only for formatting reasons
    strcat(methods, "\n");

    // for each param, need line setting struct of top-level
    // object to the declared struct using a macro
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        char full_macro_name[200];
        strcpy(full_macro_name, "");
        strcat(full_macro_name, name);
        strcat(full_macro_name, "_");
        strcat(full_macro_name, param_name);
        strupr(full_macro_name);

        strcat(methods, "\t");
        strcat(methods, full_macro_name);
        strcat(methods, "_STRUCT(o) = ");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o;\n");

    }

    // newline only for formatting reasons
    strcat(methods, "\n");

    // for each param, either create call to their set_valid_values function
    // or set each item in its struct using individual macros
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* constrained = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;
        char* param_type = cJSON_GetObjectItem(param, "type")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;
        strupr(param_macro_name);

        char full_macro_name[100];
        strcpy(full_macro_name, name);
        strcat(full_macro_name, "_");
        strcat(full_macro_name, param_name);
        strupr(full_macro_name);

        strcat(methods, "\t");
        strcat(methods, full_macro_name);
        strcat(methods, "_");
        strcat(methods, param_macro_name);

        // default value for not being set is different depending on type
        if (strcmp(param_type, "uint32_t") == 0 || strcmp(param_type, "int") == 0) {
            strcat(methods, "(o) = -1;\n");
        }
        else {
            strcat(methods, "(o) = \"not set\";\n");
        }

        // constrained with valid values, can use set_valid_values method
        if (strcmp(constrained, "true") == 0) {

            strcat(methods, "\t");
            strcat(methods, full_macro_name);
            strcat(methods, "_");
            strcat(methods, param_macro_name);
            strcat(methods, "_INDEX(o) = -1;\n");

            strcat(methods, "\t");
            strcat(methods, name);
            strcat(methods, "_");
            strcat(methods, param_name);
            strcat(methods, "_set_valid_values(o);\n\n");

        }
        // no valid values, set everything manually in this method
        else {

            strcat(methods, "\t");
            strcat(methods, full_macro_name);
            strcat(methods, "_CONSTRAINED(o) = false;\n");

            strcat(methods, "\t");
            strcat(methods, full_macro_name);
            strcat(methods, "_VALID_VALUES(o) = NULL;\n");

            strcat(methods, "\t");
            strcat(methods, full_macro_name);
            strcat(methods, "_NUM_VALID_VALUES(o) = 0;\n\n");

        }

    }

    // return the new object created
    strcat(methods, "\treturn o;\n\n}\n\n");

}

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

void create_randomizeobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    strcat(methods, "void ");
    strcat(methods, name);
    strcat(methods, "_randomizeobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o) {\n\n");
    
    // each param gets its own print statement
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(param, "type")->valuestring;
        char* constrained = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;
        char full_macro[1000];

        // add full macro name, needs to be separate so it can be capitalized
        strcpy(full_macro, name);
        strcat(full_macro, "_");
        strcat(full_macro, param_name);
        strcat(full_macro, "_");

        strupr(full_macro);
        strupr(param_macro_name);

        char curr_num[2];
        itoa(i, curr_num, 10);

        if (strcmp(constrained, "true") == 0) {

            strcat(methods, "\tuint32_t num_valid_values");
            strcat(methods, curr_num);
            strcat(methods, " = ");
            strcat(methods, full_macro);
            strcat(methods, "NUM_VALID_VALUES(o);\n\tuint32_t new_index");
            strcat(methods, curr_num);
            strcat(methods, " = (uint32_t) (num_valid_values");
            strcat(methods, curr_num);
            strcat(methods, " * (rand() / (RAND_MAX + 1.0)));\n\t");
            strcat(methods, full_macro);
            strcat(methods, param_macro_name);
            strcat(methods, "_INDEX(o) = new_index");
            strcat(methods, curr_num);
            strcat(methods, ";\n\t");
            strcat(methods, full_macro);
            strcat(methods, param_macro_name);
            strcat(methods, "(o) = ");
            strcat(methods, full_macro);
            strcat(methods, "VALID_VALUES(o)[new_index");
            strcat(methods, curr_num);
            strcat(methods, "];\n\n");

        }
        else {

            if (strcmp(param_type, "uint32_t") == 0 || strcmp(param_type, "int") == 0) {

                strcat(methods, "\t");
                strcat(methods, full_macro);
                strcat(methods, param_macro_name);
                strcat(methods, "(o) = rand() / (RAND_MAX + 1.0);\n\n");

            }
            else {

                strcat(methods, "\tuint32_t rand_length");
                strcat(methods, curr_num);
                strcat(methods, " = (uint32_t) (20 * (rand() / (RAND_MAX + 1.0)));\n\t");
                strcat(methods, full_macro);
                strcat(methods, param_macro_name);
                strcat(methods, "(o) = randomString(rand_length");
                strcat(methods, curr_num);
                strcat(methods, ");\n\n");

            }

        }

    }

    // closing characters of method
    strcat(methods, "}\n\n");

}

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

void create_printobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    strcat(methods, "void ");
    strcat(methods, name);
    strcat(methods, "_printobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o) {\n\n");
    
    // each param gets its own print statement
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(param, "type")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;
        char full_macro[1000];

        strcat(methods, "\tprintf(\"");
        strcat(methods, param_macro_name);
        strcat(methods, " : %");
        
        // change internal of print statement to match type of parameter
        if (strcmp(param_type, "uint32_t") == 0 || strcmp(param_type, "int") == 0) {
            strcat(methods, "d");
        }
        else {
            strcat(methods, "s");
        }

        if (i != (num_params - 1)) {
            strcat(methods, " ; ");
        }

        strcat(methods, "\", ");

        // add full macro name, needs to be separate so it can be capitalized
        strcpy(full_macro, name);
        strcat(full_macro, "_");
        strcat(full_macro, param_name);
        strcat(full_macro, "_");
        strcat(full_macro, param_macro_name);
        strupr(full_macro);

        // finally add macro to the master methods string
        strcat(methods, full_macro);
        strcat(methods, "(o));\n");

    }

    // closing characters of method
    strcat(methods, "\n}\n\n");

}

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

void create_deleteobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);
    
    // starting text of the delete method
    strcat(methods, "void ");
    strcat(methods, name);
    strcat(methods, "_deleteobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *s) {\n\n\tassert(s!=NULL);\n\n");

    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_type = cJSON_GetObjectItem(param, "type")->valuestring;
        char* param_constrained = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;

        char full_macro[1000];
        strcpy(full_macro, name);
        strcat(full_macro, "_");
        strcat(full_macro, param_name);
        strupr(full_macro);

        // if a param is constrained, you must free its valid values
        if (strcmp(param_constrained, "true") == 0) {
            strcat(methods, "\tfree(");
            strcat(methods, full_macro);
            strcat(methods, "_VALID_VALUES(s));\n");
        }

        // always free the struct itself
        strcat(methods, "\tfree(");
        strcat(methods, full_macro);
        strcat(methods, "_STRUCT(s));\n");

    }

    // final free
    strcat(methods, "\n\tfree(s);\n\n}\n\n");

}

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

void create_writeobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    // beginning string of method, starts the fwrite statement
    strcat(methods, "void ");
    strcat(methods, name);
    strcat(methods, "_writeobject(FILE *stream, object_");
    strcat(methods, name);
    strcat(methods, "_str *o) {\n\n    assert(stream!=NULL);\n    fwrite(o, sizeof(object_");
    strcat(methods, name);
    strcat(methods, "_str), 1, stream);\n\n}\n\n");

}

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

void create_readobject(char* name, char* methods, cJSON* params_json) {
    
    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other neede variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    // starting text of method, starts declaring new objects to be created
    strcat(methods, "void *");
    strcat(methods, name);
    strcat(methods, "_readobject(FILE *stream) {\n\n    object_");
    strcat(methods, name);
    strcat(methods, "_str *o;\n");

    // each param needs its own struct declaration
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\t");
        strcat(methods, name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, " *");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o;\n");

    }

    // assert for main object
    strcat(methods, "\n\tassert(stream!=NULL);\n");
    strcat(methods, "\n\to = malloc(sizeof(object_");
    strcat(methods, name);
    strcat(methods, "_str));\n");

    // each param needs its own malloc line
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\t");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o = malloc(sizeof(");
        strcat(methods, name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "));\n");

    }

    // assert method for the main object
    strcat(methods, "\n\tassert(o!=NULL);\n");

    // each param needs its own assert line with the newly malloced object
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        strcat(methods, "\tassert(");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o!=NULL);\n");

    }

    // newline only for formatting reasons
    strcat(methods, "\n");

    // set struct variables of main object to newly declared objects using macros
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;

        char full_macro_name[200];
        strcpy(full_macro_name, "");
        strcat(full_macro_name, name);
        strcat(full_macro_name, "_");
        strcat(full_macro_name, param_name);
        strupr(full_macro_name);

        strcat(methods, "\t");
        strcat(methods, full_macro_name);
        strcat(methods, "_STRUCT(o) = ");
        strcat(methods, object_name);
        strcat(methods, "_");
        strcat(methods, param_name);
        strcat(methods, "_o;\n");

    }

    // start the fread statement
    strcat(methods, "\n\tfread(o, sizeof(object_");
    strcat(methods, name);
    strcat(methods, "_str), 1, stream);\n\n\treturn o;\n\n}\n\n");

}

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

void create_copyobject(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    // beginning text of copyobject method
    strcat(methods, "void *");
    strcat(methods, name);
    strcat(methods, "_copyobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o) {\n\n    object_");
    strcat(methods, name);
    strcat(methods, "_str *c = ");
    strcat(methods, name);
    strcat(methods, "_createobject();\n\n");
    
    // each param has the values from the original copied over
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_macro_name = cJSON_GetObjectItem(param, "macro_name")->valuestring;
        char* constrained = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;

        char full_macro_name[200];
        strcpy(full_macro_name, "");
        strcat(full_macro_name, name);
        strcat(full_macro_name, "_");
        strcat(full_macro_name, param_name);
        strcat(full_macro_name, "_");
        strupr(full_macro_name);
        strupr(param_macro_name);

        strcat(methods, "\t");

        if (strcmp(constrained, "true") == 0) {
            
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "_INDEX(c) = ");
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "_INDEX(o);\n\t");
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "(c) = ");
            strcat(methods, full_macro_name);
            strcat(methods, "VALID_VALUES(c)[");
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "_INDEX(o)];\n\n");

        }
        else {
            
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "(c) = ");
            strcat(methods, full_macro_name);
            strcat(methods, param_macro_name);
            strcat(methods, "(o);\n\n");

        }

    }

    // close memcpy and the entire copyobject_method
    strcat(methods, "\treturn c;\n\n}\n");

}

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

void create_methods_c(char* name, char* methods, cJSON* params_json) {

    // call methods in order of final appearance in the .c file, can be changed
    create_uid(name, methods);
    create_valid_value_methods(name, methods, params_json);
    create_createobject(name, methods, params_json);
    create_randomizeobject(name, methods, params_json);
    create_printobject(name, methods, params_json);
    create_deleteobject(name, methods, params_json);
    create_writeobject(name, methods, params_json);
    create_readobject(name, methods, params_json);
    create_copyobject(name, methods, params_json);

}

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
 * create_includes_h(name, methods, params_json)
 *
 * SIDE-EFFECT
 *
 *  alters the "methods" parameter
 *
 */

void create_methods_end_h(char* name, char* methods, cJSON* params_json) {

    // get top-level cJSON objects
    cJSON *object = cJSON_GetObjectItem(params_json, "object");
    cJSON *params = cJSON_GetObjectItem(params_json, "params");

    // get other needed variables
    char* object_name = cJSON_GetObjectItem(object, "name")->valuestring;
    uint32_t num_params = cJSON_GetArraySize(params);

    // clear the methods string so it is clean
    strcpy(methods, "");
    
    // for each param, if their values are constrained
    // a set_valid_values method must be declared
    for (uint32_t i = 0; i < num_params; i++) {

        cJSON* param = cJSON_GetArrayItem(params, i);
        char* param_name = cJSON_GetObjectItem(param, "name")->valuestring;
        char* param_constrained = cJSON_GetObjectItem(param, "has_valid_values")->valuestring;

        if (strcmp(param_constrained, "true") == 0) {
            strcat(methods, "void ");
            strcat(methods, name);
            strcat(methods, "_");
            strcat(methods, param_name);
            strcat(methods, "_set_valid_values(object_");
            strcat(methods, name);
            strcat(methods, "_str* o);\n\n");
        }

    }

    // createobject and start of randomizeobject
    strcat(methods, "object_");
    strcat(methods, name);
    strcat(methods, "_str *");
    strcat(methods, name);
    strcat(methods, "_createobject(void);\n\nvoid ");

    // randomizeobject and start of printobject
    strcat(methods, name);
    strcat(methods, "_randomizeobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o);\n\nvoid ");

    // printobject and start of deleteobject
    strcat(methods, name);
    strcat(methods, "_printobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o);\n\nvoid ");

    // deleteobject and start of writeobject
    strcat(methods, name);
    strcat(methods, "_deleteobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o);\n\nvoid ");

    // writeobject and start of readobject
    strcat(methods, name);
    strcat(methods, "_writeobject(FILE *stream, object_");
    strcat(methods, name);
    strcat(methods, "_str *o);\n\nvoid *");

    // readobject and start of copyobject
    strcat(methods, name);
    strcat(methods, "_readobject(FILE *stream);\n\nvoid *");

    // copyobject and end of entire module
    strcat(methods, name);
    strcat(methods, "_copyobject(object_");
    strcat(methods, name);
    strcat(methods, "_str *o);\n\n#endif /* MODULE_");
    strcat(methods, name);
    strcat(methods, "_H_ */");
}

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
 *  char* params_json
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

void create_c_file(char* name, cJSON* params_json) {

    printf("\nBeginning creation of new c file\n");

    // master string variables for .c file
    char filename[19]; 
    char header[200];
    char includes[200];
    char methods[5000];

    // form new filenamme to be created
    strcpy(filename, "../module/");
    strcat(filename, name);
    strcat(filename, ".c");

    // creates empty file and opens to write to
    FILE* file_ptr = fopen(filename, "w");

    // forms strings and load into master string vars
    header_module_c(name, header);
    create_includes_c(name, includes);
    create_methods_c(name, methods, params_json);
    
    // put strings into file
    fputs(header, file_ptr);
    fputs(includes, file_ptr);
    fputs(methods, file_ptr);

    // finally, close file
    fclose(file_ptr);

    printf("\nNew c file successfully created as %s\n", filename);

}

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

void create_h_file(char* name, cJSON* params_json) {

    // prepare master string vars
    char master[60000];
    char filename[19]; 
    char header[2000];
    char includes[5000];
    char new_structs[5000];
    char object[5000];
    char macros[5000];
    char methods[40000];

    // clear master for appending other strings
    strcpy(master, "");

    // prepare filname of new file to be created
    strcpy(filename, "../module/");
    strcat(filename, name);
    strcat(filename, ".h");

    // create new .h file and open for writing
    FILE* file_ptr = fopen(filename, "w");

    // load content into master strings
    header_module_h(name, header);
    create_includes_h(name, includes);
    create_new_structs(name, new_structs, params_json);
    create_new_type(name, object, params_json);
    create_macros(name, macros, params_json);
    create_methods_end_h(name, methods, params_json);

    // concatenate all sub-master strings into master
    strcat(master, header);
    strcat(master, includes);
    strcat(master, new_structs);
    strcat(master, object);
    strcat(master, macros);
    strcat(master, methods);

    // load master into file and close
    fputs(master, file_ptr);
    fclose(file_ptr);

}

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

void create_new_module(char* name, char* params_json) {

    cJSON *json = getJSON(params_json);

    //cJSON_Print(json);

    create_c_file(name, json);

    create_h_file(name, json);

    edit_existing_files(name);

    cJSON_Delete(json);

}