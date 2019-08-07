/*

       AAAA    CCCC   OOOO   TTTTTT   SSSSS  PPPPP
      AA  AA  CC     OO  OO    TT    SS      PP  PP
      AAAAAA  CC     OO  OO    TT     SSSS   PPPPP
      AA  AA  CC     OO  OO    TT        SS  PP
      AA  AA   CCCC   OOOO     TT    SSSSS   PP

######################################################
##########    ACO algorithms for the TSP    ##########
######################################################

      Version: 1.0
      File:    utilities.h
      Author:  Thomas Stuetzle
      Purpose: some additional useful procedures
      Check:   README.txt and legal.txt
      Copyright (C) 2002  Thomas Stuetzle
*/


/***************************************************************************

    Program's name: acotsp

    Ant Colony Optimization algorithms (AS, ACS, EAS, RAS, MMAS, BWAS) for the 
    symmetric TSP 

    Copyright (C) 2004  Thomas Stuetzle

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    email: stuetzle no@spam informatik.tu-darmstadt.de
    mail address: Universitaet Darmstadt
                  Fachbereich Informatik
                  Hochschulstr. 10
                  D-64283 Darmstadt
		  Germany

***************************************************************************/

#define INFTY                 LONG_MAX
#define MAXIMUM_NO_TRIES      100

#define TRUE  1
#define FALSE 0

/* general macros */

#define MAX(x,y)        ((x)>=(y)?(x):(y))
#define MIN(x,y)        ((x)<=(y)?(x):(y))

#define DEBUG( x )

#define TRACE( x )

/* constants for a random number generator, for details see numerical recipes in C */

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

extern long int seed;

double mean ( long int *values, long int max);

double meanr ( double *values, long int max );

double std_deviation ( long int *values, long int i, double mean );

double std_deviationr ( double *values, long int i, double mean );

long int best_of_vector ( long int *values, long int i );

long int worst_of_vector ( long int *values, long int i );

void swap ( long int v[], long int i, long int j );

void sort ( long int v[], long int left, long int right );

double quantil ( long int vector[], double q, long int numbers );

void swap2(long int v[], long int v2[], long int i, long int j);

void sort2(long int v[], long int v2[], long int left, long int right);

double ran01 ( long *idum );

long int random_number ( long *idum );

long int ** generate_int_matrix( long int n, long int m);

double ** generate_double_matrix( long int n, long int m);
