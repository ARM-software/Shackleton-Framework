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

    char** values = malloc(sizeof(char*) * 68);
    //values[0] = "-aa-eval"; 
    values[0] = "-adce"; 
    values[1] = "-always-inline";
    values[2] = "-argpromotion";
    values[3] = "-basicaa"; 
    values[4] = "-break-crit-edges";
    values[5] = "-codegenprepare"; 
    values[6] = "-constmerge";
    values[7] = "-constprop"; 
    values[8] = "-da"; 
    values[9] = "-dce"; 
    values[10] = "-deadargelim";
    values[11] = "-die"; 
    values[12] = "-domfrontier";
    values[13] = "-domtree"; 
    values[14] = "-dse";
    values[15] = "-functionattrs"; 
    values[16] = "-globaldce"; 
    values[17] = "-globalopt";
    values[18] = "-gvn"; 
    values[19] = "-indvars"; 
    values[20] = "-inline";
    values[21] = "-instcombine"; 
    values[22] = "-instcount";
    values[23] = "-intervals"; 
    values[24] = "-ipconstprop"; 
    values[25] = "-ipsccp"; 
    values[26] = "-iv-users";
    values[27] = "-jump-threading";
    values[28] = "-lazy-value-info";
    values[29] = "-lcssa"; 
    values[30] = "-licm"; 
    values[31] = "-lint"; 
    values[32] = "-loop-deletion";
    values[33] = "-loop-extract"; 
    values[34] = "-loop-extract-single"; 
    values[35] = "-loop-reduce";
    values[36] = "-loop-rotate"; 
    values[37] = "-loop-simplify"; 
    values[38] = "-loop-unroll";
    values[39] = "-loop-unswitch"; 
    values[40] = "-loops"; 
    values[41] = "-loweratomic";
    values[42] = "-lowerinvoke"; 
    values[43] = "-lowerswitch";
    values[44] = "-mem2reg";
    values[45] = "-memcpyopt";
    values[46] = "-memdep";  
    values[47] = "-mergefunc";
    values[48] = "-mergereturn";
    values[49] = "-module-debuginfo"; 
    values[50] = "-partial-inliner"; 
    values[51] = "-postdomtree"; 
    //values[53] = "-print-dom-info"; 
    //values[54] = "-print-function";
    //values[55] = "-print-module";  
    values[52] = "-prune-eh";
    values[53] = "-reassociate";
    values[54] = "-reg2mem"; 
    values[55] = "-regions";
    values[56] = "-scalar-evolution"; 
    values[57] = "-sccp";
    values[58] = "-scev-aa"; 
    values[59] = "-simplifycfg"; 
    values[60] = "-sink"; 
    values[61] = "-sroa"; 
    values[62] = "-strip";
    values[63] = "-strip-dead-debug-info"; 
    values[64] = "-strip-dead-prototypes"; 
    values[65] = "-strip-debug-declare";
    values[66] = "-strip-nondebug"; 
    values[67] = "-tailcallelim";

    PASS_VALID_VALUES(o) = values;
    PASS_CONSTRAINED(o) = true;
    PASS_NUM_VALID_VALUES(o) = 68;

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