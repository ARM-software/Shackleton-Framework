/* This file has been generated with opag 0.6.4.  */

#ifndef HDR_PARSE
#define HDR_PARSE 1

struct options {

/* Set to 1 if option --tries (-r) has been specified.  */
unsigned int opt_tries : 1;

/* Set to 1 if option --tours (-s) has been specified.  */
unsigned int opt_tours : 1;

/* Set to 1 if option --time (-t) has been specified.  */
unsigned int opt_time : 1;

/* Set to 1 if option --tsplibfile (-i) has been specified.  */
unsigned int opt_tsplibfile : 1;

/* Set to 1 if option --optimum (-o) has been specified.  */
unsigned int opt_optimum : 1;

/* Set to 1 if option --ants (-m) has been specified.  */
unsigned int opt_ants : 1;

/* Set to 1 if option --nnants (-g) has been specified.  */
unsigned int opt_nnants : 1;

/* Set to 1 if option --alpha (-a) has been specified.  */
unsigned int opt_alpha : 1;

/* Set to 1 if option --beta (-b) has been specified.  */
unsigned int opt_beta : 1;

/* Set to 1 if option --rho (-e) has been specified.  */
unsigned int opt_rho : 1;

/* Set to 1 if option --q0 (-q) has been specified.  */
unsigned int opt_q0 : 1;

/* Set to 1 if option --elitistants (-c) has been specified.  */
unsigned int opt_elitistants : 1;

/* Set to 1 if option --rasranks (-f) has been specified.  */
unsigned int opt_rasranks : 1;

/* Set to 1 if option --nnls (-k) has been specified.  */
unsigned int opt_nnls : 1;

/* Set to 1 if option --localsearch (-l) has been specified.  */
unsigned int opt_localsearch : 1;

/* Set to 1 if option --dlb (-d) has been specified.  */
unsigned int opt_dlb : 1;

/* Set to 1 if option --as (-u) has been specified.  */
unsigned int opt_as : 1;

/* Set to 1 if option --eas (-v) has been specified.  */
unsigned int opt_eas : 1;

/* Set to 1 if option --ras (-w) has been specified.  */
unsigned int opt_ras : 1;

/* Set to 1 if option --mmas (-x) has been specified.  */
unsigned int opt_mmas : 1;

/* Set to 1 if option --bwas (-y) has been specified.  */
unsigned int opt_bwas : 1;

/* Set to 1 if option --acs (-z) has been specified.  */
unsigned int opt_acs : 1;

/* Set to 1 if option --help (-h) has been specified.  */
unsigned int opt_help : 1;

/* Argument to option --tries (-r).  */
const char *arg_tries;

/* Argument to option --tours (-s).  */
const char *arg_tours;

/* Argument to option --time (-t).  */
const char *arg_time;

/* Argument to option --tsplibfile (-i).  */
const char *arg_tsplibfile;

/* Argument to option --optimum (-o).  */
const char *arg_optimum;

/* Argument to option --ants (-m).  */
const char *arg_ants;

/* Argument to option --nnants (-g).  */
const char *arg_nnants;

/* Argument to option --alpha (-a).  */
const char *arg_alpha;

/* Argument to option --beta (-b).  */
const char *arg_beta;

/* Argument to option --rho (-e).  */
const char *arg_rho;

/* Argument to option --q0 (-q).  */
const char *arg_q0;

/* Argument to option --elitistants (-c).  */
const char *arg_elitistants;

/* Argument to option --rasranks (-f).  */
const char *arg_rasranks;

/* Argument to option --nnls (-k).  */
const char *arg_nnls;

/* Argument to option --localsearch (-l).  */
const char *arg_localsearch;

/* Argument to option --dlb (-d).  */
const char *arg_dlb;

};

/* Parse command line options.  Return index of first non-option argument,
   or -1 if an error is encountered.  */
extern int parse_options (struct options *options, const char *program_name, int argc, char **argv);

extern void check_out_of_range ( double value, double MIN, double MAX, char *optionName );

extern int parse_commandline (int argc, char *argv []);

#endif
