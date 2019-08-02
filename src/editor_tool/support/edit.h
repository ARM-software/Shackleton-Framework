/*
 ============================================================================
 Name        : editor_tool/support/edit.h
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
    
 Description : Main .h file for editing the existing files of Shackleton
               to add a new object type
 ============================================================================
 */

#ifndef EDITOR_TOOL_SUPPORT_EDIT_H_
#define EDITOR_TOOL_SUPPORT_EDIT_H_

/*
 * IMPORT
 */

#include "../../support/utility.h"
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
 *   edit_osaka_h_read
 *
 * DESCRIPTION
 *
 *  Helper for the edit_osaka_h method to read
 *  the original content and add to it
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_osaka_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_osaka_h_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_osaka_h
 *
 * DESCRIPTION
 *
 *  Takes the existing osaka.h file and creates a new
 *  version with all the existing information as well as 
 *  a new item in the osaka_object_type enum object
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_osaka_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the osaka.h file
 *
 */

void edit_osaka_h(char* name);

/*
 * NAME
 *
 *   edit_modules_h_read
 *
 * DESCRIPTION
 *
 *  Helper for the edit_modules_h method to read
 *  the original content and add to it
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_modules_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_modules_h_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_modules_h
 *
 * DESCRIPTION
 *
 *  Takes the existing modules.h file and creates a new
 *  version with all the existing information plus a new include
 *  to the .h file of the new type created
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_modules_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the modules.h file
 *
 */

void edit_modules_h(char* name);

/*
 * NAME
 *
 *   edit_modules_c_get_item
 *
 * DESCRIPTION
 *
 *  Creates the new item to be added to the 
 *  object_table_function array
 *
 * PARAMETERS
 *
 *  char* name
 *  char* item
 *  uint32_t index
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_modules_c_get_item(name, item, 4);
 *
 * SIDE-EFFECT
 *
 *  Edits the item variable
 *
 */

void edit_modules_c_get_item(char* name, char* item, uint32_t index);

/*
 * NAME
 *
 *   edit_modules_c_read
 *
 * DESCRIPTION
 *
 *  Helper for the edit_modules_c method to read
 *  the original content and add to it
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_modules_c_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_modules_c_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_modules_c
 *
 * DESCRIPTION
 *
 *  Takes the existing modules.c file and creates a new
 *  version with all the existing information plus the following:
 *      - new object_function_str in the object_table_function
 *        that has the new enum number, enum string (autogen_<name>),
 *        createobject, deleteobject, printobect, writeobject,
 *        readobject, and copyobject methods
 *      - increase of MAXTYPE by 1 
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_modules_c(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the modules.c file
 *
 */

void edit_modules_c(char* name);

/*
 * NAME
 *
 *   edit_add_build_statement
 *
 * DESCRIPTION
 *
 *  Creates build statement for new Shackleton object
 *  type and adds it to the new makefile
 *
 * PARAMETERS
 *
 *  char* name
 *  char* stmt
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_add_build_statement(name, stmt);
 *
 * SIDE-EFFECT
 *
 *  Adds new build statement to makefile
 *
 */

void edit_add_build_statement(char* name, char* stmt);

/*
 * NAME
 *
 *   edit_makefile_read
 *
 * DESCRIPTION
 *
 *  Helper for edit_makefile that reads the contents
 *  of the original makefile into a content string
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_makefile_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_makefile_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_makefile
 *
 * DESCRIPTION
 *
 *  Takes the existing makefile and creates a new
 *  version with all the existing information plus the following:
 *      - adds <name>.o to the OBJS declaration
 *      - adds a line for the command line argument for building
 *        the new object type
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_makefile(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the master makefile
 *
 */

void edit_makefile(char* name);

/*
 * NAME
 *
 *   edit_fitness_new_h_method
 *
 * DESCRIPTION
 *
 *  Creates the new method definition for fitness method
 *  for a new type
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 *  edit_fitness_new_h_method(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

void edit_fitness_new_h_method(char* name, char* content);

/*
 * NAME
 *
 *   edit_fitness_h_read
 *
 * DESCRIPTION
 *
 *  Helper for edit_fitness_h method that reads the contents
 *  of the original fitness.h file into a content string
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_fitness_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_fitness_h_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_fitness_h
 *
 * DESCRIPTION
 *
 *  Takes the existing fitness.h file, reads through it line
 *  by line, and inserts the new items needed for the new
 *  module type being created
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_fitness_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the fitness.h file
 *
 */

void edit_fitness_h(char* name);

/*
 * NAME
 *
 *   edit_fitness_c_read
 *
 * DESCRIPTION
 *
 *  Helper for edit_fitness_c method that reads the contents
 *  of the original fitness.c file into a content string
 *
 * PARAMETERS
 *
 *  char* name
 *  char* content
 *
 * RETURN
 *
 *  bool
 *
 * EXAMPLE
 *
 * edit_fitness_c_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_fitness_c_read(char* name, char* content);

/*
 * NAME
 *
 *   edit_fitness_c
 *
 * DESCRIPTION
 *
 *  Takes the existing fitness.c file, reads through it line
 *  by line, and inserts the new items needed for the new
 *  module type being created
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_fitness_c(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the fitness.c file
 *
 */

void edit_fitness_c(char* name);

/*
 * NAME
 *
 *   edit_existing_files
 *
 * DESCRIPTION
 *
 *  Master method that calls all other methods
 *  for editing the needed files for adding a new
 *  object type to Shackleton
 *
 * PARAMETERS
 *
 *  char* name
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * edit_existing_files(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the following files:
 *      - osaka/osaka.h
 *      - module/modules.c
 *      - module/modules.h
 *      - makefile
 *
 */

void edit_existing_files(char* name);

#endif /* EDITOR_TOOL_SUPPORT_EDIT_H_ */