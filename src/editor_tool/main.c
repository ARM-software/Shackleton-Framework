/*
 ============================================================================
 Name        : editor_tool/main.c
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
    
 Description : Tool for adding additional types of items to the
               Shackleton framework. If errors occur upon auto-generation
               please diagnose these issues and alert the devloper
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

#include "support/create.h"

uint32_t main(uint32_t argc, char* argv[]) {

    printf("\nEntering the editor tool\n");

    // the first given argument will always be used as the name
    // for the new object type to be added
    if (argc == 1) {
        printf("You must pass the name of the json file used, without the json extension\n");
        return 0;
    }
    
    // copy over argv[1] into its own var
    char name[strlen(argv[1])];
    strcpy(name, argv[1]);

    char filename[100];
    strcpy(filename, "object_types/");
    strcat(filename, name);
    strcat(filename, ".json");

    printf("\nName for the file being used is %s\n", name);
    printf("\nThe json file being used is %s", filename);

    // all actual computation is done here
    create_new_module(name, filename);

    printf("\nNew object type successfully created.\n");

    return 0;

}