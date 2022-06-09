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
      File:    times.c
      Author:  Thomas Stuetzle
      Purpose: routines for measuring elapsed time (CPU or real)
      Check:   README.txt and legal.txt
      Copyright (C) 2004  Thomas Stuetzle
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



#include <stdio.h>
#include <time.h>

#include "timer.h"


clock_t start_time;

double elapsed;


void start_timers()
/*    
      FUNCTION:       virtual and real time of day are computed and stored to 
                      allow at later time the computation of the elapsed time 
		      (virtual or real) 
      INPUT:          none
      OUTPUT:         none
      (SIDE)EFFECTS:  virtual and real time are computed   
*/
{
    start_time = clock();
}



double elapsed_time( type )
	TIMER_TYPE type;
/*    
      FUNCTION:       return the time used in seconds (virtual or real, depending on type) 
      INPUT:          TIMER_TYPE (virtual or real time)
      OUTPUT:         seconds since last call to start_timers (virtual or real)
      (SIDE)EFFECTS:  none
*/
{
    elapsed = clock()- start_time;
    return elapsed / CLOCKS_PER_SEC;
}



