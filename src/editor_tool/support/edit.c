/*
 ============================================================================
 Name        : editor_tool/support/edit.c
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
    
 Description : Main .c file for editing the existing files of Shackleton
               to add a new object type
 ============================================================================
 */

/*
 * IMPORT
 */

#include "edit.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *  edit_osaka_h_read
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
 *  bool - indicates success or failure
 *
 * EXAMPLE
 *
 *  edit_osaka_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_osaka_h_read(char* name, char* content) {

    // variables related to reading from the existing file
    FILE *osaka;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    // other variables needed, string vars especially
    char obj[50];
    char temp_name[100];

    // flag to keep track of going through items
    bool flag = false;
    uint32_t num = 0;

    // prepare the new name to be added to the enum
    strcpy(temp_name, name);
    strupr(temp_name);
    strcpy(obj, temp_name);

    // open already existing osaka.h file
    osaka = fopen("../osaka/osaka.h", "r");

    if (osaka == NULL) {
        exit(EXIT_FAILURE);
    }
    
    // read osaka.h line by line
    while ((read = getline(&line, &len, osaka)) != -1) {

        // type already exists, make no change to the file
        if (strstr(line, obj) != NULL) {

            free(line);
            fclose(osaka);
            return false;

        }
        // when we reach this line, means we are inside osaka_object_typ
        // and we need to be ready to add new type
        else if (strstr(line, "NOTSET = -1") != NULL) {
            flag = true;
        }
        // reached the end of osaka_object_typ lines,
        // prepare and add the new object type
        else if (strstr(line, "} osaka_object_typ;") != NULL) {

            char number[2];
            sprintf(number, "%d", num);
            //itoa(num, number, 10);

            strcat(content, "\t,");
            strcat(content, temp_name);
            strcat(content, " = ");
            strcat(content, number);
            strcat(content, "\n");

            flag = false;

        }
        else if (flag == true) {

            // increment num so the enum value when added is correct
            num = num + 1;

        }

        // when complete with choices, add the line from original file
        strcat(content, line);
    
    }
    
    // free line and close file, return true for success
    free(line);
    fclose(osaka);

    return true;

}

/*
 * NAME
 *
 *  edit_osaka_h
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
 *  edit_osaka_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the osaka.h file
 *
 */

void edit_osaka_h(char* name) {

    // declare and clear content string variable
    char content[100000];
    strcpy(content, "");

    // content is created here, false if could not add for some reason
    bool success = edit_osaka_h_read(name, content);

    // if created osaka_h was successful, go ahead with 
    // clearing and adding the updated content to osaka.h
    if (success) {

        FILE *new;
        new = fopen("../osaka/osaka.h", "w");
        fputs(content, new);
        fclose(new);

    }

}

/*
 * NAME
 *
 *  edit_modules_h_read
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
 *  edit_modules_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_modules_h_read(char* name, char* content) {

    // variables for reading through the file
    FILE *modules;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    // other needed variables to check for end conditions
    char obj[50];
    strcpy(obj, name);
    strcat(obj, ".h");
    bool flag = false;

    // open existing modules.h file
    modules = fopen("../module/modules.h", "r");

    if (modules == NULL) {
        exit(EXIT_FAILURE);
    }
    
    // read modules.h line by line
    while ((read = getline(&line, &len, modules)) != -1) {

        // read #include lines until they are done
        if (strstr(line, "#include ") != NULL) {

            flag = true;

            // type already exists, return false and make no change
            if (strstr(line, obj) != NULL) {

                free(line);
                fclose(modules);
                return false;

            }

        }
        // done with other includes, add the new one
        else if (flag) {

            char include[50];
            strcpy(include, "#include \"");
            strcat(include, name);
            strcat(include, ".h\"\n");
            strcat(content, include);
            flag = false;

        }

        // add line to master content variable
        strcat(content, line);

    }
    
    // free line and close file, return true for success
    free(line);
    fclose(modules);

    return true;

}

/*
 * NAME
 *
 *  edit_modules_h
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
 *  edit_modules_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the modules.h file
 *
 */

void edit_modules_h(char* name) {

    // declare and clear content string to be edited
    char content[5000];
    strcpy(content, "");

    // content created here, returns false if failed for some reason
    bool success = edit_modules_h_read(name, content);

    // if creating content for modules.h was success,
    // clear modules.h and load it with the updated content
    if (success) {

        FILE *new;
        new = fopen("../module/modules.h", "w");
        fputs(content, new);
        fclose(new);

    }

}

/*
 * NAME
 *
 *  edit_modules_c_get_item
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
 *  edit_modules_c_get_item(name, item, 4);
 *
 * SIDE-EFFECT
 *
 *  Edits the item variable
 *
 */

void edit_modules_c_get_item(char* name, char* item, uint32_t index) {

    // declare and prepare all variables
    char num[4];
    sprintf(num, "%d", index);
    //itoa(index, num, 10);
    char temp_name[100];
    strcpy(temp_name, name);
    strupr(temp_name);

    // each osaka_object_type has an item in the object
    // functions table, so it's added here
    strcpy(item, "\t{\n\t\t");
    strcat(item, num);
    strcat(item, ",\n\t\t\"");
    strcat(item, temp_name);
    strcat(item, "\",\n\t\t");
    strcat(item, name);
    strcat(item, "_createobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_randomizeobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_deleteobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_printobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_writeobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_readobject,\n\t\t");
    strcat(item, name);
    strcat(item, "_copyobject,\n\t},\n");

}

/*
 * NAME
 *
 *  edit_modules_c_read
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
 *  edit_modules_c_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_modules_c_read(char* name, char* content) {

    // variables needed for reading through file
    FILE *modules;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    // declare and initialize needed variables
    uint32_t num = 0;
    char content_temp[1000];
    char item[300];
    strcpy(item, "");
    strcpy(content_temp, "");
    char temp_name[100];
    strcpy(temp_name, "\"");
    strcat(temp_name, name);
    strcat(temp_name, "\",");
    strupr(temp_name);
    // in_array 
    bool in_array = false;
    bool done = false;

    // open modules.c to read through
    modules = fopen("../module/modules.c", "r");

    if (modules == NULL) {
        exit(EXIT_FAILURE);
    }

    // read modules.c line by line
    while ((read = getline(&line, &len, modules)) != -1) {

        // all items have been added, so add each line encountered
        if (done) {

            // unless, you're at the maxtype line, this is updated with the new incremented value
            if (strstr(line, "MAXTYPE=") != NULL) {

                num = num + 1;
                char number[2];
                sprintf(number, "%d", num);
                //itoa(num, number, 10);
                strcat(content, "uint32_t MAXTYPE=");
                strcat(content, number);
                strcat(content, ";");

            }
            // else, just add the line as is
            else {

                strcat(content, line);

            }
        }
        // inside the object functions table array
        else if (in_array) {

            // type already exists, return failure and make no change
            if (strstr(line, temp_name) != NULL) {

                free(line);
                fclose(modules);
                return false;

            }
            // found terminator, add new type before adding terminator and set done to true
            else if (strstr(line, "TERMINATOR") != NULL) {

                edit_modules_c_get_item(name, item, num);
                strcat(content, item);
                strcat(content, content_temp);
                strcat(content, line);
                done = true;

            }
            // got through but wasn't terminator, add lines cached to this point
            else if (strstr(line, "},") != NULL) {

                strcat(content_temp, line);
                strcat(content, content_temp);
                strcpy(content_temp, "");
                num = num + 1;

            }
            // just add the line as is
            else {

                strcat(content_temp, line);

            }
        }
        // start of needed array, need to look for where to add so set in_array to true
        else if (strstr(line, "{") != NULL) {

            strcat(content, line);
            in_array = true;

        }
        // just add the line as is
        else {
            
            strcat(content, line);

        }

    }

    // free line and close, return true for success
    free(line);
    fclose(modules);

    return true;

}

/*
 * NAME
 *
 *  edit_modules_c
 *
 * DESCRIPTION
 *
 *  Takes the existing modules.c file and creates a new
 *  version with all the existing information plus the following:
 *      - new object_function_str in the object_table_function
 *        that has the new enum number, enum string (<name>),
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
 *  edit_modules_c(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the modules.c file
 *
 */

void edit_modules_c(char* name) {

    // create and clear the master content variable
    char content[10000];
    strcpy(content, "");

    // where new content is creates, returns false if failed for some reason
    bool success = edit_modules_c_read(name, content);

    // if creating new content was successful,
    // clear modules.c and load with new content
    if (success) {

        FILE *new;
        new = fopen("../module/modules.c", "w");
        fputs(content, new);
        fclose(new);

    }

}

/*
 * NAME
 *
 *  edit_add_build_statement
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
 *  edit_add_build_statement(name, stmt);
 *
 * SIDE-EFFECT
 *
 *  Adds new build statement to makefile
 *
 */

void edit_add_build_statement(char* name, char* stmt) {

    // new build statement is constant form and
    // is added after all other autogenerated types
    strcpy(stmt, "$(OBJDIR)/");
    strcat(stmt, name);
    strcat(stmt, ".o : $(SRCDIR)/module/");
    strcat(stmt, name);
    strcat(stmt, ".c $(SRCDIR)/module/");
    strcat(stmt, name);
    strcat(stmt, ".h\n\tcc -c $(SRCDIR)/module/");
    strcat(stmt, name);
    strcat(stmt, ".c -o $@\n\n");

}

/*
 * NAME
 *
 *  edit_makefile_read
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
 *  edit_makefile_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_makefile_read(char* name, char* content) {

    // variables for reading the file
    FILE *stream;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    char obj[100];
    strcpy(obj, name);
    strcat(obj, ".o");

    // open the makefile for reading
    stream = fopen("../../makefile", "r");

    if (stream == NULL) {
        exit(EXIT_FAILURE);
    }

    // read makefile line by line
    while ((read = getline(&line, &len, stream)) != -1) {

        // need to add .o file for this file
        if (strstr(line, "OBJS :=") != NULL) {

            // will need to sort through OBJS line using " " as a delimiter
            char* temp;
            char delim[] = " ";
            
            temp = strtok(line, delim);

            while (temp != NULL) {

                // type already exists, return failure and make no change
                if (strcmp(temp, obj) == 0) {

                    free(line);
                    fclose(stream);
                    return false;

                }
                // always add new .o file just before evolution.o
                else if (strcmp(temp, "evolution.o") == 0) {

                    strcat(content, obj);
                    strcat(content, " ");

                }

                // still add things as usual at the end, regardless of other choices
                strcat(content, temp);
                strcat(content, " ");
                temp = strtok(NULL, delim);

            }

        }
        else if (strstr(line, "$(OBJDIR)/evolution.o") != NULL) {

            // always add the new build statement just before that for evolution.o
            char stmt[500];
            edit_add_build_statement(name, stmt);
            strcat(content, stmt);
            strcat(content, line);

        }
        else {

            // else, just add the line as is
            strcat(content, line);

        }

    }

    // free line and close file, return true for success
    free(line);
    fclose(stream);

    return true;

}

/*
 * NAME
 *
 *  edit_makefile
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
 *  edit_makefile(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the master makefile
 *
 */

void edit_makefile(char* name) {

    // create and clear master content string
    char content[10000];
    strcpy(content, "");

    // content is created here, returns false if it fails for some reason
    bool success = edit_makefile_read(name, content);

    // if content for new makefile is successful, go ahead and
    // clear makefile and load with the new content
    if (success) {

        FILE *new;
        new = fopen("../makefile", "w");
        fputs(content, new);
        fclose(new);

    }

}

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

void edit_fitness_new_h_method(char* name, char* content) {

    // create the block comment that describes the new method
    strcat(content, "/*\n");
    strcat(content, " * NAME\n");
    strcat(content, " *\n");
    strcat(content, " *   fitness_");
    strcat(content, name);
    strcat(content, "\n *\n");
    strcat(content, " * DESCRIPTION\n");
    strcat(content, " *\n");
    strcat(content, " * Calculates the fitness value specifically for an ");
    strcat(content, name);
    strcat(content, "\n * inidividual, currently is only a default. AUTO-GENERATED\n");
    strcat(content, " *\n");
    strcat(content, " * PARAMETERS\n");
    strcat(content, " *\n");
    strcat(content, " *  node_str* indiv - the individual that is to be evaluated\n");
    strcat(content, " *  bool vis - whether or not visualization is enabled\n");
    strcat(content, " *\n");
    strcat(content, " * RETURN\n");
    strcat(content, " *\n");
    strcat(content, " *  uint32_t - the fitness value for indiv\n");
    strcat(content, " *\n");
    strcat(content, " * EXAMPLE\n");
    strcat(content, " *\n");
    strcat(content, " * uint32_t ");
    strcat(content, name);
    strcat(content, "_fit = fitness_");
    strcat(content, name);
    strcat(content, "(node, true);\n");
    strcat(content, " *\n");
    strcat(content, " * SIDE-EFFECT\n");
    strcat(content, " *\n");
    strcat(content, " * none\n");
    strcat(content, " *\n");
    strcat(content, " */\n\n");

    // add the actual method definition
    strcat(content, "uint32_t fitness_");
    strcat(content, name);
    strcat(content, "(node_str* indiv, bool vis);\n\n");

}

/*
 * NAME
 *
 *  edit_fitness_h_read
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
 *  edit_fitness_h_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_fitness_h_read(char* name, char* content) {

    // variables needed for reading through file
    FILE *fitness;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    // declare and initialize needed variables
    char desc_temp[1000];
    strcpy(desc_temp, "");

    // booleans for checking end conditions
    bool at_function_pointers = false;
    bool pointer_added = false;
    bool at_new_method = false;
    bool done = false;

    // need to form a check for if type already exists
    char fp_stmt[200];
    strcpy(fp_stmt, "uint32_t (*fpfitness_");
    strcat(fp_stmt, name);
    strcat(fp_stmt, ")");

    // open fitness.h to read through
    fitness = fopen("../evolution/fitness.h", "r");

    if (fitness == NULL) {
        exit(EXIT_FAILURE);
    }

    // read fitness.h line by line
    while ((read = getline(&line, &len, fitness)) != -1) {

        // everything new has been added, copy rest as is
        if (done) {

            strcat(content, line);

        }
        // pointer declaration was added, now need to add new method
        else if (pointer_added) {

            // reached end of method that wasn't fitness_top, add as is
            if (strstr(line, "/*") != NULL) {
                
                strcat(content, desc_temp);
                strcpy(desc_temp, line);

            }
            // add new method just before the fitness_top method
            else if (strstr(line, "fitness_top")) {

                edit_fitness_new_h_method(name, content);
                strcat(content, desc_temp);
                strcat(content, line);
                done = true;

            }
            // save everything until an end condition in case it needs to be
            // added after the new method has been appended
            else {

                strcat(desc_temp, line);
            
            }

        }
        // searching for the function pointer declarations
        else if (strstr(line, "uint32_t (*") != NULL) {

            // type already exists, return failure and make no change
            if (strstr(line, fp_stmt) != NULL) {

                free(line);
                fclose(fitness);
                return false;

            }

            // found function pointers, set flag to true
            strcat(desc_temp, line);
            at_function_pointers = true;

        }
        // just add the line as is
        else {
            
            // this means we have gone through all existing function pointers
            // so we need to append the new one
            if (at_function_pointers) {
                
                strcat(content, desc_temp);
                strcpy(desc_temp, "");
                strcat(content, "uint32_t (*fpfitness_");
                strcat(content, name);
                strcat(content, ")(node_str *n, bool vis);\n\n");

                // set flag to move on to next searching element
                pointer_added = true;
                at_function_pointers = false;

            }
            else {

                // save in desc_temp in case it needs to be appended after a new portion
                strcat(desc_temp, line);

            }

        }

    }

    // free line and close, return true for success
    free(line);
    fclose(fitness);

    return true;

}

/*
 * NAME
 *
 *  edit_fitness_h
 *
 * DESCRIPTION
 *
 *  Takes the existing fitness.h file, reads through it line
 *  by line, and inserts the new items needed for the new
 *  module type being created, namely:
 *      - adding a new function pointer declaration at
 *        the top of the file
 *      - creating a new method definition for the method
 *        specific to the new object type
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
 *  edit_fitness_h(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the fitness.h file
 *
 */

void edit_fitness_h(char* name) {

    // declare and clear content string variable
    char content[100000];
    strcpy(content, "");

    // content is created here, false if could not add for some reason
    bool success = edit_fitness_h_read(name, content);

    // if created fitness_h was successful, go ahead with 
    // clearing and adding the updated content to fitness.h
    if (success) {

        FILE *new;
        new = fopen("../evolution/fitness.h", "w");
        fputs(content, new);
        fclose(new);

    }

}

/*
 * NAME
 *
 *  edit_fitness_new_c_method
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
 *  edit_fitness_new_c_method(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

void edit_fitness_new_c_method(char* name, char* content) {

    // create the block comment for the new methof being added
    strcat(content, "/*\n");
    strcat(content, " * NAME\n");
    strcat(content, " *\n");
    strcat(content, " *   fitness_");
    strcat(content, name);
    strcat(content, "\n *\n");
    strcat(content, " * DESCRIPTION\n");
    strcat(content, " *\n");
    strcat(content, " * Calculates the fitness value specifically for an ");
    strcat(content, name);
    strcat(content, "\n * inidividual, currently is only a default. AUTO-GENERATED\n");
    strcat(content, " *\n");
    strcat(content, " * PARAMETERS\n");
    strcat(content, " *\n");
    strcat(content, " *  node_str* indiv - the individual that is to be evaluated\n");
    strcat(content, " *  bool vis - whether or not visualization is enabled\n");
    strcat(content, " *\n");
    strcat(content, " * RETURN\n");
    strcat(content, " *\n");
    strcat(content, " *  uint32_t - the fitness value for indiv\n");
    strcat(content, " *\n");
    strcat(content, " * EXAMPLE\n");
    strcat(content, " *\n");
    strcat(content, " * uint32_t ");
    strcat(content, name);
    strcat(content, "_fit = fitness_");
    strcat(content, name);
    strcat(content, "(node, true);\n");
    strcat(content, " *\n");
    strcat(content, " * SIDE-EFFECT\n");
    strcat(content, " *\n");
    strcat(content, " * none\n");
    strcat(content, " *\n");
    strcat(content, " */\n\n");

    // add the default method itself, will always return 100 if left unchanged
    strcat(content, "uint32_t fitness_");
    strcat(content, name);
    strcat(content, "(node_str* indiv, bool vis) {\n\n\treturn 100;\n\n}\n\n");

}

/*
 * NAME
 *
 *  edit_fitness_c_read
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
 *  edit_fitness_c_read(name, content);
 *
 * SIDE-EFFECT
 *
 *  Edits the content variable
 *
 */

bool edit_fitness_c_read(char* name, char* content) {

    // variables needed for reading through file
    FILE *fitness;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    // declare and initialize needed variables
    char desc_temp[50000];
    strcpy(desc_temp, "");
    uint32_t curr_num = 0;

    // booleans for checking end conditions
    bool at_fpfitness_defines = false;
    bool conditional_added = false;
    bool adding_conditional = false;
    bool done = false;

    // open fitness.c to read through
    fitness = fopen("../evolution/fitness.c", "r");

    if (fitness == NULL) {
        exit(EXIT_FAILURE);
    }

    // read fitness.c line by line
    while ((read = getline(&line, &len, fitness)) != -1) {

        // all new items have been added, just use the rest as is
        if (done) {

            strcat(content, line);

        }
        // at the fpfitness initialization lines in fitness_setup
        else if (at_fpfitness_defines) {

            // for each fpfitness line, add as is 
            if (strstr(line, "fpfitness") != NULL) {
                
                strcat(content, line);

            }
            // until you've saved them all, now add new initialization for new item
            else {

                strcat(content, "\tfpfitness_");
                strcat(content, name);
                strcat(content, " = &fitness_");
                strcat(content, name);
                strcat(content, ";\n");
                strcat(content, line);
                done = true;

            }

        }
        // condition within fitness_top was successfully added
        // now search for the function pointer initializations in fitness_setup
        else if (conditional_added) {

            // within the fitness_setup method
            if (strstr(line, "fpfitness") != NULL) {
                
                at_fpfitness_defines = true;

            }

            strcat(content, line);

        }
        // inside fitness_top method
        else if (adding_conditional) {

            // if reach the else {, this is where new conditional
            // statement needs to be added
            if (strstr(line, "else {") != NULL) {

                char number[2];
                sprintf(number, "%d", curr_num);

                strcat(content, "\telse if (type == ");
                strcat(content, number);
                strcat(content, ") {\n\t\treturn fitness_");
                strcat(content, name);
                strcat(content, "(indiv, vis);\n\t}\n");
                strcat(content, line);

                // successfully added, moving on
                conditional_added = true;

            }
            else {

                // if a closing bracket is found, we had a conditional
                // for an existing type, increment curr_num to keep track
                if (strstr(line, "}") != NULL) {

                    curr_num = curr_num + 1;

                }

                strcat(content, line);

            }

        }
        // looking first for the fitness_top method,
        // new method will be added just before it
        else {
            
            // fitness_top method found, add new method and then add info 
            // gotten up to this point for the fitness_top method
            if (strstr(line, "fitness_top") != NULL) {
                
                edit_fitness_new_c_method(name, content);
                strcat(content, desc_temp);
                strcpy(desc_temp, "");

                // next, will add conditional within fitness_top
                adding_conditional = true;

            }
            // this means a method other than fitness_top was found
            // and fully processed, add to content and clear desc_temo
            else if (strstr(line, "/*") != NULL) {

                strcat(content, desc_temp);
                strcpy(desc_temp, line);

            }
            // type already exists, return failure and make no change
            else if (strstr(line, name) != NULL) {

                free(line);
                fclose(fitness);
                return false;

            }
            // keep track of information as you go
            // in case it needs to be added after new content
            else {

                strcat(desc_temp, line);

            }

        }

    }

    // free line and close, return true for success
    free(line);
    fclose(fitness);

    //return true, indicates success
    return true;

}

/*
 * NAME
 *
 *  edit_fitness_c
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
 *  edit_fitness_c(name);
 *
 * SIDE-EFFECT
 *
 *  Edits the fitness.c file
 *
 */

void edit_fitness_c(char* name) {

    // declare and clear content string variable
    char content[100000];
    strcpy(content, "");

    // content is created here, false if could not add for some reason
    bool success = edit_fitness_c_read(name, content);

    // if created fitness_c was successful, go ahead with 
    // clearing and adding the updated content to fitness.c
    if (success) {

        FILE *new;
        new = fopen("../evolution/fitness.c", "w");
        fputs(content, new);
        fclose(new);

    }

}

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
 *      - evolution/fitness.h
 *      - evolution/fitness.c
 *
 */

void edit_existing_files(char* name) {

    edit_osaka_h(name);
    edit_modules_h(name);
    edit_modules_c(name);
    edit_makefile(name);
    edit_fitness_h(name);
    edit_fitness_c(name);

}