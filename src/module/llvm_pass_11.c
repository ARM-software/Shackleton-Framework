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
	
    int num_passes = 250;
    char** values = malloc(sizeof(char*) * num_passes);
    values[0] = "--aa";
    values[1] = "--adce";
    values[2] = "--add-discriminators";
    values[3] = "--aggressive-instcombine";
    values[4] = "--alignment-from-assumptions";
    values[5] = "--always-inline";
    values[6] = "--argpromotion";
    values[7] = "--asan";
    values[8] = "--asan-globals-md";
    values[9] = "--assume-builder";
    values[10] = "--assume-simplify";
    values[11] = "--assumption-cache-tracker";
    values[12] = "--atomic-expand";
    values[13] = "--attributor";
    values[14] = "--attributor-cgscc";
    values[15] = "--barrier";
    values[16] = "--basic-aa";
    values[17] = "--basiccg";
    values[18] = "--bdce";
    values[19] = "--block-freq";
    values[20] = "--bounds-checking";
    values[21] = "--branch-prob";
    values[22] = "--break-crit-edges";
    values[23] = "--called-value-propagation";
    values[24] = "--callsite-splitting";
    values[25] = "--canon-freeze";
    values[26] = "--canonicalize-aliases";
    values[27] = "--cfl-anders-aa";
    values[28] = "--cfl-steens-aa";
    values[29] = "--cg-profile";
    values[30] = "--codegenprepare";
    values[31] = "--consthoist";
    values[32] = "--constmerge";
    values[33] = "--constprop";
    values[34] = "--coro-cleanup";
    values[35] = "--coro-early";
    values[36] = "--coro-elide";
    values[37] = "--coro-split";
    values[38] = "--correlated-propagation";
    values[39] = "--cost-model";
    values[40] = "--cross-dso-cfi";
    values[41] = "--da";
    values[42] = "--dce";
    values[43] = "--deadargelim";
    values[44] = "--delinearize";
    values[45] = "--demanded-bits";
    values[46] = "--die";
    values[47] = "--div-rem-pairs";
    values[48] = "--divergence";
    values[49] = "--domfrontier";
    values[50] = "--domtree";
    values[51] = "--dse";
    values[52] = "--dwarfehprepare";
    values[53] = "--early-cse";
    values[54] = "--early-cse-memssa";
    values[55] = "--ee-instrument";
    values[56] = "--elim-avail-extern";
    values[57] = "--expand-reductions";
    values[58] = "--expandmemcmp";
    values[59] = "--external-aa";
    values[60] = "--extract-blocks";
    values[61] = "--fix-irreducible";
    values[62] = "--flattencfg";
    values[63] = "--float2int";
    values[64] = "--forceattrs";
    values[65] = "--functionattrs";
    values[66] = "--global-merge";
    values[67] = "--globaldce";
    values[68] = "--globalopt";
    values[69] = "--globals-aa";
    values[70] = "--globalsplit";
    values[71] = "--guard-widening";
    values[72] = "--gvn";
    values[73] = "--gvn-hoist";
    values[74] = "--gvn-sink";
    values[75] = "--hardware-loops";
    values[76] = "--hotcoldsplit";
    values[77] = "--hwasan";
    values[78] = "--indirectbr-expand";
    values[79] = "--indvars";
    values[80] = "--infer-address-spaces";
    values[81] = "--inferattrs";
    values[82] = "--inject-tli-mappings";
    values[83] = "--inline";
    values[84] = "--insert-gcov-profiling";
    values[85] = "--instcombine";
    values[86] = "--instcount";
    values[87] = "--instnamer";
    values[88] = "--instrorderfile";
    values[89] = "--instrprof";
    values[90] = "--instsimplify";
    values[91] = "--interleaved-access";
    values[92] = "--interleaved-load-combine";
    values[93] = "--internalize";
    values[94] = "--intervals";
    values[95] = "--ipconstprop";
    values[96] = "--ipsccp";
    values[97] = "--irce";
    values[98] = "--iv-users";
    values[99] = "--jump-threading";
    values[100] = "--lazy-block-freq";
    values[101] = "--lazy-branch-prob";
    values[102] = "--lazy-value-info";
    values[103] = "--lcssa";
    values[104] = "--lcssa-verification";
    values[105] = "--libcalls-shrinkwrap";
    values[106] = "--licm";
    values[107] = "--lint";
    values[108] = "--load-store-vectorizer";
    values[109] = "--loop-accesses";
    values[110] = "--loop-data-prefetch";
    values[111] = "--loop-deletion";
    values[112] = "--loop-distribute";
    values[113] = "--loop-extract";
    values[114] = "--loop-extract-single";
    values[115] = "--loop-fusion";
    values[116] = "--loop-guard-widening";
    values[117] = "--loop-idiom";
    values[118] = "--loop-instsimplify";
    values[119] = "--loop-interchange";
    values[120] = "--loop-load-elim";
    values[121] = "--loop-predication";
    values[122] = "--loop-reduce";
    values[123] = "--loop-reroll";
    values[124] = "--loop-rotate";
    values[125] = "--loop-simplify";
    values[126] = "--loop-simplifycfg";
    values[127] = "--loop-sink";
    values[128] = "--loop-unroll";
    values[129] = "--loop-unroll-and-jam";
    values[130] = "--loop-unswitch";
    values[131] = "--loop-vectorize";
    values[132] = "--loop-versioning";
    values[133] = "--loop-versioning-licm";
    values[134] = "--loops";
    values[135] = "--lower-constant-intrinsics";
    values[136] = "--lower-expect";
    values[137] = "--lower-guard-intrinsic";
    values[138] = "--lower-matrix-intrinsics";
    values[139] = "--lower-widenable-condition";
    values[140] = "--loweratomic";
    values[141] = "--lowerinvoke";
    values[142] = "--lowerswitch";
    values[143] = "--lowertypetests";
    values[144] = "--machine-branch-prob";
    values[145] = "--make-guards-explicit";
    values[146] = "--mem2reg";
    values[147] = "--memcpyopt";
    values[148] = "--memdep";
    values[149] = "--memoryssa";
    values[150] = "--mergefunc";
    values[151] = "--mergeicmps";
    values[152] = "--mergereturn";
    values[153] = "--mldst-motion";
    values[154] = "--module-debuginfo";
    values[155] = "--module-summary-analysis";
    values[156] = "--module-summary-info";
    values[157] = "--name-anon-globals";
    values[158] = "--nary-reassociate";
    values[159] = "--newgvn";
    values[160] = "--objc-arc";
    values[161] = "--objc-arc-aa";
    values[162] = "--objc-arc-apelim";
    values[163] = "--objc-arc-contract";
    values[164] = "--objc-arc-expand";
    values[165] = "--openmpopt";
    values[166] = "--opt-remark-emitter";
    values[167] = "--partial-inliner";
    values[168] = "--partially-inline-libcalls";
    values[169] = "--pgo-icall-prom";
    values[170] = "--pgo-memop-opt";
    values[171] = "--phi-values";
    values[172] = "--place-backedge-safepoints-impl";
    values[173] = "--place-safepoints";
    values[174] = "--polly-ast";
    values[175] = "--polly-canonicalize";
    values[176] = "--polly-cleanup";
    values[177] = "--polly-codegen";
    values[178] = "--polly-dce";
    values[179] = "--polly-delicm";
    values[180] = "--polly-dependences";
    values[181] = "--polly-detect";
    values[182] = "--polly-dump-module";
    values[183] = "--polly-export-jscop";
    values[184] = "--polly-flatten-schedule";
    values[185] = "--polly-function-dependences";
    values[186] = "--polly-function-scops";
    values[187] = "--polly-import-jscop";
    values[188] = "--polly-mse";
    values[189] = "--polly-opt-isl";
    values[190] = "--polly-optree";
    values[191] = "--polly-prepare";
    values[192] = "--polly-prune-unprofitable";
    values[193] = "--polly-rewrite-byref-params";
    values[194] = "--polly-scops";
    values[195] = "--polly-simplify";
    values[196] = "--polyhedral-info";
    values[197] = "--post-inline-ee-instrument";
    values[198] = "--postdomtree";
    values[199] = "--pre-isel-intrinsic-lowering";
    values[200] = "--profile-summary-info";
    values[201] = "--prune-eh";
    values[202] = "--reassociate";
    values[203] = "--redundant-dbg-inst-elim";
    values[204] = "--reg2mem";
    values[205] = "--regions";
    values[206] = "--rewrite-statepoints-for-gc";
    values[207] = "--rewrite-symbols";
    values[208] = "--rpo-functionattrs";
    values[209] = "--safe-stack";
    values[210] = "--sancov";
    values[211] = "--scalar-evolution";
    values[212] = "--scalarize-masked-mem-intrin";
    values[213] = "--scalarizer";
    values[214] = "--sccp";
    values[215] = "--scev-aa";
    values[216] = "--scoped-noalias";
    values[217] = "--separate-const-offset-from-gep";
    values[218] = "--simple-loop-unswitch";
    values[219] = "--simplifycfg";
    values[220] = "--sink";
    values[221] = "--sjljehprepare";
    values[222] = "--slp-vectorizer";
    values[223] = "--slsr";
    values[224] = "--speculative-execution";
    values[225] = "--sroa";
    values[226] = "--stack-safety";
    values[227] = "--stack-safety-local";
    values[228] = "--strip";
    values[229] = "--strip-dead-debug-info";
    values[230] = "--strip-dead-prototypes";
    values[231] = "--strip-debug-declare";
    values[232] = "--strip-gc-relocates";
    values[233] = "--strip-nondebug";
    values[234] = "--strip-nonlinetable-debuginfo";
    values[235] = "--structurizecfg";
    values[236] = "--tailcallelim";
    values[237] = "--targetlibinfo";
    values[238] = "--tbaa";
    values[239] = "--transform-warning";
    values[240] = "--tti";
    values[241] = "--type-promotion";
    values[242] = "--unify-loop-exits";
    values[243] = "--unique-internal-linkage-names";
    values[244] = "--unreachableblockelim";
    values[245] = "--vector-combine";
    values[246] = "--verify-safepoint-ir";
    values[247] = "--wasmehprepare";
    values[248] = "--wholeprogramdevirt";
    values[249] = "--winehprepare";

    PASS_VALID_VALUES(o) = values;
    PASS_CONSTRAINED(o) = true;
    PASS_NUM_VALID_VALUES(o) = num_passes;

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

    printf("pass : %s(%d)", PASS(o), PASS_INDEX(o));

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

bool llvm_pass_compareobject(object_llvm_pass_str *o1, object_llvm_pass_str *o2)   {

    return PASS_INDEX(o1) == PASS_INDEX(o2);
}