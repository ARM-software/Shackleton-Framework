#ifndef EVOLUTION_OPTSEQUENCE_H_
#define EVOLUTION_OPTSEQUENCE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../osaka/osaka.h"
#include "../module/gi_llvm_pass.h"
#include "../support/visualization.h"
#include "../support/utility.h"

typedef struct linkedListNode {
    char* data;
    struct linkedListNode *next;
} linkedListNode;

typedef struct optseq {
    int length;
    struct linkedListNode* seqList;
    osaka_object_typ ot;
} optseq;

//char defaultO3[86][50] = {"-licm", "-jump-threading", "-memoryssa", "-early-cse-memssa", "-memdep", "-tbaa", "-bdce", "-instsimplify", "-loop-sink", "-strip-dead-prototypes", "-aa", "-argpromotion", "-callsite-splitting", "-aggressive-instcombine", "-scalar-evolution", "-transform-warning", "-phi-values", "-early-cse", "-block-freq", "-gvn", "-verify", "-globaldce", "-instcombine", "-correlated-propagation", "-prune-eh", "-postdomtree", "-mldst-motion", "-loop-unswitch", "-elim-avail-extern", "-ipsccp", "-slp-vectorizer", "-branch-prob", "-loop-unroll", "-basicaa", "-lower-expect", "-basiccg", "-loop-distribute", "-sccp", "-inline", "-functionattrs", "-lazy-branch-prob", "-adce", "-float2int", "-alignment-from-assumptions", "-inferattrs", "-profile-summary-info", "-lazy-value-info", "-rpo-functionattrs", "-globals-aa", "-constmerge", "-reassociate", "-libcalls-shrinkwrap", "-dse", "-loop-vectorize", "-domtree", "-mem2reg", "-opt-remark-emitter", "-loop-simplify", "-loop-idiom", "-pgo-memop-opt", "-lcssa-verification", "-called-value-propagation", "-demanded-bits", "-div-rem-pairs", "-forceattrs", "-globalopt", "-indvars", "-simplifycfg", "-tti", "-memcpyopt", "-loop-rotate", "-targetlibinfo", "-barrier", "-lcssa", "-loop-deletion", "-loop-load-elim", "-sroa", "-lazy-block-freq", "-ee-instrument", "-loops", "-assumption-cache-tracker", "-loop-accesses", "-deadargelim", "-scoped-noalias", "-speculative-execution", "-tailcallelim"};


char* seq_str_fitness(node_str* indiv);
char* gen_seq_str(node_str* indiv, int* seq_length);
optseq* seq_from_default(char* org_seq[50], osaka_object_typ ot);
optseq* mutate(optseq* seq, node_str* indiv);
optseq* insert(optseq* seq, node_str* patch);
optseq* replace(optseq* seq, node_str* patch);
optseq* delete(optseq* seq, node_str* patch);

int length(linkedListNode* head);
linkedListNode* append(linkedListNode* head, char* pass);
linkedListNode* newLinkedListNode(char* pass);

int get_num_valid();
char** get_valid_passes();
int check_valid_pass(char* data);


#endif /* EVOLUTION_OPTSEQUENCE_H_ */