/*
 ============================================================================
 Name        : llvm_pass.c
 Author      : Hannah Peeler
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
    
 Description : LLVM optimization pass object type for use with the LLVM
                    integrated portion of the Shackleton Framework
 ============================================================================
 */

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"
#include "llvm_pass.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*
 * ROUTINES
 */

uint32_t llvm_pass_uid(void)  {
    
    static uint32_t uid=0;
    return ++uid;

}

void llvm_pass_set_valid_values(object_llvm_pass_str* o) {

    char** values = malloc(sizeof(char*) * 69);
    values[0] = "-aa-eval"; 
    values[1] = "-adce"; 
    values[2] = "-always-inline";
    values[3] = "-argpromotion";
    values[4] = "-basicaa"; 
    values[5] = "-break-crit-edges";
    values[6] = "-codegenprepare"; 
    values[7] = "-constmerge";
    values[8] = "-constprop"; 
    values[9] = "-da"; 
    values[10] = "-dce"; 
    values[11] = "-deadargelim";
    values[12] = "-die"; 
    values[13] = "-domfrontier";
    values[14] = "-domtree"; 
    values[15] = "-dse";
    values[16] = "-functionattrs"; 
    values[17] = "-globaldce"; 
    values[18] = "-globalopt";
    values[19] = "-gvn"; 
    values[20] = "-indvars"; 
    values[21] = "-inline";
    values[22] = "-instcombine"; 
    values[23] = "-instcount";
    values[24] = "-intervals"; 
    values[25] = "-ipconstprop"; 
    values[26] = "-ipsccp"; 
    values[27] = "-iv-users";
    values[28] = "-jump-threading";
    values[29] = "-lazy-value-info";
    values[30] = "-lcssa"; 
    values[31] = "-licm"; 
    values[32] = "-lint"; 
    values[33] = "-loop-deletion";
    values[34] = "-loop-extract"; 
    values[35] = "-loop-extract-single"; 
    values[36] = "-loop-reduce";
    values[37] = "-loop-rotate"; 
    values[38] = "-loop-simplify"; 
    values[39] = "-loop-unroll";
    values[40] = "-loop-unswitch"; 
    values[41] = "-loops"; 
    values[42] = "-loweratomic";
    values[43] = "-lowerinvoke"; 
    values[44] = "-lowerswitch";
    values[45] = "-mem2reg";
    values[46] = "-memcpyopt";
    values[47] = "-memdep";  
    values[48] = "-mergefunc";
    values[49] = "-mergereturn";
    values[50] = "-module-debuginfo"; 
    values[51] = "-partial-inliner"; 
    values[52] = "-postdomtree"; 
    //values[53] = "-print-dom-info"; 
    //values[54] = "-print-function";
    //values[55] = "-print-module";  
    values[53] = "-prune-eh";
    values[54] = "-reassociate";
    values[55] = "-reg2mem"; 
    values[56] = "-regions";
    values[57] = "-scalar-evolution"; 
    values[58] = "-sccp";
    values[59] = "-scev-aa"; 
    values[60] = "-simplifycfg"; 
    values[61] = "-sink"; 
    values[62] = "-sroa"; 
    values[63] = "-strip";
    values[64] = "-strip-dead-debug-info"; 
    values[65] = "-strip-dead-prototypes"; 
    values[66] = "-strip-debug-declare";
    values[67] = "-strip-nondebug"; 
    values[68] = "-tailcallelim";

    PASS_VALID_VALUES(o) = values;
    PASS_CONSTRAINED(o) = true;
    PASS_NUM_VALID_VALUES(o) = 69;

    return;

}

object_llvm_pass_str *llvm_pass_createobject(void)    {

    object_llvm_pass_str *o;
    pass_struct *s;

    o = malloc(sizeof(object_llvm_pass_str));
    s = malloc(sizeof(pass_struct));

    assert(o!=NULL);
    assert(s!=NULL);

    PASS_STRUCT(o) = s;
    PASS_INDEX(o) = -1;
    PASS(o) = "not set";
    
    llvm_pass_set_valid_values(o);

    return o;

}

void llvm_pass_randomizeobject(object_llvm_pass_str* o) {
    
    if (PASS_CONSTRAINED(o)) {

        int num_valid_values = PASS_NUM_VALID_VALUES(o);
        int new_item = (int) (num_valid_values * (rand() / (RAND_MAX + 1.0)));
        PASS_INDEX(o) = new_item;
        PASS(o) = PASS_VALID_VALUES(o)[new_item];

    }
    else {
        
        int rand_length = (int) (20 * (rand() / (RAND_MAX + 1.0)));
        PASS(o) = randomString(rand_length);

    }

}

void llvm_pass_printobject(object_llvm_pass_str *o)   {

    printf("pass : %s", PASS(o));

}

void llvm_pass_describeobject(char* desc, object_llvm_pass_str *o) {

    strcat(desc, PASS(o));

}

void llvm_pass_deleteobject(object_llvm_pass_str *s)  {

    assert(s!=NULL);

    free(PASS_VALID_VALUES(s));
    free(PASS_STRUCT(s));
    free(s);

}

void llvm_pass_writeobject(FILE *stream,object_llvm_pass_str *o)  {

    assert(stream!=NULL);

    fwrite(o,sizeof(object_llvm_pass_str),1,stream);

}

void *llvm_pass_readobject(FILE *stream)   {

    object_llvm_pass_str *o;
    pass_struct *s;

    assert(stream!=NULL);


    o=malloc(sizeof(object_llvm_pass_str));
    s=malloc(sizeof(pass_struct));
    assert(o!=NULL);
    assert(s!=NULL);

    fread(o,sizeof(object_llvm_pass_str),1,stream);

    return o;

}

void *llvm_pass_copyobject(object_llvm_pass_str *o)   {

    object_llvm_pass_str *c = llvm_pass_createobject();

    PASS_INDEX(c) = PASS_INDEX(o);
    PASS(c) = PASS_VALID_VALUES(c)[PASS_INDEX(c)];

    return c;

}