/*
 ================================================================================
 Name        : main.c
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

 Description : Rough framework for inputting evolutionary
                             parameters for genetic programming
 ================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../support/llvm.h"
#include "sys/time.h"

int main(int argc, char* argv[]) {

    uint32_t num_runs = 20;

    char build_command[200];
    strcpy(build_command, "clang++ -S -emit-llvm test.cpp && clang++ -S -emit-llvm math.cpp && llvm-link test.ll math.ll -S -o my_test.ll && opt my_test.ll");
    system(build_command);

    char run_command[50];
    strcpy(run_command, "llvm-as my_test.ll && lli my_test.bc");

    struct timeval start, end; 

    double total_time = 0.0;
    double time_taken = 0.0;

    for (uint32_t runs = 0; runs < num_runs; runs++) {

        gettimeofday(&start, NULL);
        system(run_command);
        gettimeofday(&end, NULL);

        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

        total_time = total_time + time_taken;

    }

    time_taken = total_time / num_runs;
    printf("The average time taken without any optimization: %f\n\n", time_taken);

}