/*
 ============================================================================
 Name        : mutation.h
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
    
 Description : Macro and Micro mutations that allow us to change a 
               single individual 
 ============================================================================
 */

#ifndef EVOLUTION_MUTATION_H_
#define EVOLUTION_MUTATION_H_

/*
 * IMPORT
 */

#include "../osaka/osaka.h"
#include "../support/visualization.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   mutation_single_unit_all_params
 *
 * DESCRIPTION
 *
 *  Takes in a single individual and changes the values
 *  of all parameters associated with that individual
 *
 * PARAMETERS
 *
 *  *node_str osaka -- the head of the individual
 *  uint32_t -- the index of the unit to change in the individual
 *  bool vis -- whether or not visualization is enabled
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * mutation_single_unit_all_params(osaka, 5, true);
 *
 * SIDE-EFFECT
 *
 *  edits osaka
 *
 */

void mutation_single_unit_all_params(node_str* osaka, uint32_t ind, bool vis);

/*
 * NAME
 *
 *   mutation_single_unit_single_param
 *
 * DESCRIPTION
 *
 *  Takes in a single individual and changes the value of
 *  one parameter of a single unit at random
 *
 * PARAMETERS
 *
 *  *node_str osaka -- the head of the individual
 *  uint32_t -- the index of the unit to change in the individual
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * mutation_single_unit_single_param(osaka, 6);
 *
 * SIDE-EFFECT
 *
 *  edits osaka
 *
 */

void mutation_single_unit_single_param(node_str* osaka, uint32_t ind);

#endif /* EVOLUTION_MUTATION_H_ */