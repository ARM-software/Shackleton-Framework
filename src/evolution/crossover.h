/*
 ============================================================================
 Name        : crossover.h
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

#ifndef EVOLUTION_CROSSOVER_H_
#define EVOLUTION_CROSSOVER_H_

/*
 * IMPORT
 */

#include "../osaka/osaka.h"
#include "../support/visualization.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void crossover_onepoint_macro(node_str* osaka1, node_str* osaka2, bool vis);

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

void crossover_twopoint_basic(node_str* osaka1, node_str* osaka2, bool vis);

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

void crossover_twopoint_diff(node_str* osaka1, node_str* osaka2, bool vis);

#endif /* EVOLUTION_CROSSOVER_H_ */