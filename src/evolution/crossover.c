/*
 ============================================================================
 Name        : crossover.c
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
    
 Description : All crossover functionality for 2 individuals that
               that are genetically spliced together into 2
               different individuals
 ============================================================================
 */

/*
 * IMPORT
 */

#include "crossover.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   crossover_onepoint_macro
 *
 * DESCRIPTION
 *
 *  Takes in two osaka individuals to be evolved and splices
 *  them at a single point in their genotype sequence
 *
 * PARAMETERS
 *
 *  *node_str osaka1 -- the head of 1 osaka object
 *  *node_str osaka2 -- the head of another osaka object
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * crossover_onepoint_macro(osaka1, osaka2, false);
 *
 * SIDE-EFFECT
 *
 *  edits osaka1 and osaka2
 *
 */

void crossover_onepoint_macro(node_str* osaka1, node_str* osaka2, bool vis) {

    if (vis) {
        printf("\nPerforming onepoint crossover on individuals starting at %d and %d ---------------------\n", UID(osaka1), UID(osaka2));
    }

    uint32_t random = 1;
    uint32_t osaka1_length = osaka_listlength(osaka1);
    uint32_t osaka2_length = osaka_listlength(osaka2);

    if (vis) {
        printf("\n Individual 1 before crossover: ------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka1);
        printf("\n\n Individual 2 before crossover: ------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka2);
    }

    // we don't want the random number to exceed the length
    // of the shorter osaka sequence
    if (osaka1_length < osaka2_length) {
        while (random <= 1) {
            random = (uint32_t) (osaka1_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
    }
    else {
        while (random <= 1) {
            random = (uint32_t) (osaka2_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
    }

    if (vis) {
        printf("\n\n------------------------- splitting is to be done at point %d -------------------------\n", random);

        printf("\nPlanned crossover points: ------------------------------------------------------------\n\n");
        visualization_print_individual_concise_details_to_nth(osaka1, random);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth(osaka1, random);
        printf("\n\n");
        visualization_print_individual_concise_details_to_nth(osaka2, random);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth(osaka2, random);
    }

    // the same point is used in both osaka sequences
    node_str* nth_osaka1 = osaka_nthnode(osaka1, random);
    node_str* nth_osaka2 = osaka_nthnode(osaka2, random);

    // swap is implemented by changing the "last" and "next" pointers
    // starting with the "next" pointers of the last nodes
    node_str* osaka1_last = LAST(nth_osaka1);
    node_str* osaka2_last = LAST(nth_osaka2);
    NEXT(osaka1_last) = nth_osaka2;
    NEXT(osaka2_last) = nth_osaka1;
    // and then the "last" pointers of the current nodes
    LAST(nth_osaka1) = osaka2_last;
    LAST(nth_osaka2) = osaka1_last;

    if (vis) {
        printf("\n\nIndividual 1 after crossover: --------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka1);
        printf("\n\nIndividual 2 after crossover: --------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka2);
        printf("\n\n");

        printf("\nCrossover complete -------------------------------------------------------------------\n\n");
    }

}

/*
 * NAME
 *
 *   crossover_twopoint_basic
 *
 * DESCRIPTION
 *
 *  Takes in two osaka individuals to be evolved and splices
 *  them at 2 points in their genotype sequence
 *
 * PARAMETERS
 *
 *  *node_str osaka1 -- the head of 1 osaka object
 *  *node_str osaka2 -- the head of another osaka object
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * crossover_twopoint_basic(osaka1, osaka2, true);
 *
 * SIDE-EFFECT
 *
 *  edits osaka1 and osaka2
 *
 */

void crossover_twopoint_basic(node_str* osaka1, node_str* osaka2, bool vis) {

    // implementation for onepoint crossover can be reused here
    // as the only difference if that two points are used
    // instead of just one

    crossover_onepoint_macro(osaka1, osaka2, vis);
    crossover_onepoint_macro(osaka1, osaka2, vis);

}

/*
 * NAME
 *
 *   crossover_twopoint_diff
 *
 * DESCRIPTION
 *
 *  Takes in two osaka individuals to be evolved and splices
 *  them at 2 points in their genotype sequence. Guarantees that two
 *  separate points will be chosen, guaranteeing that there will be
 *  two new individuals created.
 *
 * PARAMETERS
 *
 *  *node_str osaka1 -- the head of 1 osaka object
 *  *node_str osaka2 -- the head of another osaka object
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * crossover_twopoint_diff(osaka1, osaka2, false);
 *
 * SIDE-EFFECT
 *
 *  edits osaka1 and osaka2
 *
 */

void crossover_twopoint_diff(node_str* osaka1, node_str* osaka2, bool vis) {

    if (vis) {
        printf("\nPerforming twopoint crossover on individuals starting at %d and %d ---------------------\n", UID(osaka1), UID(osaka2));
    }

    uint32_t random1;
    uint32_t random2;
    uint32_t osaka1_length = osaka_listlength(osaka1);
    uint32_t osaka2_length = osaka_listlength(osaka2);

    if (vis) {
        printf("\nIndividual 1 before crossover: -------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka1);
        printf("\n\nIndividual 2 before crossover: -------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka2);
    }

    // we don't want the random number to exceed the length
    // of the shorted osaka sequence
    if (osaka1_length < osaka2_length) {
        random1 = (uint32_t) (osaka1_length * (rand() / (RAND_MAX + 1.0))) + 1;
        while (random1 <= 1) {
            random1 = (uint32_t) (osaka1_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
        random2 = (uint32_t) (osaka1_length * (rand() / (RAND_MAX + 1.0))) + 1;
        // ensure that we are actually doing pure twopoint
        while (random1 == random2 || random2 <= 1) {
            random2 = (uint32_t) (osaka1_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
    }
    else {
        random1 = (uint32_t) (osaka2_length * (rand() / (RAND_MAX + 1.0))) + 1;
        while (random1 <= 1) {
            random1 = (uint32_t) (osaka2_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
        random2 = (uint32_t) (osaka2_length * (rand() / (RAND_MAX + 1.0))) + 1;
        // ensure that we are actually doing pure twopoint
        while (random1 == random2 || random2 <= 1) {
            random2 = (uint32_t) (osaka2_length * (rand() / (RAND_MAX + 1.0))) + 1;
        }
    }

    if (vis) {
        printf("\n\n--------------------- splitting is to be done at points %d and %d ----------------------\n", random1, random2);
        uint32_t first = random1;
        uint32_t second = random2;
        if (random1 > random2) {
            first = random2;
            second = random1;
        }
        printf("\nPlanned crossover points: ------------------------------------------------------------\n\n");
        visualization_print_individual_concise_details_to_nth(osaka1, first);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth_to_mth(osaka1, first, second);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth(osaka1, second);

        printf("\n\n");

        visualization_print_individual_concise_details_to_nth(osaka2, first);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth_to_mth(osaka2, first, second);
        printf(" <--///--> ");
        visualization_print_individual_concise_details_from_nth(osaka2, second);
    }

    // the same point is used in both osaka sequences
    node_str* nth_osaka1 = osaka_nthnode(osaka1, random1);
    node_str* nth_osaka2 = osaka_nthnode(osaka2, random1);

    // swap is implemented by changing the "last" and "next" pointers
    // starting with the "next" pointers of the last nodes
    node_str* osaka1_last = LAST(nth_osaka1);
    node_str* osaka2_last = LAST(nth_osaka2);
    NEXT(osaka1_last) = nth_osaka2;
    NEXT(osaka2_last) = nth_osaka1;
    // and then the "last" pointers of the current nodes
    LAST(nth_osaka1) = osaka2_last;
    LAST(nth_osaka2) = osaka1_last;

    // the same point is used in both osaka sequences
    node_str* nth_osaka3 = osaka_nthnode(osaka_findheadnode(nth_osaka1), random2);
    node_str* nth_osaka4 = osaka_nthnode(osaka_findheadnode(nth_osaka2), random2);

    // swap is implemented by changing the "last" and "next" pointers
    // starting with the "next" pointers of the last nodes
    node_str* osaka3_last = LAST(nth_osaka3);
    node_str* osaka4_last = LAST(nth_osaka4);
    NEXT(osaka3_last) = nth_osaka4;
    NEXT(osaka4_last) = nth_osaka3;
    // and then the "last" pointers of the current nodes
    LAST(nth_osaka3) = osaka4_last;
    LAST(nth_osaka4) = osaka3_last;

    if (vis) {
        printf("\n\nIndividual 1 after crossover: --------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka1);
        printf("\n\nIndividual 2 after crossover: --------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(osaka2);
        printf("\n\n");

        printf("\nCrossover complete -------------------------------------------------------------------\n\n");
    }

}