#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "acotsp.h"

// Testcases
const int num_testcases = 1;
char files[4][50] = {"src/files/llvm/aco/lin318.tsp"};
/*const int num_testcases = 4;
char files[4][50] = {
                         "src/files/llvm/aco/d198.tsp",
                         "src/files/llvm/aco/lin318.tsp",
                         "src/files/llvm/aco/pcb442.tsp",
                         "src/files/llvm/aco/kroA100.tsp"
                     };*/
//const char* files[] = {"lin318.tsp", "kroA100.tsp", "d198.tsp"};
//const char* const files[] = {"kroA100.tsp"};
 
// Driver method
int main() {
    //printf("\n");
    //printf("In testing code, running all %d testcase(s)\n", num_testcases);
    int arg_num = 3;
    for (int i = 0; i < num_testcases; i++) {
        char file_to_test[100] = "";
        strcpy(file_to_test, "");
        strcat(file_to_test, files[i]);
        //printf("Currently testing this file: %s", file_to_test);
        char* args[3] = {"none", "--tsplibfile", file_to_test};
        acotsp(arg_num, args);
        //printf("\n\n\n\n\n\n\n\n\n\n DONE \n\n\n\n\n\n\n\n\n\n");
    }

    /*
    for (int i = 0; i < n; i++) {
        printf("Running test case with file %s\n", files[i]);
        char run_command[100] = "";
        strcpy(run_command, ".src/files/llvm/asotsp/acotsp --tsplibfile src/files/llvm/asotsp/");
        strcat(run_command, files[i]);
        printf("Here is the run command: %s\n", run_command);
        int a = system(run_command);
        printf("Result of running the command: %d\n", a);
    }
    */
    //printf("\n");
}
