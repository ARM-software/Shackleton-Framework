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
      File:    InOut.c
      Author:  Thomas Stuetzle
      Purpose: mainly input / output / statistic routines
      Check:   README and gpl.txt
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "InOut.h"
#include "TSP.h"
#include "timer.h"
#include "utilities.h"
#include "ants.h"
#include "ls.h"
#include "parse.h"


long int *best_in_try;
long int *best_found_at;
double   *time_best_found;
double   *time_total_run;

long int n_try;             /* try counter */
long int n_tours;           /* counter of number constructed tours */
long int iteration;         /* iteration counter */
long int restart_iteration; /* remember iteration when restart was done if any */
double   restart_time;      /* remember time when restart was done if any */
long int max_tries;         /* maximum number of independent tries */
long int max_tours;         /* maximum number of tour constructions in one try */

double   lambda;            /* Parameter to determine branching factor */
double   branch_fac;        /* If branching factor < branch_fac => update trails */

double   max_time;          /* maximal allowed run time of a try  */
double   time_used;         /* time used until some given event */
double   time_passed;       /* time passed until some moment*/
long int optimal;           /* optimal solution or bound to find */


double   mean_ants;         /* average tour length */
double   stddev_ants;       /* stddev of tour lengths */
double   branching_factor;  /* average node branching factor when searching */
double   found_branching;   /* branching factor when best solution is found */

long int found_best;        /* iteration in which best solution is found */
long int restart_found_best;/* iteration in which restart-best solution is found */

/* ------------------------------------------------------------------------ */

FILE *report, *comp_report, *stat_report;

char name_buf[LINE_BUF_LEN];
int  opt;



struct point * read_etsp(const char *tsp_file_name) 
/*    
      FUNCTION: parse and read instance file
      INPUT:    instance name
      OUTPUT:   list of coordinates for all nodes
      COMMENTS: Instance files have to be in TSPLIB format, otherwise procedure fails
*/
{
    FILE         *tsp_file;
    char         buf[LINE_BUF_LEN];
    long int     i, j;
    struct point *nodeptr;

    tsp_file = fopen(tsp_file_name, "r");
    if ( tsp_file == NULL ) {
	fprintf(stderr,"No instance file specified, abort\n");
	exit(1);
    }
    assert(tsp_file != NULL);
    //printf("\nreading tsp-file %s ... \n", tsp_file_name);

    fscanf(tsp_file,"%s", buf);
    while ( strcmp("NODE_COORD_SECTION", buf) != 0 ) {
	if ( strcmp("NAME", buf) == 0 ) {
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s ", buf); )
	    fscanf(tsp_file, "%s", buf);
	    strcpy(instance.name, buf);
	    TRACE ( printf("%s \n", instance.name); )
	    buf[0]=0;
	}
	else if ( strcmp("NAME:", buf) == 0 ) {
	    fscanf(tsp_file, "%s", buf);
	    strcpy(instance.name, buf);
	    TRACE ( printf("%s \n", instance.name); )
	    buf[0]=0;
	}
	else if ( strcmp("COMMENT", buf) == 0 ){
	    fgets(buf, LINE_BUF_LEN, tsp_file);
	    TRACE ( printf("%s", buf); )
	    buf[0]=0;
	}
	else if ( strcmp("COMMENT:", buf) == 0 ){
	    fgets(buf, LINE_BUF_LEN, tsp_file);
	    TRACE ( printf("%s", buf); )
	    buf[0]=0;
	}
	else if ( strcmp("TYPE", buf) == 0 ) {
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s ", buf); )
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s\n", buf); )
	    if( strcmp("TSP", buf) != 0 ) {
		fprintf(stderr,"\n Not a TSP instance in TSPLIB format !!\n");
		exit(1);
	    }
	    buf[0]=0;
	}
	else if ( strcmp("TYPE:", buf) == 0 ) {
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s\n", buf); )
	    if( strcmp("TSP", buf) != 0 ) {
		fprintf(stderr,"\n Not a TSP instance in TSPLIB format !!\n");
		exit(1);
	    }
	    buf[0]=0;
	}
	else if( strcmp("DIMENSION", buf) == 0 ){
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s ", buf); );
	    fscanf(tsp_file, "%ld", &n);
	    instance.n = n;
	    TRACE ( printf("%ld\n", n); );
	    assert ( n > 2 && n < 6000);
	    buf[0]=0;
	}
	else if ( strcmp("DIMENSION:", buf) == 0 ) {
	    fscanf(tsp_file, "%ld", &n);
	    instance.n = n;
	    TRACE ( printf("%ld\n", n); );
	    assert ( n > 2 && n < 6000);
	    buf[0]=0;
	}
	else if( strcmp("DISPLAY_DATA_TYPE", buf) == 0 ){
	    fgets(buf, LINE_BUF_LEN, tsp_file);
	    TRACE ( printf("%s", buf); );
	    buf[0]=0;
	}
	else if ( strcmp("DISPLAY_DATA_TYPE:", buf) == 0 ) {
	    fgets(buf, LINE_BUF_LEN, tsp_file);
	    TRACE ( printf("%s", buf); );
	    buf[0]=0;
	}
	else if( strcmp("EDGE_WEIGHT_TYPE", buf) == 0 ){
	    buf[0]=0;
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s ", buf); );
	    buf[0]=0;
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s\n", buf); );
	    if ( strcmp("EUC_2D", buf) == 0 ) {
		distance = round_distance;
	    }
	    else if ( strcmp("CEIL_2D", buf) == 0 ) {
		distance = ceil_distance;
	    }
	    else if ( strcmp("GEO", buf) == 0 ) {
		distance = geo_distance;
	    }
	    else if ( strcmp("ATT", buf) == 0 ) {
		distance = att_distance;
	    }
	    else if ( strcmp("EUC_TOROID", buf) == 0 ) {
	        distance = toroid_distance;
	   }
	    else
		fprintf(stderr,"EDGE_WEIGHT_TYPE %s not implemented\n",buf);
	    strcpy(instance.edge_weight_type, buf);
	    buf[0]=0;
	}
	else if( strcmp("EDGE_WEIGHT_TYPE:", buf) == 0 ){
	    /* set pointer to appropriate distance function; has to be one of 
	       EUC_2D, CEIL_2D, GEO, ATT or EUC_TOROID. Everything else fails */
	    buf[0]=0;
	    fscanf(tsp_file, "%s", buf);
	    TRACE ( printf("%s\n", buf); )
		printf("EDGE_WEIGHT_TYPE: %s\n", buf);
	    if ( strcmp("EUC_2D", buf) == 0 ) {
		distance = round_distance;
	    }
	    else if ( strcmp("CEIL_2D", buf) == 0 ) {
		distance = ceil_distance;
	    }
	    else if ( strcmp("GEO", buf) == 0 ) {
		distance = geo_distance;
	    }
	    else if ( strcmp("ATT", buf) == 0 ) {
		distance = att_distance;
	    }
	    else if ( strcmp("EUC_TOROID", buf) == 0 ) {
	        distance = toroid_distance;
	   }
	    else {
		fprintf(stderr,"EDGE_WEIGHT_TYPE %s not implemented\n",buf);
		exit(1);
	    }
	    strcpy(instance.edge_weight_type, buf);
	    buf[0]=0;
	}
	buf[0]=0;
	fscanf(tsp_file,"%s", buf);
    }


    if( strcmp("NODE_COORD_SECTION", buf) == 0 ){
	TRACE ( printf("found section contaning the node coordinates\n"); )
	    }
    else{
	fprintf(stderr,"\n\nSome error ocurred finding start of coordinates from tsp file !!\n");
	exit(1);
    }

    if( (nodeptr = malloc(sizeof(struct point) * n)) == NULL )
	exit(EXIT_FAILURE);
    else {
	for ( i = 0 ; i < n ; i++ ) {
	    fscanf(tsp_file,"%ld %lf %lf", &j, &nodeptr[i].x, &nodeptr[i].y );
	}
    }
    TRACE ( printf("number of cities is %ld\n",n); )
    TRACE ( printf("\n... done\n"); )
	return (nodeptr);
}



void write_report( void )
/*    
      FUNCTION: output some info about trial (best-so-far solution quality, time)
      INPUT:    none
      OUTPUT:   none
      COMMENTS: none
*/
{
    //printf("best %ld, iteration: %ld, time %.2f\n",(*best_so_far_ant).tour_length,iteration,elapsed_time( VIRTUAL));  //disabled 6/9/2021 for cleaner terminal
    fprintf(comp_report,"best %ld\t iteration %ld\t tours %ld\t time %.3f\n",(*best_so_far_ant).tour_length,iteration,n_tours,time_used);
}



void print_default_parameters() 
/*    
      FUNCTION: output default parameter settings
      INPUT:    none
      OUTPUT:   none
      COMMENTS: none
*/
{
    fprintf(stderr,"\nDefault parameter settings are:\n\n");
    fprintf(stderr,"max_tries\t\t %ld\n", max_tries);
    fprintf(stderr,"max_tours\t\t %ld\n", max_tours);
    fprintf(stderr,"max_time\t\t %.2f\n", max_time);
    fprintf(stderr,"optimum\t\t\t %ld\n", optimal);
    fprintf(stderr,"n_ants\t\t\t %ld\n", n_ants);
    fprintf(stderr,"nn_ants\t\t\t %ld\n", nn_ants);
    fprintf(stderr,"alpha\t\t\t %.2f\n", alpha);
    fprintf(stderr,"beta\t\t\t %.2f\n", beta);
    fprintf(stderr,"rho\t\t\t %.2f\n", rho);
    fprintf(stderr,"q_0\t\t\t %.2f\n", q_0);
    fprintf(stderr,"elitist_ants\t\t 0\n");
    fprintf(stderr,"ras_ranks\t\t 6\n");
    fprintf(stderr,"ls_flag\t\t\t %ld\n", ls_flag);
    fprintf(stderr,"nn_ls\t\t\t %ld\n", nn_ls);
    fprintf(stderr,"dlb_flag\t\t %ld\n", dlb_flag);
    fprintf(stderr,"as_flag\t\t\t %ld\n", as_flag);
    fprintf(stderr,"eas_flag\t\t %ld\n", eas_flag);
    fprintf(stderr,"ras_flag\t\t %ld\n", ras_flag);
    fprintf(stderr,"mmas_flag\t\t %ld\n", mmas_flag);
    fprintf(stderr,"bwas_flag\t\t %ld\n", bwas_flag);
    fprintf(stderr,"acs_flag\t\t %ld\n", acs_flag);
}



void set_default_parameters() 
/*    
      FUNCTION: set default parameter settings
      INPUT:    none
      OUTPUT:   none
      COMMENTS: none
*/
{
    ls_flag        = 3;     /* per default run 3-opt*/
    dlb_flag       = TRUE;  /* apply don't look bits in local search */
    nn_ls          = 20;    /* use fixed radius search in the 20 nearest neighbours */
    n_ants         = 25;    /* number of ants */
    nn_ants        = 20;    /* number of nearest neighbours in tour construction */
    alpha          = 1.0;
    beta           = 2.0;
    rho            = 0.5;
    q_0            = 0.0;
    max_tries      = 1;    // Changed to 5 on 6/14/2021, was 10  // Changed to 1 on 7/14/2021
    max_tours      = 100;
    max_time       = 10.0;
    optimal        = 1;
    branch_fac     = 1.00001;
    as_flag        = FALSE;
    eas_flag       = FALSE;
    ras_flag       = FALSE;
    mmas_flag      = TRUE; 
    u_gb           = INFTY;
    bwas_flag      = FALSE; 
    acs_flag       = FALSE;
    ras_ranks      = 6;
    elitist_ants   = 100;
}



void population_statistics ( void )
/*    
      FUNCTION:       compute some population statistics like average tour length, 
                      standard deviations, average distance, branching-factor and 
		      output to a file gathering statistics
      INPUT:          none
      OUTPUT:         none
      (SIDE)EFFECTS:  none
*/
{
    long int j, k;
    long int *l;
    double   pop_mean, pop_stddev, avg_distance = 0.0;
    
    l = calloc(n_ants, sizeof(long int));
    for( k = 0 ; k < n_ants ; k++ ) {
	l[k] = ant[k].tour_length;
    }
    
    pop_mean = mean( l, n_ants);
    pop_stddev = std_deviation( l, n_ants, pop_mean );
    branching_factor = node_branching(lambda);
    
    for ( k = 0 ; k < n_ants-1 ; k++ ) 
	for ( j = k+1 ; j < n_ants ; j++) {
	    avg_distance += (double)distance_between_ants( &ant[k], &ant[j]);
	}
    avg_distance /= ((double)n_ants * (double)(n_ants-1) / 2.); 
    

    fprintf(stat_report,"%ld\t%.1f\t%.5f\t%.7f\t%.5f\t%.1f\t%.1f\t%.5f\n",iteration, pop_mean, pop_stddev, pop_stddev / pop_mean, branching_factor,  (branching_factor - 1.) * (double)n, avg_distance, avg_distance / (double)n);
}



double node_branching(double l) 
/*    
      FUNCTION:       compute the average node lambda-branching factor 
      INPUT:          lambda value 
      OUTPUT:         average node branching factor 
      (SIDE)EFFECTS:  none
      COMMENTS:       see the ACO book for a definition of the average node 
                      lambda-branching factor 
*/
{
  long int  i, m;
  double    min, max, cutoff;
  double    avg;
  double    *num_branches;

  num_branches = calloc(n, sizeof(double));

  for ( m = 0 ; m < n ; m++ ) {
    /* determine max, min to calculate the cutoff value */
    min = pheromone[m][instance.nn_list[m][1]];
    max = pheromone[m][instance.nn_list[m][1]];
    for ( i = 1 ; i < nn_ants ; i++ ) {
      if ( pheromone[m][instance.nn_list[m][i]] > max )
	max = pheromone[m][instance.nn_list[m][i]];
      if ( pheromone[m][instance.nn_list[m][i]] < min )
	min = pheromone[m][instance.nn_list[m][i]];
    }
    cutoff = min + l * (max - min);
    
    for ( i = 0 ; i < nn_ants ; i++ ) {    
      if ( pheromone[m][instance.nn_list[m][i]] > cutoff )
	num_branches[m] += 1.;
    }
  }
  avg = 0.;
  for ( m = 0 ; m < n ; m++ ) {
    avg += num_branches[m];
  }
  free ( num_branches );
  /* Norm branching factor to minimal value 1 */
  return ( avg / (double) (n * 2)  );
}



void output_solution( void ) 
/*    
      FUNCTION:       output a solution together with node coordinates
      INPUT:          none
      OUTPUT:         none
      COMMENTS:       not used in the default implementation but may be useful anyway
*/
{

    long int i;
    
    for ( i = 0 ; i < n ; i++ ) {
	fprintf(stat_report," %ld %f %f\n",(*best_so_far_ant).tour[i],instance.nodeptr[(*best_so_far_ant).tour[i]].x, instance.nodeptr[(*best_so_far_ant).tour[i]].y);
    }
    //printf("\n"); 
}



void exit_try( long int ntry ) 
/*    
      FUNCTION:       save some statistical information on a trial once it finishes
      INPUT:          trial number
      OUTPUT:         none
      COMMENTS:       
*/
{
  checkTour( (*best_so_far_ant).tour );
/*    printTourFile( (*best_so_far_ant).tour ); */

  //disabled 6/9/2021 for cleaner terminal
  //printf("\n Best Solution in try %ld is %ld\n",ntry, (*best_so_far_ant).tour_length);
  fprintf(report,"Best: %ld\t Iterations: %6ld\t B-Fac %.5f\t Time %.2f\t Tot.time %.2f\n", (*best_so_far_ant).tour_length, found_best, found_branching, time_used, elapsed_time( VIRTUAL ));
  //printf(" Best Solution was found after %ld iterations\n", found_best);

  best_in_try[ntry] = (*best_so_far_ant).tour_length;
  best_found_at[ntry] = found_best;
  time_best_found[ntry] = time_used;
  time_total_run[ntry] = elapsed_time( VIRTUAL );
  //printf("try %ld, Best %ld, found at iteration %ld, found at time %f\n",ntry, best_in_try[ntry], best_found_at[ntry], time_best_found[ntry]);

  fprintf(comp_report,"end try %ld\n\n",ntry);
  fprintf(stat_report,"end try %ld\n\n",ntry);
  output_solution();
  fflush(report); 
  fflush(comp_report); 
  fflush(stat_report); 

}



void exit_program( void ) 
/*    
      FUNCTION:       save some final statistical information on a trial once it finishes
      INPUT:          none
      OUTPUT:         none
      COMMENTS:       
*/
{
  long int best_tour_length, worst_tour_length;
  double   t_avgbest, t_stdbest, t_avgtotal, t_stdtotal;
  double   avg_sol_quality = 0., avg_cyc_to_bst = 0., stddev_best, stddev_iterations;

  best_tour_length = best_of_vector( best_in_try ,max_tries );
  worst_tour_length = worst_of_vector( best_in_try , max_tries );

  avg_cyc_to_bst = mean( best_found_at , max_tries );
  stddev_iterations = std_deviation( best_found_at, max_tries, avg_cyc_to_bst );

  avg_sol_quality = mean( best_in_try , max_tries );
  stddev_best = std_deviation( best_in_try, max_tries, avg_sol_quality);

  t_avgbest = meanr( time_best_found, max_tries );
  //printf(" t_avgbest = %f\n", t_avgbest );
  t_stdbest = std_deviationr( time_best_found, max_tries, t_avgbest);

  t_avgtotal = meanr( time_total_run, max_tries );
  //printf(" t_avgtotal = %f\n", t_avgtotal );
  t_stdtotal = std_deviationr( time_total_run, max_tries, t_avgtotal);

  fprintf(report,"\nAverage-Best: %.2f\t Average-Iterations: %.2f", avg_sol_quality, avg_cyc_to_bst);
  fprintf(report,"\nStddev-Best: %.2f \t Stddev Iterations: %.2f", stddev_best, stddev_iterations);
  fprintf(report,"\nBest try: %ld\t\t Worst try: %ld\n", best_tour_length, worst_tour_length);
  fprintf(report,"\nAvg.time-best: %.2f stddev.time-best: %.2f\n", t_avgbest, t_stdbest);  
  fprintf(report,"\nAvg.time-total: %.2f stddev.time-total: %.2f\n", t_avgtotal, t_stdtotal); 

  if ( optimal > 0 ) {
    fprintf(report," excess best = %f, excess average = %f, excess worst = %f\n",(double)(best_tour_length - optimal) / (double)optimal,(double)(avg_sol_quality - optimal) / (double)optimal,(double)(worst_tour_length - optimal) / (double)optimal);
  }

  fprintf(comp_report,"end problem %s\n",instance.name);
}



void init_program( long int argc, char *argv[] ) 
/*    
      FUNCTION:       initialize the program, 
      INPUT:          program arguments, needed for parsing commandline
      OUTPUT:         none
      COMMENTS:       
*/
{

  char temp_buffer[LINE_BUF_LEN + 5];

  printf(PROG_ID_STR);
  set_default_parameters();
  setbuf(stdout,NULL);
  parse_commandline(argc, argv);

  assert (n_ants < MAX_ANTS-1);
  assert (nn_ants < MAX_NEIGHBOURS);
  assert (nn_ants > 0);
  assert (nn_ls > 0);
  assert (max_tries <= MAXIMUM_NO_TRIES);
  
  best_in_try = calloc(max_tries, sizeof(long int));
  best_found_at = calloc(max_tries, sizeof(long int));
  time_best_found = calloc(max_tries, sizeof(double));
  time_total_run = calloc(max_tries, sizeof(double));
   
  seed = (long int) time( NULL );
  
  TRACE ( printf("read problem data  ..\n\n"); )
  instance.nodeptr = read_etsp(name_buf);
  TRACE ( printf("\n .. done\n\n"); )

  nn_ls = MIN(n-1,nn_ls);
  
  sprintf(temp_buffer,"best.%s",instance.name);
  TRACE ( printf("%s\n",temp_buffer); )
  report = fopen(temp_buffer, "w");
  sprintf(temp_buffer,"cmp.%s",instance.name);
  TRACE ( printf("%s\n",temp_buffer); )
  comp_report = fopen(temp_buffer, "w");
  sprintf(temp_buffer,"stat.%s",instance.name);
  TRACE ( printf("%s\n",temp_buffer); )
  stat_report = fopen(temp_buffer, "w");
   
  //printf("calculating distance matrix ..\n");
  instance.distance = compute_distances();
  //printf(" .. done\n");
  write_params();
  fprintf(comp_report,"begin problem %s\n",name_buf);
  //printf("allocating ants' memory ..\n");
  allocate_ants();
  //printf(" .. done\n");
  DEBUG ( assert ( nn_ls < n && 0 < nn_ls ); )

  //printf("\nFinally set ACO algorithm specific parameters, typically done as proposed in literature\n\n");
  /* default setting for elitist_ants is 0; if EAS is applied and
     option elitist_ants is not used, we set the default to
     elitist_ants = n */
  if ( eas_flag && elitist_ants == 0 )
    elitist_ants = n;
}



void printDist(void) 
/*    
      FUNCTION:       print distance matrix 
      INPUT:          none
      OUTPUT:         none
*/
{
  long int i,j;

  printf("Distance Matrix:\n");
  for ( i = 0 ; i < n ; i++) {
    printf("From %ld:  ",i);
    for ( j = 0 ; j < n - 1 ; j++ ) {
      printf(" %ld", instance.distance[i][j]);
    }
    printf(" %ld\n", instance.distance[i][n-1]);
    printf("\n");
  }
  printf("\n");
}



void printHeur(void) 
/*    
      FUNCTION:       print heuristic information 
      INPUT:          none
      OUTPUT:         none
*/
{
  long int i, j;

  printf("Heuristic information:\n");
  for ( i = 0 ; i < n ; i++) {
    printf("From %ld:  ",i);
    for ( j = 0 ; j < n - 1 ; j++ ) {
      printf(" %.3f ", HEURISTIC(i,j));
    }
    printf(" %.3f\n", HEURISTIC(i,j));
    printf("\n");
  }
  printf("\n");
}



void printTrail(void) 
/*    
      FUNCTION:       print pheromone trail values 
      INPUT:          none
      OUTPUT:         none
*/
{
  long int i,j;

  printf("pheromone Trail matrix, iteration: %ld\n\n",iteration);
  for ( i = 0 ; i < n ; i++) {
    printf("From %ld:  ",i);
    for ( j = 0 ; j < n ; j++ ) {
      printf(" %.10f ", pheromone[i][j]);
      if ( pheromone[i][j] > 1.0 )
	printf("XXXXX\n");
    }
    printf("\n");
  }
  printf("\n");
}



void printTotal(void) 
/*    
      FUNCTION:       print values of pheromone times heuristic information 
      INPUT:          none
      OUTPUT:         none
*/
{
  long int i, j;

  printf("combined pheromone and heuristic info\n\n");
  for (i=0; i < n; i++) {
    for (j = 0; j < n - 1 ; j++) {
      printf(" %.15f &", total[i][j]);
      if ( total[i][j] > 1.0 )
	printf("XXXXX\n");
    }
    printf(" %.15f\n", total[i][n-1]);
    if ( total[i][n-1] > 1.0 )
      printf("XXXXX\n");
  }
  printf("\n");
}



void printProbabilities(void) 
/*    
      FUNCTION:       prints the selection probabilities as encountered by an ant 
      INPUT:          none
      OUTPUT:         none
      COMMENTS:       this computation assumes that no choice has been made yet. 
*/
{
  long int i, j;
  double   *p;
  double   sum_prob;

  printf("Selection Probabilities, iteration: %ld\n",iteration);
  p = calloc( n, sizeof(double) );

  for (i=0; i < n; i++) {
    printf("From %ld:  ",i);
    sum_prob = 0.;
    for ( j = 0 ; j < n ; j++) {
      if ( i == j )
	p[j] = 0.;
      else
	p[j] = total[i][j];
      sum_prob += p[j];
    }
    for ( j = 0 ; j < n ; j++) {
      p[j] = p[j] / sum_prob;
    }
    for ( j = 0 ; j < n-1 ; j++) {
      printf(" %.5f ", p[j]);
    }
    printf(" %.5f\n", p[n-1]);
    if (!(j % 26)) {
      printf("\n");
    }
    printf("\n");
  }
  printf("\n");
  free ( p );
}



void printTour( long int *t ) 
/*    
      FUNCTION:       print the tour *t
      INPUT:          pointer to a tour
      OUTPUT:         none
*/
{
    long int   i;

    printf("\n");
    for( i = 0 ; i <= n ; i++ ) {
	if (!i%25)
	    printf("\n");
	printf("%ld ", t[i]);
    }
    printf("\n");
    printf("Tour length = %ld\n\n",compute_tour_length( t ));
}



void printTourFile( long int *t ) 
/*    
      FUNCTION:       print the tour *t to cmp.tsplibfile
      INPUT:          pointer to a tour
      OUTPUT:         none
*/
{
    long int   i;

    fprintf(comp_report,"begin solution\n");
    for( i = 0 ; i < n ; i++ ) {
	fprintf(comp_report,"%ld ", t[i]);
    }
    fprintf(comp_report,"\n");
    fprintf(comp_report,"Tour length %ld\n",compute_tour_length( t ));
    fprintf(comp_report,"end solution\n");
}



void checkTour( long int *t ) 
/*    
      FUNCTION:       make a simple check whether tour *t can be feasible
      INPUT:          pointer to a tour
      OUTPUT:         none
*/
{
    long int   i, sum=0;

    for( i = 0 ; i < n ; i++ ) {
	sum += t[i];
    }
    if ( sum != (n-1) * n / 2 ) {
	fprintf(stderr,"Next tour must be flawed !!\n");
	printTour( t );
	exit(1);
    }
}



void write_params( void ) 
/*    
      FUNCTION:       writes chosen parameter settings in standard output and in 
                      report files 
      INPUT:          none
      OUTPUT:         none
*/
{
  /*printf("\nParameter-settings: \n\n");
  printf("max-tries %ld\n", max_tries);
  printf("max-tours %ld\n", max_tours);
  printf("optimum %ld\n", optimal);
  printf("time %f\n", max_time);
  printf("num-ants %ld\n", n_ants);
  printf("num-neigh %ld\n", nn_ants);
  printf("alpha %f\n", alpha);
  printf("beta %f\n", beta);
  printf("rho %f\n", rho);
  printf("q_0 %f\n", q_0);
  printf("branch-up %f\n", branch_fac);
  printf("ls_flag %ld\n", ls_flag);
  printf("nn_ls %ld\n", nn_ls);
  printf("dlb_flag %ld\n", dlb_flag);
  printf("as_flag %ld\n", as_flag);
  printf("eas_flag %ld\n", eas_flag);
  printf("ras_flag %ld\n", ras_flag);
  printf("mmas_flag %ld\n", mmas_flag);
  printf("bwas_flag %ld\n", bwas_flag);
  printf("acs_flag %ld\n", acs_flag);
  printf("\n");*/  //disabled for cleaner command line 6/10/2021
  fprintf(report,"\nParameter-settings: \n\n");
  fprintf(report,"max-tries %ld\n", max_tries);
  fprintf(report,"max-tours %ld\n", max_tours);
  fprintf(report,"optimum %ld\n", optimal);
  fprintf(report,"time %f\n", max_time);
  fprintf(report,"num-ants %ld\n", n_ants);
  fprintf(report,"num-neigh %ld\n", nn_ants);
  fprintf(report,"alpha %f\n", alpha);
  fprintf(report,"beta %f\n", beta);
  fprintf(report,"rho %f\n", rho);
  fprintf(report,"q_0 %f\n", q_0);
  fprintf(report,"branch-up %f\n", branch_fac);
  fprintf(report,"ls_flag %ld\n", ls_flag);
  fprintf(report,"nn_ls %ld\n", nn_ls);
  fprintf(report,"dlb_flag %ld\n", dlb_flag);
  fprintf(report,"as_flag %ld\n", as_flag);
  fprintf(report,"eas_flag %ld\n", eas_flag);
  fprintf(report,"ras_flag %ld\n", ras_flag);
  fprintf(report,"mmas_flag %ld\n", mmas_flag);
  fprintf(report,"bwas_flag %ld\n", bwas_flag);
  fprintf(report,"acs_flag %ld\n", acs_flag);
  fprintf(report,"\n");
  fprintf(comp_report,"%s",PROG_ID_STR);
  fprintf(comp_report,"\nParameter-settings: \n\n");
  fprintf(comp_report,"max-tries %ld\n", max_tries);
  fprintf(comp_report,"max-tours %ld\n", max_tours);
  fprintf(comp_report,"optimum %ld\n", optimal);
  fprintf(comp_report,"time %f\n", max_time);
  fprintf(comp_report,"num-ants %ld\n", n_ants);
  fprintf(comp_report,"num-neigh %ld\n", nn_ants);
  fprintf(comp_report,"alpha %f\n", alpha);
  fprintf(comp_report,"beta %f\n", beta);
  fprintf(comp_report,"rho %f\n", rho);
  fprintf(comp_report,"q_0 %f\n", q_0);
  fprintf(comp_report,"branch-up %f\n", branch_fac);
  fprintf(comp_report,"ls_flag %ld\n", ls_flag);
  fprintf(comp_report,"nn_ls %ld\n", nn_ls);
  fprintf(comp_report,"dlb_flag %ld\n", dlb_flag);
  fprintf(comp_report,"as_flag %ld\n", as_flag);
  fprintf(comp_report,"eas_flag %ld\n", eas_flag);
  fprintf(comp_report,"ras_flag %ld\n", ras_flag);
  fprintf(comp_report,"mmas_flag %ld\n", mmas_flag);
  fprintf(comp_report,"bwas_flag %ld\n", bwas_flag);
  fprintf(comp_report,"acs_flag %ld\n", acs_flag);
  fprintf(comp_report,"\n");
}











