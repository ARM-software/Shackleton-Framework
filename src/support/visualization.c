/*
 ============================================================================
 Name        : visualization.c
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
    
 Description : Helper method for visualizing what is happening
               at any given time. Includes options to cache generations
               as we go and output individual nodes
 ============================================================================
 */

/*
 * IMPORT ...
 */

#include "visualization.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   visualization_print_individual_verbose
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual using the verbose internal
 *  osaka methods
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_verbose(osaka_indiv)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_verbose(node_str* indiv) {

    // only use internal methods through osaka
    osaka_printnodearray(indiv);

}

/*
 * NAME
 *
 *   visualization_print_individual_concise_addresses
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual concisely with its addresses
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_concise_addresses(osaka_indiv)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_concise_addresses(node_str* indiv) {

    printf("{ %p }", indiv);

    // only print pointer with <---> to represent connections
    while (NEXT(indiv) != NULL) {

        indiv = NEXT(indiv);
        printf(" <---> { %p }", indiv);

    }

}

/*
 * NAME
 *
 *   visualization_print_individual_concise_details
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual concisely with its details
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_concise_details(osaka_indiv)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_concise_details(node_str* indiv) {

    printf("{ ");
    osaka_printnode_concise(indiv);
    printf(" }");

    // using internal methods of osaka, with <---> representing connections
    while (NEXT(indiv) != NULL) {

        indiv = NEXT(indiv);
        printf(" <---> { ");
        osaka_printnode_concise(indiv);
        printf(" }");

    }

}

/*
 * NAME
 *
 *   visualization_print_individual_concise_details_to_nth
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual concisely with its details
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *  uint32_t nth -- node to stop at
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_concise_details_to_nth(osaka_indiv)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_concise_details_to_nth(node_str* indiv, uint32_t nth) {

    printf("{ ");
    osaka_printnode_concise(indiv);
    printf(" }");

    uint32_t curr = 2;

    // using internal methods of osaka, with <---> representing connections
    while (NEXT(indiv) != NULL && curr < nth) {

        printf(" <---> { ");
        indiv = NEXT(indiv);
        osaka_printnode_concise(indiv);
        printf(" }");

        curr++;

    }

}

/*
 * NAME
 *
 *   visualization_print_individual_concise_details_from_nth
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual concisely with its details
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *  uint32_t nth -- node to start from
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_concise_details_from_nth(osaka_indiv, 7)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_concise_details_from_nth(node_str* indiv, uint32_t nth) {

    indiv = osaka_nthnode(indiv, nth);

    printf("{ ");
    osaka_printnode_concise(indiv);
    printf(" }");

    // using internal methods of osaka, with <---> representing connections
    while (NEXT(indiv) != NULL) {

        printf(" <---> { ");
        indiv = NEXT(indiv);
        osaka_printnode_concise(indiv);
        printf(" }");

    }

}

/*
 * NAME
 *
 *   visualization_print_individual_concise_details_from_nth_to_mth
 *
 * DESCRIPTION
 *
 *  Given a pointer to the head of an osaka individual,
 *  prints the individual concisely with its details
 *
 * PARAMETERS
 *
 *  node_str* indiv -- osaka structure to print
 *  uint32_t nth -- node to start at
 *  uint32_t mth -- node to stop at
 *
 * RETURN
 *
 *  void
 *
 * EXAMPLE
 *
 * visualization_print_individual_concise_details_from_nth_to_mth(osaka_indiv, 2, 6)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void visualization_print_individual_concise_details_from_nth_to_mth(node_str* indiv, uint32_t nth, uint32_t mth) {

    indiv = osaka_nthnode(indiv, nth);

    printf("{ ");
    osaka_printnode_concise(indiv);
    printf(" }");

    uint32_t curr = 1;

    // using internal methods of osaka, with <---> representing connections
    while (NEXT(indiv) != NULL && curr < nth) {

        printf(" <---> { ");
        indiv = NEXT(indiv);
        osaka_printnode_concise(indiv);
        printf(" }");

        curr++;

    }

}

void vis_print_parents(bool vis, node_str** offsprings) {
    //if vis, print out contestant information
    if (vis) {
        printf("Contestant 1 starts at node %d\n", UID(offsprings[0]));
        visualization_print_individual_concise_details(offsprings[0]);
        printf("\n\nContestant 2 starts at node %d\n\n", UID(offsprings[1]));
        visualization_print_individual_concise_details(offsprings[1]);
        printf("\n");
    }
}

void vis_best_node(bool vis, node_str* final_node) {
    if (vis) {
        printf("Best node: ---------------------------------------------------------------------------\n\n");
        visualization_print_individual_concise_details(final_node);
        printf("\n\n--------------------------------------------------------------------------------------\n\n");
    }
}

void vis_print_gen(bool vis, bool end_of_gen, node_str** current_generation, uint32_t gen_idx, uint32_t pop_size) {
    if (!vis) {
        return;
    }
    char msg[200];
    for (int i = 0; i < pop_size; i++) {
        if (end_of_gen) {
            sprintf(msg, "------------------- Printing Individual %d at end of Generation %d --------------------\n\n", i + 1, gen_idx + 1);
        } else {
            sprintf(msg, "----------------------- Printing Individual %d before beginning -----------------------\n\n", i + 1);
        }
        printf("%s", msg);
        visualization_print_individual_concise_details(current_generation[i]);
        printf("\n\n");
    }
}

void vis_itr(bool vis, int it, int gen) {
    if (vis) {
        printf("---------------------------- Iteration %d of Generation %d ----------------------------\n", it + 1, gen + 1);
    }
}