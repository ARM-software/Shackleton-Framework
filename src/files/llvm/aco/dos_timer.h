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
      File:    times.h
      Author:  Thomas Stuetzle
      Purpose: routines for measuring elapsed time (CPU or real)
      Check:   README.txt and legal.txt
*/

extern clock_t start_time;

extern double elapsed;

int time_expired();

void start_timers();

double elapsed_time();

typedef enum type_timer {REAL, VIRTUAL} TIMER_TYPE;

