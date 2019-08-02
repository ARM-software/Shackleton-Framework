/*
 ============================================================================
 Name        : utility.c
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
    
 Description : File for any functions that can be used
               across the project for making code more
               reusable
 ============================================================================
 */

/*
 * IMPORT ...
 */

#include "utility.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *   str2int
 *
 * DESCRIPTION
 *
 *  Takes in a string and outputs the same value
 *  but now as an int
 *
 * PARAMETERS
 *
 *  uint32_t* out
 *  char* s
 *  uint32_t base
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * hstr2int(out, s, 10)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

str2int_errno str2int(uint32_t *out, char *s, uint32_t base) {

    char *end;

    if (s[0] == '\0' || isspace(s[0])) {

        return STR2INT_INCONVERTIBLE;

    }

    errno = 0;
    long l = strtol(s, &end, base);

    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX)) {
        
        return STR2INT_OVERFLOW;

    }
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN)) {

        return STR2INT_UNDERFLOW;

    }
    if (*end != '\0') {

        return STR2INT_INCONVERTIBLE;

    }

    *out = l;
    return STR2INT_SUCCESS;

}

/*
 * NAME
 *
 *   swap
 *
 * DESCRIPTION
 *
 *  Reverses a string
 *
 * PARAMETERS
 *
 *  char* temp1
 *  char* temp2
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * swap(temp, temp1)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void swap(char* temp1, char* temp2) {

    char* temp;
    *temp = *temp1;
    *temp1 = *temp2;
    *temp2 = *temp;

} 

/*
 * NAME
 *
 *   reverse
 *
 * DESCRIPTION
 *
 *  Reverses a string
 *
 * PARAMETERS
 *
 *  char str[]
 *  uint32_t length
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * reverse(str, len)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void reverse(char str[], uint32_t length) {

    uint32_t start = 0; 
    uint32_t end = length -1;

    while (start < end) {

        swap((str+start), (str+end)); 
        start++; 
        end--; 
    
    } 

} 

/*
 * NAME
 *
 *   itoa
 *
 * DESCRIPTION
 *
 *  Converts an uint32_t to a string
 *
 * PARAMETERS
 *
 *  uint32_t num
 *  char* str
 *  uint32_t base
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * itoa(3, number, 10)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

char* itoa(uint32_t num, char* str, uint32_t base) {

    uint32_t i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) {

        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) {

        isNegative = true; 
        num = -num; 
    
    } 
  
    // Process individual digits 
    while (num != 0) {

        uint32_t rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    
    } 
  
    // If number is negative, append '-' 
    if (isNegative) {

        str[i++] = '-'; 
    }

    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
    
} 

/*
 * NAME
 *
 *   strupr
 *
 * DESCRIPTION
 *
 *  Converts a string to all upper case
 *
 * PARAMETERS
 *
 *  char* orig
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * strupr(orig)
 *
 * SIDE-EFFECT
 *
 *  none
 *
 */

void strupr(char* orig) {

    uint32_t i = 0;
 
	while (orig[i] != '\0') {

    	if (orig[i] >= 'a' && orig[i] <= 'z') {

        	orig[i] = orig[i] - 32;
    	
        }

      	i++;
	
    }

}

/*
 * NAME
 *
 *  getJSON
 *
 * DESCRIPTION
 *
 *  Creates a cJSON item from a filename given
 *
 * PARAMETERS
 *
 *  char* filename
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * cJSON *json = getJSON(filename);
 *
 * SIDE-EFFECT
 *
 *  mallocs, must be freed
 *
 */

cJSON* getJSON(char* filename) {

    // variables for reading parameter file
    FILE *json;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    char file[5000];
    strcpy(file, "");

    // open parameters file for reading
    json = fopen(filename, "r");

    if (json == NULL) {

        exit(EXIT_FAILURE);
    
    }
    
    // only nead to read the lines as they are
    while ((read = getline(&line, &len, json)) != -1) {
    
        strcat(file, line);
   
    }

    // do the parsing and close all other variables
    cJSON *root = cJSON_Parse(file);
    free(line);
    fclose(json);

    return root;

}

/*
 * NAME
 *
 *  randomString
 *
 * DESCRIPTION
 *
 *  Creates a random string given a target length
 *
 * PARAMETERS
 *
 *  uint32_t length
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * char* new_string = randomString(10);
 *
 * SIDE-EFFECT
 *
 *  mallocs a new string that must be freed at some point
 *
 */

char *randomString(uint32_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) {

        randomString = malloc(sizeof(char) * (length + 1));

        if (randomString) {

            for (uint32_t n = 0; n < length; n++) {   

                uint32_t key = rand() % (uint32_t)(sizeof(charset) - 1);
                randomString[n] = charset[key];

            }

            randomString[length] = '\0';

        }

    }

    return randomString;

}

/*
 * NAME
 *
 *  set_params_from_file
 *
 * DESCRIPTION
 *
 *  Given a parameters file that is predetermined to be in 
 *  src/files/, will use the parameter values in that file
 *  to be the parameters for 
 *
 * PARAMETERS
 *
 *  uint32_t num_gen
 *  uint32_t pop_size
 *  uint32_t perc_cross
 *  uint32_t perc_mut
 *  uint32_t tourn_size
 *  bool vis
 *
 * RETURN
 *
 *  none
 *
 * EXAMPLE
 *
 * set_params_from_file(num_generations, num_population_size, percent_crossover, percent_mutation, tournament_size, visualization);
 *
 * SIDE-EFFECT
 *
 *  Resets all params within main based on the values in params file
 *
 */

void set_params_from_file(uint32_t *num_gen, uint32_t *pop_size, uint32_t *perc_cross, uint32_t *perc_mut, uint32_t *tourn_size, bool *vis) {

    FILE *file;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    char filename[30];
    strcpy(filename, "src/files/parameters.txt");

    file = fopen(filename, "r");

    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    
    // read osaka.h line by line
    while ((read = getline(&line, &len, file)) != -1) {

        char* temp;
        char delim[] = " ";
        
        temp = strtok(line, delim);

        while (temp != NULL) {

            if (strcmp(temp, "num_generations:") == 0) {
                printf("\tsetting num_generations from file\n");
                temp = strtok(NULL, delim);
                temp[strlen(temp) - 2] = '\0';
                str2int(num_gen, temp, 10);
            }
            else if (strcmp(temp, "num_population_size:") == 0) {
                printf("\tsetting num_population_size from file\n");
                temp = strtok(NULL, delim);
                temp[strlen(temp) - 2] = '\0';
                str2int(pop_size, temp, 10);
            }
            else if (strcmp(temp, "percent_crossover:") == 0) {
                printf("\tsetting percent_crossover from file\n");
                temp = strtok(NULL, delim);
                temp[strlen(temp) - 2] = '\0';
                str2int(perc_cross, temp, 10);
            }
            else if (strcmp(temp, "percent_mutation:") == 0) {
                printf("\tsetting percent_mutation from file\n");
                temp = strtok(NULL, delim);
                temp[strlen(temp) - 2] = '\0';
                str2int(perc_mut, temp, 10);
            }
            else if (strcmp(temp, "tournament_size:") == 0) {
                printf("\tsetting tournament_size from file\n");
                temp = strtok(NULL, delim);
                temp[strlen(temp) - 2] = '\0';
                str2int(tourn_size, temp, 10);
            }
            else if (strcmp(temp, "visualization:") == 0) {
                printf("\tsetting visualization from file\n");
                temp = strtok(NULL, delim);
                if (strcmp(temp, "true") == 0) {
                    *vis = true;
                }
                else {
                    *vis = false;
                }
            }
            else {
                temp = strtok(NULL, delim);
            }

        }

    }

    // free line and close file, return true for success
    free(line);
    fclose(file);

}