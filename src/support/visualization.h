/*
 ============================================================================
 Name        : visualization.h
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

#ifndef SUPPORT_VISUALIZATION_H_
#define SUPPORT_VISUALIZATION_H_

/*
 * IMPORT ...
 */

#include "../osaka/osaka.h"

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

void visualization_print_individual_verbose(node_str* indiv);

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

void visualization_print_individual_concise_addresses(node_str* indiv);

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

void visualization_print_individual_concise_details(node_str* indiv);

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

void visualization_print_individual_concise_details_to_nth(node_str* indiv, uint32_t nth);

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

void visualization_print_individual_concise_details_from_nth(node_str* indiv, uint32_t nth);

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

void visualization_print_individual_concise_details_from_nth_to_mth(node_str* indiv, uint32_t nth, uint32_t mth);

void vis_print_parents(bool vis, node_str** offsprings);
void vis_best_node(bool vis, node_str* final_node);
void vis_print_gen(bool vis, bool end_of_gen, node_str** current_generation, uint32_t gen_idx, uint32_t pop_size);
void vis_itr(bool vis, int it, int gen);

#endif /* SUPPORT_VISUALIZATION_H_ */