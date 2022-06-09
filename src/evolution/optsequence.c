/*
 ============================================================================
 Name        : fitness.c
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
    
 Description : Main and helper functions for determining the fitness
               of an individual and using that fitness value within
               the evolution process
 ============================================================================
 */

/*
 * IMPORT
 */

#include "optsequence.h"

//char defaultO3[86][50] = {"-licm", "-jump-threading", "-memoryssa", "-early-cse-memssa", "-memdep", "-tbaa", "-bdce", "-instsimplify", "-loop-sink", "-strip-dead-prototypes", "-aa", "-argpromotion", "-callsite-splitting", "-aggressive-instcombine", "-scalar-evolution", "-transform-warning", "-phi-values", "-early-cse", "-block-freq", "-gvn", "-verify", "-globaldce", "-instcombine", "-correlated-propagation", "-prune-eh", "-postdomtree", "-mldst-motion", "-loop-unswitch", "-elim-avail-extern", "-ipsccp", "-slp-vectorizer", "-branch-prob", "-loop-unroll", "-basicaa", "-lower-expect", "-basiccg", "-loop-distribute", "-sccp", "-inline", "-functionattrs", "-lazy-branch-prob", "-adce", "-float2int", "-alignment-from-assumptions", "-inferattrs", "-profile-summary-info", "-lazy-value-info", "-rpo-functionattrs", "-globals-aa", "-constmerge", "-reassociate", "-libcalls-shrinkwrap", "-dse", "-loop-vectorize", "-domtree", "-mem2reg", "-opt-remark-emitter", "-loop-simplify", "-loop-idiom", "-pgo-memop-opt", "-lcssa-verification", "-called-value-propagation", "-demanded-bits", "-div-rem-pairs", "-forceattrs", "-globalopt", "-indvars", "-simplifycfg", "-tti", "-memcpyopt", "-loop-rotate", "-targetlibinfo", "-barrier", "-lcssa", "-loop-deletion", "-loop-load-elim", "-sroa", "-lazy-block-freq", "-ee-instrument", "-loops", "-assumption-cache-tracker", "-loop-accesses", "-deadargelim", "-scoped-noalias", "-speculative-execution", "-tailcallelim"};

optseq* seq_from_default(char** org_seq, osaka_object_typ ot) {
    struct optseq* seq = (optseq*) malloc(sizeof(optseq));
    struct linkedListNode *head = NULL;
    int seq_len = 86;
    int i;
    for (i = 0; i < seq_len; i++) {
        head = append(head, org_seq[i]);
    }
    seq->length = seq_len;
    seq->seqList = head;
    seq->ot = ot;
    return seq;
}

char** get_default(int num_levels, int target_default) {
    int* default_string_lengths = gi_llvm_default_level_string_lengths(num_levels);
    char*** default_strings = gi_llvm_set_default_level_strings(default_string_lengths, num_levels);
    return default_strings[target_default];
}

char* seq_str_fitness(node_str* indiv) {
    int num_levels = 7;
    int target_default = 4;
    //char** defaultO3 = get_default(num_levels, target_default);
    //optseq* seq = seq_from_default(defaultO3, indiv->objtype);
    int len = 0;
    return gen_seq_str(indiv, &len);
}

char* gen_seq_str(node_str* indiv, int* seq_length) {
    int num_levels = 7;
    int target_default = 4;
    //visualization_print_individual_concise_details(indiv);
    char** default_str = get_default(num_levels, target_default);
    optseq* seq = seq_from_default(default_str, indiv->objtype);
    
    while (NEXT(indiv) != NULL){
        seq = mutate(seq, indiv);
        indiv = NEXT(indiv);
    }

    *seq_length = seq->length;
    char* seq_str = malloc(2000);
    strcpy(seq_str, "");
    linkedListNode* head = seq->seqList;

    //for (int i = 0; i < seq->length; i++) {
    //int total = 0;
    //int valid = 0;
    while (head->next != NULL){
        char* pass_name = head->data;
        linkedListNode* temp = head;
        head = head->next;
        free(temp);
        //printf("check result: %d\n", check_valid_pass(pass_name));
        if (check_valid_pass(pass_name)) {
            strcat(seq_str, pass_name);
            strcat(seq_str, " ");
            //printf("apppended\n");
            //valid++;
        }
        //total++;
    }
    free(seq);
    //printf("sequence: %s\nseq->length: %d, total: %d, valid: %d\n\n", seq_str, seq->length, total, valid);
    return seq_str;
}

optseq* mutate(optseq* seq, node_str* indiv) {
    char* type = gi_llvm_pass_get_type(OBJECT(indiv));
    //char* type = "replacement";
    if (strcmp(type, "insertion") == 0) {
        //printf("insertion mutation\n");
        return insert(seq, indiv);
    }
    else if (strcmp(type, "deletion") == 0) {
        //printf("deletion mutation\n");
        return delete(seq, indiv);
    }
    else if (strcmp(type, "replacement") == 0) {
        //printf("replacement mutation\n");
        return replace(seq, indiv);
    }
    printf("\nWARNING: INVALID PASS TYPE, RETURNING NULL SEQUENCE\n\n");
    return NULL; 
}


optseq* insert(optseq* seq, node_str* patch) {
    double loc = gi_llvm_pass_get_loc(OBJECT(patch));
    char* pass = gi_llvm_pass_get_pass(OBJECT(patch));

    int pos = (int)(loc*seq->length);
    if (pos == 0) {
        linkedListNode* head = newLinkedListNode(pass);
        head->next = seq->seqList;
        seq->seqList = head;
        seq->length++;
        return seq;
    }
    
    linkedListNode* current = seq->seqList;
    int counter = 0;
    while (counter < pos-1) {
        current = current->next;
        counter++;
    }

    linkedListNode* new_node = newLinkedListNode(pass);
    linkedListNode* temp = current->next;
    current->next = new_node;
    new_node->next = temp;
    seq->length++;
    return seq;
}

optseq* replace(optseq* seq, node_str* patch) {
    double loc = gi_llvm_pass_get_loc(OBJECT(patch));
    char* pass = gi_llvm_pass_get_pass(OBJECT(patch));
    int pos = (int)(loc*seq->length);
    linkedListNode* current = seq->seqList;
    int counter = 0;
    while (counter < pos) {
        current = current->next;
        counter++;
    }
    current->data = pass;
    return seq;
}

optseq* delete(optseq* seq, node_str* patch) {
    double loc = gi_llvm_pass_get_loc(OBJECT(patch));
    int pos = (int)(loc*seq->length);
    if (pos == 0) {
        linkedListNode* head = seq->seqList;
        seq->seqList = head->next;
        //free(head);
        seq->length--;
        return seq;
    }
    linkedListNode* current = seq->seqList;
    int counter = 0;
    while (counter < pos-1) {
        current = current->next;
        counter++;
    }
    linkedListNode* todelete = current->next;
    current->next = todelete->next;
    //free(todelete);
    seq->length--;
    return seq;
}

int length(linkedListNode* head) {
    int length = 0;
    linkedListNode *current;
    for(current = head; current != NULL; current = current->next) {
        length++;
    }
    return length;
}

linkedListNode* append(linkedListNode* head, char* pass) {
    linkedListNode *current = head;
    if (current == NULL) {
        //printf("current is null\n");
        return newLinkedListNode(pass);
    }
    while(current->next != NULL) {
        //printf("current: %p, current->next: %p\n", current, current->next);
        current = current->next;
    }
    //printf("current: %p, current->next: %p\n", current, current->next);
    current->next = newLinkedListNode(pass);
    //printf("finish append, current->next: %p, current->next->next: %p\n\n", current->next, current->next->next);
    return head;
}

linkedListNode* newLinkedListNode(char* pass) {
    linkedListNode *new_node = (linkedListNode*) malloc(sizeof(linkedListNode));
    new_node->data = pass;
    new_node->next = NULL;
    return new_node;
}

int get_num_valid() {
    return 68;
}

char** get_valid_passes() {
    int num_passes = get_num_valid();
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
    return values;
}

int check_valid_pass(char* data) {
    char** valid_passes = get_valid_passes();
    int num_valid = get_num_valid();
    for (int i = 0; i < num_valid; i++) {
        if (strcmp(data, valid_passes[i]) == 0) {
            //printf("data: %s, valid_passes[%d]: %s\n", data, i, valid_passes[i]);
            //printf("YES: %s\n", data);
            return 1;
        }
    }
    free(valid_passes);
    //printf("NO:  %s\n", data);
    return 0;
}