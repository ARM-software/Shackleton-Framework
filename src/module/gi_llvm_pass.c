/*
 * gi_llvm_pass.c
 *
 * Created on: <created_date>
 * Author: Auto-generated .c file using Shackleton tool
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <assert.h>
 #include <string.h>

 #include "../osaka/osaka.h"
 #include "gi_llvm_pass.h"

uint32_t gi_llvm_pass_uid(void) {

    static uint32_t uid=0;
    return ++uid;

}

void gi_llvm_pass_patch_type_set_valid_values(object_gi_llvm_pass_str* o) {

	char** values = malloc(sizeof(char*) * 3);
	values[0] = "insertion";
	values[1] = "deletion";
	values[2] = "replacement";
	GI_LLVM_PASS_PATCH_TYPE_VALID_VALUES(o) = values;
	GI_LLVM_PASS_PATCH_TYPE_CONSTRAINED(o) = true;
	GI_LLVM_PASS_PATCH_TYPE_NUM_VALID_VALUES(o) = 3;

	return;

}

char*** gi_llvm_set_default_level_strings(int* default_string_lengths, const int num_levels) {
    char*** default_strings = malloc(sizeof(char**) * num_levels);
    for (int l = 0; l < num_levels; l++) {
        default_strings[l] = malloc(sizeof(char*) * default_string_lengths[l]);
    }
    default_strings[0][0] = "-tti";
    default_strings[0][1] = "-verify";
    default_strings[0][2] = "-targetlibinfo";


    default_strings[1][0] = "-tti";
    default_strings[1][1] = "-always-inline";
    default_strings[1][2] = "-basiccg";
    default_strings[1][3] = "-assumption-cache-tracker";
    default_strings[1][4] = "-verify";
    default_strings[1][5] = "-targetlibinfo";
    default_strings[1][6] = "-barrier";
    default_strings[1][7] = "-ee-instrument";
    default_strings[1][8] = "-forceattrs";
    default_strings[1][9] = "-profile-summary-info";


    default_strings[2][0] = "-licm";
    default_strings[2][1] = "-jump-threading";
    default_strings[2][2] = "-memoryssa";
    default_strings[2][3] = "-early-cse-memssa";
    default_strings[2][4] = "-memdep";
    default_strings[2][5] = "-tbaa";
    default_strings[2][6] = "-bdce";
    default_strings[2][7] = "-instsimplify";
    default_strings[2][8] = "-loop-sink";
    default_strings[2][9] = "-strip-dead-prototypes";
    default_strings[2][10] = "-aa";
    default_strings[2][11] = "-scalar-evolution";
    default_strings[2][12] = "-transform-warning";
    default_strings[2][13] = "-phi-values";
    default_strings[2][14] = "-early-cse";
    default_strings[2][15] = "-block-freq";
    default_strings[2][16] = "-globaldce";
    default_strings[2][17] = "-verify";
    default_strings[2][18] = "-instcombine";
    default_strings[2][19] = "-correlated-propagation";
    default_strings[2][20] = "-prune-eh";
    default_strings[2][21] = "-postdomtree";
    default_strings[2][22] = "-loop-unswitch";
    default_strings[2][23] = "-ipsccp";
    default_strings[2][24] = "-branch-prob";
    default_strings[2][25] = "-loop-unroll";
    default_strings[2][26] = "-basicaa";
    default_strings[2][27] = "-lower-expect";
    default_strings[2][28] = "-basiccg";
    default_strings[2][29] = "-loop-distribute";
    default_strings[2][30] = "-sccp";
    default_strings[2][31] = "-functionattrs";
    default_strings[2][32] = "-lazy-branch-prob";
    default_strings[2][33] = "-adce";
    default_strings[2][34] = "-float2int";
    default_strings[2][35] = "-alignment-from-assumptions";
    default_strings[2][36] = "-inferattrs";
    default_strings[2][37] = "-profile-summary-info";
    default_strings[2][38] = "-lazy-value-info";
    default_strings[2][39] = "-rpo-functionattrs";
    default_strings[2][40] = "-globals-aa";
    default_strings[2][41] = "-reassociate";
    default_strings[2][42] = "-libcalls-shrinkwrap";
    default_strings[2][43] = "-dse";
    default_strings[2][44] = "-loop-vectorize";
    default_strings[2][45] = "-domtree";
    default_strings[2][46] = "-mem2reg";
    default_strings[2][47] = "-opt-remark-emitter";
    default_strings[2][48] = "-loop-simplify";
    default_strings[2][49] = "-loop-idiom";
    default_strings[2][50] = "-pgo-memop-opt";
    default_strings[2][51] = "-lcssa-verification";
    default_strings[2][52] = "-called-value-propagation";
    default_strings[2][53] = "-demanded-bits";
    default_strings[2][54] = "-div-rem-pairs";
    default_strings[2][55] = "-forceattrs";
    default_strings[2][56] = "-globalopt";
    default_strings[2][57] = "-indvars";
    default_strings[2][58] = "-simplifycfg";
    default_strings[2][59] = "-tti";
    default_strings[2][60] = "-memcpyopt";
    default_strings[2][61] = "-loop-rotate";
    default_strings[2][62] = "-targetlibinfo";
    default_strings[2][63] = "-barrier";
    default_strings[2][64] = "-lcssa";
    default_strings[2][65] = "-loop-deletion";
    default_strings[2][66] = "-always-inline";
    default_strings[2][67] = "-loop-load-elim";
    default_strings[2][68] = "-sroa";
    default_strings[2][69] = "-lazy-block-freq";
    default_strings[2][70] = "-ee-instrument";
    default_strings[2][71] = "-loops";
    default_strings[2][72] = "-assumption-cache-tracker";
    default_strings[2][73] = "-loop-accesses";
    default_strings[2][74] = "-deadargelim";
    default_strings[2][75] = "-scoped-noalias";
    default_strings[2][76] = "-speculative-execution";
    default_strings[2][77] = "-tailcallelim";


    default_strings[3][0] = "-licm";
    default_strings[3][1] = "-jump-threading";
    default_strings[3][2] = "-memoryssa";
    default_strings[3][3] = "-early-cse-memssa";
    default_strings[3][4] = "-memdep";
    default_strings[3][5] = "-tbaa";
    default_strings[3][6] = "-bdce";
    default_strings[3][7] = "-instsimplify";
    default_strings[3][8] = "-loop-sink";
    default_strings[3][9] = "-strip-dead-prototypes";
    default_strings[3][10] = "-aa";
    default_strings[3][11] = "-scalar-evolution";
    default_strings[3][12] = "-transform-warning";
    default_strings[3][13] = "-phi-values";
    default_strings[3][14] = "-early-cse";
    default_strings[3][15] = "-block-freq";
    default_strings[3][16] = "-gvn";
    default_strings[3][17] = "-verify";
    default_strings[3][18] = "-globaldce";
    default_strings[3][19] = "-instcombine";
    default_strings[3][20] = "-correlated-propagation";
    default_strings[3][21] = "-prune-eh";
    default_strings[3][22] = "-postdomtree";
    default_strings[3][23] = "-mldst-motion";
    default_strings[3][24] = "-loop-unswitch";
    default_strings[3][25] = "-elim-avail-extern";
    default_strings[3][26] = "-ipsccp";
    default_strings[3][27] = "-slp-vectorizer";
    default_strings[3][28] = "-branch-prob";
    default_strings[3][29] = "-loop-unroll";
    default_strings[3][30] = "-basicaa";
    default_strings[3][31] = "-lower-expect";
    default_strings[3][32] = "-basiccg";
    default_strings[3][33] = "-loop-distribute";
    default_strings[3][34] = "-sccp";
    default_strings[3][35] = "-inline";
    default_strings[3][36] = "-functionattrs";
    default_strings[3][37] = "-lazy-branch-prob";
    default_strings[3][38] = "-adce";
    default_strings[3][39] = "-float2int";
    default_strings[3][40] = "-alignment-from-assumptions";
    default_strings[3][41] = "-inferattrs";
    default_strings[3][42] = "-profile-summary-info";
    default_strings[3][43] = "-lazy-value-info";
    default_strings[3][44] = "-rpo-functionattrs";
    default_strings[3][45] = "-globals-aa";
    default_strings[3][46] = "-constmerge";
    default_strings[3][47] = "-reassociate";
    default_strings[3][48] = "-libcalls-shrinkwrap";
    default_strings[3][49] = "-dse";
    default_strings[3][50] = "-loop-vectorize";
    default_strings[3][51] = "-domtree";
    default_strings[3][52] = "-mem2reg";
    default_strings[3][53] = "-opt-remark-emitter";
    default_strings[3][54] = "-loop-simplify";
    default_strings[3][55] = "-loop-idiom";
    default_strings[3][56] = "-pgo-memop-opt";
    default_strings[3][57] = "-lcssa-verification";
    default_strings[3][58] = "-called-value-propagation";
    default_strings[3][59] = "-demanded-bits";
    default_strings[3][60] = "-div-rem-pairs";
    default_strings[3][61] = "-forceattrs";
    default_strings[3][62] = "-globalopt";
    default_strings[3][63] = "-indvars";
    default_strings[3][64] = "-simplifycfg";
    default_strings[3][65] = "-tti";
    default_strings[3][66] = "-memcpyopt";
    default_strings[3][67] = "-loop-rotate";
    default_strings[3][68] = "-targetlibinfo";
    default_strings[3][69] = "-barrier";
    default_strings[3][70] = "-lcssa";
    default_strings[3][71] = "-loop-deletion";
    default_strings[3][72] = "-loop-load-elim";
    default_strings[3][73] = "-sroa";
    default_strings[3][74] = "-lazy-block-freq";
    default_strings[3][75] = "-ee-instrument";
    default_strings[3][76] = "-loops";
    default_strings[3][77] = "-assumption-cache-tracker";
    default_strings[3][78] = "-loop-accesses";
    default_strings[3][79] = "-deadargelim";
    default_strings[3][80] = "-scoped-noalias";
    default_strings[3][81] = "-speculative-execution";
    default_strings[3][82] = "-tailcallelim";


    default_strings[4][0] = "-licm";
    default_strings[4][1] = "-jump-threading";
    default_strings[4][2] = "-memoryssa";
    default_strings[4][3] = "-early-cse-memssa";
    default_strings[4][4] = "-memdep";
    default_strings[4][5] = "-tbaa";
    default_strings[4][6] = "-bdce";
    default_strings[4][7] = "-instsimplify";
    default_strings[4][8] = "-loop-sink";
    default_strings[4][9] = "-strip-dead-prototypes";
    default_strings[4][10] = "-aa";
    default_strings[4][11] = "-argpromotion";
    default_strings[4][12] = "-callsite-splitting";
    default_strings[4][13] = "-aggressive-instcombine";
    default_strings[4][14] = "-scalar-evolution";
    default_strings[4][15] = "-transform-warning";
    default_strings[4][16] = "-phi-values";
    default_strings[4][17] = "-early-cse";
    default_strings[4][18] = "-block-freq";
    default_strings[4][19] = "-gvn";
    default_strings[4][20] = "-verify";
    default_strings[4][21] = "-globaldce";
    default_strings[4][22] = "-instcombine";
    default_strings[4][23] = "-correlated-propagation";
    default_strings[4][24] = "-prune-eh";
    default_strings[4][25] = "-postdomtree";
    default_strings[4][26] = "-mldst-motion";
    default_strings[4][27] = "-loop-unswitch";
    default_strings[4][28] = "-elim-avail-extern";
    default_strings[4][29] = "-ipsccp";
    default_strings[4][30] = "-slp-vectorizer";
    default_strings[4][31] = "-branch-prob";
    default_strings[4][32] = "-loop-unroll";
    default_strings[4][33] = "-basicaa";
    default_strings[4][34] = "-lower-expect";
    default_strings[4][35] = "-basiccg";
    default_strings[4][36] = "-loop-distribute";
    default_strings[4][37] = "-sccp";
    default_strings[4][38] = "-inline";
    default_strings[4][39] = "-functionattrs";
    default_strings[4][40] = "-lazy-branch-prob";
    default_strings[4][41] = "-adce";
    default_strings[4][42] = "-float2int";
    default_strings[4][43] = "-alignment-from-assumptions";
    default_strings[4][44] = "-inferattrs";
    default_strings[4][45] = "-profile-summary-info";
    default_strings[4][46] = "-lazy-value-info";
    default_strings[4][47] = "-rpo-functionattrs";
    default_strings[4][48] = "-globals-aa";
    default_strings[4][49] = "-constmerge";
    default_strings[4][50] = "-reassociate";
    default_strings[4][51] = "-libcalls-shrinkwrap";
    default_strings[4][52] = "-dse";
    default_strings[4][53] = "-loop-vectorize";
    default_strings[4][54] = "-domtree";
    default_strings[4][55] = "-mem2reg";
    default_strings[4][56] = "-opt-remark-emitter";
    default_strings[4][57] = "-loop-simplify";
    default_strings[4][58] = "-loop-idiom";
    default_strings[4][59] = "-pgo-memop-opt";
    default_strings[4][60] = "-lcssa-verification";
    default_strings[4][61] = "-called-value-propagation";
    default_strings[4][62] = "-demanded-bits";
    default_strings[4][63] = "-div-rem-pairs";
    default_strings[4][64] = "-forceattrs";
    default_strings[4][65] = "-globalopt";
    default_strings[4][66] = "-indvars";
    default_strings[4][67] = "-simplifycfg";
    default_strings[4][68] = "-tti";
    default_strings[4][69] = "-memcpyopt";
    default_strings[4][70] = "-loop-rotate";
    default_strings[4][71] = "-targetlibinfo";
    default_strings[4][72] = "-barrier";
    default_strings[4][73] = "-lcssa";
    default_strings[4][74] = "-loop-deletion";
    default_strings[4][75] = "-loop-load-elim";
    default_strings[4][76] = "-sroa";
    default_strings[4][77] = "-lazy-block-freq";
    default_strings[4][78] = "-ee-instrument";
    default_strings[4][79] = "-loops";
    default_strings[4][80] = "-assumption-cache-tracker";
    default_strings[4][81] = "-loop-accesses";
    default_strings[4][82] = "-deadargelim";
    default_strings[4][83] = "-scoped-noalias";
    default_strings[4][84] = "-speculative-execution";
    default_strings[4][85] = "-tailcallelim";


    default_strings[5][0] = "-licm";
    default_strings[5][1] = "-jump-threading";
    default_strings[5][2] = "-memoryssa";
    default_strings[5][3] = "-early-cse-memssa";
    default_strings[5][4] = "-memdep";
    default_strings[5][5] = "-tbaa";
    default_strings[5][6] = "-bdce";
    default_strings[5][7] = "-instsimplify";
    default_strings[5][8] = "-loop-sink";
    default_strings[5][9] = "-strip-dead-prototypes";
    default_strings[5][10] = "-aa";
    default_strings[5][11] = "-scalar-evolution";
    default_strings[5][12] = "-transform-warning";
    default_strings[5][13] = "-phi-values";
    default_strings[5][14] = "-block-freq";
    default_strings[5][15] = "-early-cse";
    default_strings[5][16] = "-gvn";
    default_strings[5][17] = "-verify";
    default_strings[5][18] = "-globaldce";
    default_strings[5][19] = "-instcombine";
    default_strings[5][20] = "-correlated-propagation";
    default_strings[5][21] = "-prune-eh";
    default_strings[5][22] = "-postdomtree";
    default_strings[5][23] = "-mldst-motion";
    default_strings[5][24] = "-loop-unswitch";
    default_strings[5][25] = "-elim-avail-extern";
    default_strings[5][26] = "-ipsccp";
    default_strings[5][27] = "-slp-vectorizer";
    default_strings[5][28] = "-branch-prob";
    default_strings[5][29] = "-loop-unroll";
    default_strings[5][30] = "-basicaa";
    default_strings[5][31] = "-lower-expect";
    default_strings[5][32] = "-basiccg";
    default_strings[5][33] = "-loop-distribute";
    default_strings[5][34] = "-sccp";
    default_strings[5][35] = "-inline";
    default_strings[5][36] = "-functionattrs";
    default_strings[5][37] = "-lazy-branch-prob";
    default_strings[5][38] = "-adce";
    default_strings[5][39] = "-float2int";
    default_strings[5][40] = "-alignment-from-assumptions";
    default_strings[5][41] = "-inferattrs";
    default_strings[5][42] = "-profile-summary-info";
    default_strings[5][43] = "-lazy-value-info";
    default_strings[5][44] = "-rpo-functionattrs";
    default_strings[5][45] = "-globals-aa";
    default_strings[5][46] = "-constmerge";
    default_strings[5][47] = "-reassociate";
    default_strings[5][48] = "-dse";
    default_strings[5][49] = "-loop-vectorize";
    default_strings[5][50] = "-domtree";
    default_strings[5][51] = "-mem2reg";
    default_strings[5][52] = "-opt-remark-emitter";
    default_strings[5][53] = "-loop-simplify";
    default_strings[5][54] = "-loop-idiom";
    default_strings[5][55] = "-lcssa-verification";
    default_strings[5][56] = "-called-value-propagation";
    default_strings[5][57] = "-demanded-bits";
    default_strings[5][58] = "-div-rem-pairs";
    default_strings[5][59] = "-forceattrs";
    default_strings[5][60] = "-globalopt";
    default_strings[5][61] = "-indvars";
    default_strings[5][62] = "-simplifycfg";
    default_strings[5][63] = "-tti";
    default_strings[5][64] = "-memcpyopt";
    default_strings[5][65] = "-loop-rotate";
    default_strings[5][66] = "-targetlibinfo";
    default_strings[5][67] = "-barrier";
    default_strings[5][68] = "-lcssa";
    default_strings[5][69] = "-loop-deletion";
    default_strings[5][70] = "-loop-load-elim";
    default_strings[5][71] = "-sroa";
    default_strings[5][72] = "-lazy-block-freq";
    default_strings[5][73] = "-ee-instrument";
    default_strings[5][74] = "-loops";
    default_strings[5][75] = "-assumption-cache-tracker";
    default_strings[5][76] = "-loop-accesses";
    default_strings[5][77] = "-deadargelim";
    default_strings[5][78] = "-scoped-noalias";
    default_strings[5][79] = "-speculative-execution";
    default_strings[5][80] = "-tailcallelim";


    default_strings[6][0] = "-licm";
    default_strings[6][1] = "-jump-threading";
    default_strings[6][2] = "-memoryssa";
    default_strings[6][3] = "-early-cse-memssa";
    default_strings[6][4] = "-memdep";
    default_strings[6][5] = "-tbaa";
    default_strings[6][6] = "-bdce";
    default_strings[6][7] = "-instsimplify";
    default_strings[6][8] = "-loop-sink";
    default_strings[6][9] = "-strip-dead-prototypes";
    default_strings[6][10] = "-aa";
    default_strings[6][11] = "-scalar-evolution";
    default_strings[6][12] = "-transform-warning";
    default_strings[6][13] = "-phi-values";
    default_strings[6][14] = "-block-freq";
    default_strings[6][15] = "-early-cse";
    default_strings[6][16] = "-gvn";
    default_strings[6][17] = "-verify";
    default_strings[6][18] = "-globaldce";
    default_strings[6][19] = "-instcombine";
    default_strings[6][20] = "-correlated-propagation";
    default_strings[6][21] = "-prune-eh";
    default_strings[6][22] = "-postdomtree";
    default_strings[6][23] = "-mldst-motion";
    default_strings[6][24] = "-loop-unswitch";
    default_strings[6][25] = "-elim-avail-extern";
    default_strings[6][26] = "-ipsccp";
    default_strings[6][27] = "-branch-prob";
    default_strings[6][28] = "-loop-unroll";
    default_strings[6][29] = "-basicaa";
    default_strings[6][30] = "-lower-expect";
    default_strings[6][31] = "-basiccg";
    default_strings[6][32] = "-loop-distribute";
    default_strings[6][33] = "-sccp";
    default_strings[6][34] = "-inline";
    default_strings[6][35] = "-functionattrs";
    default_strings[6][36] = "-lazy-branch-prob";
    default_strings[6][37] = "-adce";
    default_strings[6][38] = "-float2int";
    default_strings[6][39] = "-alignment-from-assumptions";
    default_strings[6][40] = "-inferattrs";
    default_strings[6][41] = "-profile-summary-info";
    default_strings[6][42] = "-lazy-value-info";
    default_strings[6][43] = "-rpo-functionattrs";
    default_strings[6][44] = "-globals-aa";
    default_strings[6][45] = "-constmerge";
    default_strings[6][46] = "-reassociate";
    default_strings[6][47] = "-dse";
    default_strings[6][48] = "-loop-vectorize";
    default_strings[6][49] = "-domtree";
    default_strings[6][50] = "-mem2reg";
    default_strings[6][51] = "-opt-remark-emitter";
    default_strings[6][52] = "-loop-simplify";
    default_strings[6][53] = "-loop-idiom";
    default_strings[6][54] = "-lcssa-verification";
    default_strings[6][55] = "-called-value-propagation";
    default_strings[6][56] = "-demanded-bits";
    default_strings[6][57] = "-div-rem-pairs";
    default_strings[6][58] = "-forceattrs";
    default_strings[6][59] = "-globalopt";
    default_strings[6][60] = "-indvars";
    default_strings[6][61] = "-simplifycfg";
    default_strings[6][62] = "-tti";
    default_strings[6][63] = "-memcpyopt";
    default_strings[6][64] = "-loop-rotate";
    default_strings[6][65] = "-targetlibinfo";
    default_strings[6][66] = "-barrier";
    default_strings[6][67] = "-lcssa";
    default_strings[6][68] = "-loop-deletion";
    default_strings[6][69] = "-loop-load-elim";
    default_strings[6][70] = "-sroa";
    default_strings[6][71] = "-lazy-block-freq";
    default_strings[6][72] = "-ee-instrument";
    default_strings[6][73] = "-loops";
    default_strings[6][74] = "-assumption-cache-tracker";
    default_strings[6][75] = "-loop-accesses";
    default_strings[6][76] = "-deadargelim";
    default_strings[6][77] = "-scoped-noalias";
    default_strings[6][78] = "-speculative-execution";
    default_strings[6][79] = "-tailcallelim";
    return default_strings;
}

int* gi_llvm_default_level_string_lengths(const int num_levels) {
    int* default_string_lengths = malloc(sizeof(int) * num_levels);
    default_string_lengths[0] = 3;
    default_string_lengths[1] = 10;
    default_string_lengths[2] = 78;
    default_string_lengths[3] = 83;
    default_string_lengths[4] = 86;
    default_string_lengths[5] = 81;
    default_string_lengths[6] = 80;
    return default_string_lengths;
}


void gi_llvm_pass_new_pass_set_valid_values(object_gi_llvm_pass_str* o) {

	int num_passes = 68;
    char** values = malloc(sizeof(char*) * num_passes);
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
    values[31] = "-simplifycfg"; 
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

    GI_LLVM_PASS_NEW_PASS_VALID_VALUES(o) = values;
    GI_LLVM_PASS_NEW_PASS_CONSTRAINED(o) = true;
    GI_LLVM_PASS_NEW_PASS_NUM_VALID_VALUES(o) = num_passes;

	return;

}

object_gi_llvm_pass_str *gi_llvm_pass_createobject(void) {

    object_gi_llvm_pass_str *o;
	gi_llvm_pass_patch_type *gi_llvm_pass_patch_type_o;
	gi_llvm_pass_location *gi_llvm_pass_location_o;
	gi_llvm_pass_new_pass *gi_llvm_pass_new_pass_o;

    o = malloc(sizeof(object_gi_llvm_pass_str));
	gi_llvm_pass_patch_type_o = malloc(sizeof(gi_llvm_pass_patch_type));
	gi_llvm_pass_location_o = malloc(sizeof(gi_llvm_pass_location));
	gi_llvm_pass_new_pass_o = malloc(sizeof(gi_llvm_pass_new_pass));

	assert(o!=NULL);
	assert(gi_llvm_pass_patch_type_o!=NULL);
	assert(gi_llvm_pass_location_o!=NULL);
	assert(gi_llvm_pass_new_pass_o!=NULL);

	GI_LLVM_PASS_PATCH_TYPE_STRUCT(o) = gi_llvm_pass_patch_type_o;
	GI_LLVM_PASS_LOCATION_STRUCT(o) = gi_llvm_pass_location_o;
	GI_LLVM_PASS_NEW_PASS_STRUCT(o) = gi_llvm_pass_new_pass_o;

	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(o) = "not set";
	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o) = -1;
	gi_llvm_pass_patch_type_set_valid_values(o);

	GI_LLVM_PASS_LOCATION_MY_LOCATION(o) = -1;
	GI_LLVM_PASS_LOCATION_CONSTRAINED(o) = false;
	GI_LLVM_PASS_LOCATION_VALID_VALUES(o) = NULL;
	GI_LLVM_PASS_LOCATION_NUM_VALID_VALUES(o) = 0;

	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(o) = "not set";
	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o) = -1;
	gi_llvm_pass_new_pass_set_valid_values(o);

	return o;

}

void gi_llvm_pass_randomizeobject(object_gi_llvm_pass_str *o) {

	uint32_t num_valid_values0 = GI_LLVM_PASS_PATCH_TYPE_NUM_VALID_VALUES(o);
	uint32_t new_index0 = (uint32_t) (num_valid_values0 * (rand() / (RAND_MAX + 1.0)));
	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o) = new_index0;
	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(o) = GI_LLVM_PASS_PATCH_TYPE_VALID_VALUES(o)[new_index0];

	GI_LLVM_PASS_LOCATION_MY_LOCATION(o) = rand() / (RAND_MAX + 1.0);
    //printf("NEW OBJECT LOCATION: %lf\n\n", GI_LLVM_PASS_LOCATION_MY_LOCATION(o));

	uint32_t num_valid_values1 = GI_LLVM_PASS_NEW_PASS_NUM_VALID_VALUES(o);
	uint32_t new_index1 = (uint32_t) (num_valid_values1 * (rand() / (RAND_MAX + 1.0)));
	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o) = new_index1;
	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(o) = GI_LLVM_PASS_NEW_PASS_VALID_VALUES(o)[new_index1];

}

void gi_llvm_pass_setobject(object_gi_llvm_pass_str* o, char* pass) {
    
	return;

}

char* gi_llvm_pass_get_type(object_gi_llvm_pass_str *o) {
    return GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(o);
}

double gi_llvm_pass_get_loc(object_gi_llvm_pass_str *o) {
    return GI_LLVM_PASS_LOCATION_MY_LOCATION(o);
}

char* gi_llvm_pass_get_pass(object_gi_llvm_pass_str *o) {
    return GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(o);
}

void gi_llvm_pass_printobject(object_gi_llvm_pass_str *o) {

	printf("PATCH_TYPE : %s ; ", GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(o));
	printf("LOCATION : %lf ; ", GI_LLVM_PASS_LOCATION_MY_LOCATION(o));
	printf("NEW_PASS : %s", GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(o));

}

void *gi_llvm_pass_describeobject(char* desc, object_gi_llvm_pass_str *o) {

    char* pass_type = GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(o);

    float location = GI_LLVM_PASS_LOCATION_MY_LOCATION(o);
    char loc_str[8];
    gcvt(location, 4, loc_str);
    char* new_pass = GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(o);
    
    strcat(desc, pass_type);
    strcat(desc, " ");
    strcat(desc, loc_str);
    strcat(desc, " ");
    strcat(desc, new_pass);
    strcat(desc, "\n");

}

void gi_llvm_pass_deleteobject(object_gi_llvm_pass_str *s) {

	assert(s!=NULL);

	free(GI_LLVM_PASS_PATCH_TYPE_VALID_VALUES(s));
	free(GI_LLVM_PASS_PATCH_TYPE_STRUCT(s));
	free(GI_LLVM_PASS_LOCATION_STRUCT(s));
	free(GI_LLVM_PASS_NEW_PASS_VALID_VALUES(s));
	free(GI_LLVM_PASS_NEW_PASS_STRUCT(s));

	free(s);

}

void gi_llvm_pass_writeobject(FILE *stream, object_gi_llvm_pass_str *o) {

    assert(stream!=NULL);
    fwrite(o, sizeof(object_gi_llvm_pass_str), 1, stream);

}

void *gi_llvm_pass_readobject(FILE *stream) {

    object_gi_llvm_pass_str *o;
	gi_llvm_pass_patch_type *gi_llvm_pass_patch_type_o;
	gi_llvm_pass_location *gi_llvm_pass_location_o;
	gi_llvm_pass_new_pass *gi_llvm_pass_new_pass_o;

	assert(stream!=NULL);

	o = malloc(sizeof(object_gi_llvm_pass_str));
	gi_llvm_pass_patch_type_o = malloc(sizeof(gi_llvm_pass_patch_type));
	gi_llvm_pass_location_o = malloc(sizeof(gi_llvm_pass_location));
	gi_llvm_pass_new_pass_o = malloc(sizeof(gi_llvm_pass_new_pass));

	assert(o!=NULL);
	assert(gi_llvm_pass_patch_type_o!=NULL);
	assert(gi_llvm_pass_location_o!=NULL);
	assert(gi_llvm_pass_new_pass_o!=NULL);

	GI_LLVM_PASS_PATCH_TYPE_STRUCT(o) = gi_llvm_pass_patch_type_o;
	GI_LLVM_PASS_LOCATION_STRUCT(o) = gi_llvm_pass_location_o;
	GI_LLVM_PASS_NEW_PASS_STRUCT(o) = gi_llvm_pass_new_pass_o;

	fread(o, sizeof(object_gi_llvm_pass_str), 1, stream);

	return o;

}

void *gi_llvm_pass_copyobject(object_gi_llvm_pass_str *o) {

	//printf("\nNow in copy object\n");
    object_gi_llvm_pass_str *c = gi_llvm_pass_createobject();

    //printf("\nObject has been created\n");
	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(c) = GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o);
	GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE(c) = GI_LLVM_PASS_PATCH_TYPE_VALID_VALUES(c)[GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o)];
    //printf("\nGot through editing the patch type\n");

	GI_LLVM_PASS_LOCATION_MY_LOCATION(c) = GI_LLVM_PASS_LOCATION_MY_LOCATION(o);
    //printf("\nGot through editing the location\n");

	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(c) = GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o);
	GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS(c) = GI_LLVM_PASS_NEW_PASS_VALID_VALUES(c)[GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o)];
    //printf("\nGot through editing the new pass\n");

	return c;

}

bool gi_llvm_pass_compareobject(object_gi_llvm_pass_str *o1, object_gi_llvm_pass_str *o2)   {
    if (GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o1) != GI_LLVM_PASS_PATCH_TYPE_MY_PATCH_TYPE_INDEX(o2)) {
        return false;
    }
    if (GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o1) != GI_LLVM_PASS_NEW_PASS_MY_NEW_PASS_INDEX(o2)) {
        return false;
    }
    if (fabs(GI_LLVM_PASS_LOCATION_MY_LOCATION(o1) - GI_LLVM_PASS_LOCATION_MY_LOCATION(o2)) > 0.001) {
        return false;
    }
    return true;

}