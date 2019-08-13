/* This file has been generated with opag 0.6.4.  */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>


#include "InOut.h"
#include "utilities.h"
#include "ants.h"
#include "ls.h"


#ifndef STR_ERR_UNKNOWN_LONG_OPT
# define STR_ERR_UNKNOWN_LONG_OPT   "%s: unrecognized option `--%s'\n"
#endif

#ifndef STR_ERR_LONG_OPT_AMBIGUOUS
# define STR_ERR_LONG_OPT_AMBIGUOUS "%s: option `--%s' is ambiguous\n"
#endif

#ifndef STR_ERR_MISSING_ARG_LONG
# define STR_ERR_MISSING_ARG_LONG   "%s: option `--%s' requires an argument\n"
#endif

#ifndef STR_ERR_UNEXPEC_ARG_LONG
# define STR_ERR_UNEXPEC_ARG_LONG   "%s: option `--%s' doesn't allow an argument\n"
#endif

#ifndef STR_ERR_UNKNOWN_SHORT_OPT
# define STR_ERR_UNKNOWN_SHORT_OPT  "%s: unrecognized option `-%c'\n"
#endif

#ifndef STR_ERR_MISSING_ARG_SHORT
# define STR_ERR_MISSING_ARG_SHORT  "%s: option `-%c' requires an argument\n"
#endif

#define STR_HELP_TRIES \
  "  -r, --tries          # number of independent trials\n"

#define STR_HELP_TOURS \
  "  -s, --tours          # number of steps in each trial\n"

#define STR_HELP_TIME \
  "  -t, --time           # maximum time for each trial\n"

#define STR_HELP_TSPLIBFILE \
  "  -i, --tsplibfile     f inputfile (TSPLIB format necessary)\n"

#define STR_HELP_OPTIMUM \
  "  -o, --optimum        # stop if tour better or equal optimum is found\n"

#define STR_HELP_ANTS \
  "  -m, --ants           # number of ants\n"

#define STR_HELP_NNANTS \
  "  -g, --nnants         # nearest neighbours in tour construction\n"

#define STR_HELP_ALPHA \
  "  -a, --alpha          # alpha (influence of pheromone trails)\n"

#define STR_HELP_BETA \
  "  -b, --beta           # beta (influence of heuristic information)\n"

#define STR_HELP_RHO \
  "  -e, --rho            # rho: pheromone trail evaporation\n"

#define STR_HELP_Q0 \
  "  -q, --q0             # q_0: prob. of best choice in tour construction\n"

#define STR_HELP_ELITISTANTS \
  "  -c, --elitistants    # number of elitist ants\n"

#define STR_HELP_RASRANKS \
  "  -f, --rasranks       # number of ranks in rank-based Ant System\n"

#define STR_HELP_NNLS \
  "  -k, --nnls           # No. of nearest neighbors for local search\n"

#define STR_HELP_LOCALSEARCH \
  "  -l, --localsearch    0: no local search   1: 2-opt   2: 2.5-opt   3: 3-opt\n"

#define STR_HELP_DLB \
  "  -d, --dlb            1 use don't look bits in local search\n"

#define STR_HELP_AS \
  "  -u, --as              apply basic Ant System\n"

#define STR_HELP_EAS \
  "  -v, --eas             apply elitist Ant System\n"

#define STR_HELP_RAS \
  "  -w, --ras             apply rank-based version of Ant System\n"

#define STR_HELP_MMAS \
  "  -x, --mmas            apply MAX-MIN ant system\n"

#define STR_HELP_BWAS \
  "  -y, --bwas            apply best-worst ant system\n"

#define STR_HELP_ACS \
  "  -z, --acs             apply ant colony system\n"

#define STR_HELP_HELP \
  "  -h, --help            display this help text and exit\n"

#define STR_HELP \
  STR_HELP_TRIES \
  STR_HELP_TOURS \
  STR_HELP_TIME \
  STR_HELP_TSPLIBFILE \
  STR_HELP_OPTIMUM \
  STR_HELP_ANTS \
  STR_HELP_NNANTS \
  STR_HELP_ALPHA \
  STR_HELP_BETA \
  STR_HELP_RHO \
  STR_HELP_Q0 \
  STR_HELP_ELITISTANTS \
  STR_HELP_RASRANKS \
  STR_HELP_NNLS \
  STR_HELP_LOCALSEARCH \
  STR_HELP_DLB \
  STR_HELP_AS \
  STR_HELP_EAS \
  STR_HELP_RAS \
  STR_HELP_MMAS \
  STR_HELP_BWAS \
  STR_HELP_ACS \
  STR_HELP_HELP

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
int parse_options (struct options *const options, const char *const program_name, const int argc, char **const argv)
{
  static const char *const optstr__tries = "tries";
  static const char *const optstr__tours = "tours";
  static const char *const optstr__time = "time";
  static const char *const optstr__tsplibfile = "tsplibfile";
  static const char *const optstr__optimum = "optimum";
  static const char *const optstr__ants = "ants";
  static const char *const optstr__nnants = "nnants";
  static const char *const optstr__alpha = "alpha";
  static const char *const optstr__beta = "beta";
  static const char *const optstr__rho = "rho";
  static const char *const optstr__q0 = "q0";
  static const char *const optstr__elitistants = "elitistants";
  static const char *const optstr__rasranks = "rasranks";
  static const char *const optstr__nnls = "nnls";
  static const char *const optstr__localsearch = "localsearch";
  static const char *const optstr__dlb = "dlb";
  static const char *const optstr__as = "as";
  static const char *const optstr__eas = "eas";
  static const char *const optstr__ras = "ras";
  static const char *const optstr__mmas = "mmas";
  static const char *const optstr__bwas = "bwas";
  static const char *const optstr__acs = "acs";
  static const char *const optstr__help = "help";
  int i = 0;
  options->opt_tries = 0;
  options->opt_tours = 0;
  options->opt_time = 0;
  options->opt_tsplibfile = 0;
  options->opt_optimum = 0;
  options->opt_ants = 0;
  options->opt_nnants = 0;
  options->opt_alpha = 0;
  options->opt_beta = 0;
  options->opt_rho = 0;
  options->opt_q0 = 0;
  options->opt_elitistants = 0;
  options->opt_rasranks = 0;
  options->opt_nnls = 0;
  options->opt_localsearch = 0;
  options->opt_dlb = 0;
  options->opt_as = 0;
  options->opt_eas = 0;
  options->opt_ras = 0;
  options->opt_mmas = 0;
  options->opt_bwas = 0;
  options->opt_acs = 0;
  options->opt_help = 0;
  options->arg_tries = 0;
  options->arg_tours = 0;
  options->arg_time = 0;
  options->arg_tsplibfile = 0;
  options->arg_optimum = 0;
  options->arg_ants = 0;
  options->arg_nnants = 0;
  options->arg_alpha = 0;
  options->arg_beta = 0;
  options->arg_rho = 0;
  options->arg_q0 = 0;
  options->arg_elitistants = 0;
  options->arg_rasranks = 0;
  options->arg_nnls = 0;
  options->arg_localsearch = 0;
  options->arg_dlb = 0;
  while (++i < argc)
  {
    const char *option = argv [i];
    if (*option != '-')
      return i;
    else if (*++option == '\0')
      return i;
    else if (*option == '-')
    {
      const char *argument;
      size_t option_len;
      ++option;
      if ((argument = strchr (option, '=')) == option)
        goto error_unknown_long_opt;
      else if (argument == 0)
        option_len = strlen (option);
      else
        option_len = argument++ - option;
      switch (*option)
      {
       case '\0':
        return i + 1;
       case 'a':
        if (strncmp (option + 1, optstr__acs + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
          {
            option = optstr__acs;
            goto error_unexpec_arg_long;
          }
          options->opt_acs = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__alpha + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_alpha = argument;
          else if (++i < argc)
            options->arg_alpha = argv [i];
          else
          {
            option = optstr__alpha;
            goto error_missing_arg_long;
          }
          options->opt_alpha = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__ants + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_ants = argument;
          else if (++i < argc)
            options->arg_ants = argv [i];
          else
          {
            option = optstr__ants;
            goto error_missing_arg_long;
          }
          options->opt_ants = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__as + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
          {
            option = optstr__as;
            goto error_unexpec_arg_long;
          }
          options->opt_as = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'b':
        if (strncmp (option + 1, optstr__beta + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_beta = argument;
          else if (++i < argc)
            options->arg_beta = argv [i];
          else
          {
            option = optstr__beta;
            goto error_missing_arg_long;
          }
          options->opt_beta = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__bwas + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
          {
            option = optstr__bwas;
            goto error_unexpec_arg_long;
          }
          options->opt_bwas = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'd':
        if (strncmp (option + 1, optstr__dlb + 1, option_len - 1) == 0)
        {
          if (argument != 0)
            options->arg_dlb = argument;
          else if (++i < argc)
            options->arg_dlb = argv [i];
          else
          {
            option = optstr__dlb;
            goto error_missing_arg_long;
          }
          options->opt_dlb = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'e':
        if (strncmp (option + 1, optstr__eas + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
          {
            option = optstr__eas;
            goto error_unexpec_arg_long;
          }
          options->opt_eas = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__elitistants + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_elitistants = argument;
          else if (++i < argc)
            options->arg_elitistants = argv [i];
          else
          {
            option = optstr__elitistants;
            goto error_missing_arg_long;
          }
          options->opt_elitistants = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'h':
        if (strncmp (option + 1, optstr__help + 1, option_len - 1) == 0)
        {
          if (argument != 0)
          {
            option = optstr__help;
            goto error_unexpec_arg_long;
          }
          options->opt_help = 1;
          return i + 1;
        }
        goto error_unknown_long_opt;
       case 'l':
        if (strncmp (option + 1, optstr__localsearch + 1, option_len - 1) == 0)
        {
          if (argument != 0)
            options->arg_localsearch = argument;
          else if (++i < argc)
            options->arg_localsearch = argv [i];
          else
          {
            option = optstr__localsearch;
            goto error_missing_arg_long;
          }
          options->opt_localsearch = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'm':
        if (strncmp (option + 1, optstr__mmas + 1, option_len - 1) == 0)
        {
          if (argument != 0)
          {
            option = optstr__mmas;
            goto error_unexpec_arg_long;
          }
          options->opt_mmas = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'n':
        if (strncmp (option + 1, optstr__nnants + 1, option_len - 1) == 0)
        {
          if (option_len <= 2)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_nnants = argument;
          else if (++i < argc)
            options->arg_nnants = argv [i];
          else
          {
            option = optstr__nnants;
            goto error_missing_arg_long;
          }
          options->opt_nnants = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__nnls + 1, option_len - 1) == 0)
        {
          if (option_len <= 2)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_nnls = argument;
          else if (++i < argc)
            options->arg_nnls = argv [i];
          else
          {
            option = optstr__nnls;
            goto error_missing_arg_long;
          }
          options->opt_nnls = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'o':
        if (strncmp (option + 1, optstr__optimum + 1, option_len - 1) == 0)
        {
          if (argument != 0)
            options->arg_optimum = argument;
          else if (++i < argc)
            options->arg_optimum = argv [i];
          else
          {
            option = optstr__optimum;
            goto error_missing_arg_long;
          }
          options->opt_optimum = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'q':
        if (strncmp (option + 1, optstr__q0 + 1, option_len - 1) == 0)
        {
          if (argument != 0)
            options->arg_q0 = argument;
          else if (++i < argc)
            options->arg_q0 = argv [i];
          else
          {
            option = optstr__q0;
            goto error_missing_arg_long;
          }
          options->opt_q0 = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 'r':
        if (strncmp (option + 1, optstr__ras + 1, option_len - 1) == 0)
        {
          if (option_len < 3)
            goto error_long_opt_ambiguous;
          if (argument != 0)
          {
            option = optstr__ras;
            goto error_unexpec_arg_long;
          }
          options->opt_ras = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__rasranks + 1, option_len - 1) == 0)
        {
          if (option_len <= 3)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_rasranks = argument;
          else if (++i < argc)
            options->arg_rasranks = argv [i];
          else
          {
            option = optstr__rasranks;
            goto error_missing_arg_long;
          }
          options->opt_rasranks = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__rho + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_rho = argument;
          else if (++i < argc)
            options->arg_rho = argv [i];
          else
          {
            option = optstr__rho;
            goto error_missing_arg_long;
          }
          options->opt_rho = 1;
          break;
        }
        goto error_unknown_long_opt;
       case 't':
        if (strncmp (option + 1, optstr__time + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_time = argument;
          else if (++i < argc)
            options->arg_time = argv [i];
          else
          {
            option = optstr__time;
            goto error_missing_arg_long;
          }
          options->opt_time = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__tours + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_tours = argument;
          else if (++i < argc)
            options->arg_tours = argv [i];
          else
          {
            option = optstr__tours;
            goto error_missing_arg_long;
          }
          options->opt_tours = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__tries + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_tries = argument;
          else if (++i < argc)
            options->arg_tries = argv [i];
          else
          {
            option = optstr__tries;
            goto error_missing_arg_long;
          }
          options->opt_tries = 1;
          break;
        }
        else if (strncmp (option + 1, optstr__tsplibfile + 1, option_len - 1) == 0)
        {
          if (option_len <= 1)
            goto error_long_opt_ambiguous;
          if (argument != 0)
            options->arg_tsplibfile = argument;
          else if (++i < argc)
            options->arg_tsplibfile = argv [i];
          else
          {
            option = optstr__tsplibfile;
            goto error_missing_arg_long;
          }
          options->opt_tsplibfile = 1;
          break;
        }
       default:
       error_unknown_long_opt:
        fprintf (stderr, STR_ERR_UNKNOWN_LONG_OPT, program_name, option);
        return -1;
       error_long_opt_ambiguous:
        fprintf (stderr, STR_ERR_LONG_OPT_AMBIGUOUS, program_name, option);
        return -1;
       error_missing_arg_long:
        fprintf (stderr, STR_ERR_MISSING_ARG_LONG, program_name, option);
        return -1;
       error_unexpec_arg_long:
        fprintf (stderr, STR_ERR_UNEXPEC_ARG_LONG, program_name, option);
        return -1;
      }
    }
    else
      do
      {
        switch (*option)
        {
         case 'a':
          if (option [1] != '\0')
            options->arg_alpha = option + 1;
          else if (++i < argc)
            options->arg_alpha = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_alpha = 1;
          break;
         case 'b':
          if (option [1] != '\0')
            options->arg_beta = option + 1;
          else if (++i < argc)
            options->arg_beta = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_beta = 1;
          break;
         case 'c':
          if (option [1] != '\0')
            options->arg_elitistants = option + 1;
          else if (++i < argc)
            options->arg_elitistants = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_elitistants = 1;
          break;
         case 'd':
          if (option [1] != '\0')
            options->arg_dlb = option + 1;
          else if (++i < argc)
            options->arg_dlb = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_dlb = 1;
          break;
         case 'e':
          if (option [1] != '\0')
            options->arg_rho = option + 1;
          else if (++i < argc)
            options->arg_rho = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_rho = 1;
          break;
         case 'f':
          if (option [1] != '\0')
            options->arg_rasranks = option + 1;
          else if (++i < argc)
            options->arg_rasranks = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_rasranks = 1;
          break;
         case 'g':
          if (option [1] != '\0')
            options->arg_nnants = option + 1;
          else if (++i < argc)
            options->arg_nnants = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_nnants = 1;
          break;
         case 'h':
          options->opt_help = 1;
          return i + 1;
         case 'i':
          if (option [1] != '\0')
            options->arg_tsplibfile = option + 1;
          else if (++i < argc)
            options->arg_tsplibfile = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_tsplibfile = 1;
          break;
         case 'k':
          if (option [1] != '\0')
            options->arg_nnls = option + 1;
          else if (++i < argc)
            options->arg_nnls = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_nnls = 1;
          break;
         case 'l':
          if (option [1] != '\0')
            options->arg_localsearch = option + 1;
          else if (++i < argc)
            options->arg_localsearch = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_localsearch = 1;
          break;
         case 'm':
          if (option [1] != '\0')
            options->arg_ants = option + 1;
          else if (++i < argc)
            options->arg_ants = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_ants = 1;
          break;
         case 'o':
          if (option [1] != '\0')
            options->arg_optimum = option + 1;
          else if (++i < argc)
            options->arg_optimum = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_optimum = 1;
          break;
         case 'q':
          if (option [1] != '\0')
            options->arg_q0 = option + 1;
          else if (++i < argc)
            options->arg_q0 = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_q0 = 1;
          break;
         case 'r':
          if (option [1] != '\0')
            options->arg_tries = option + 1;
          else if (++i < argc)
            options->arg_tries = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_tries = 1;
          break;
         case 's':
          if (option [1] != '\0')
            options->arg_tours = option + 1;
          else if (++i < argc)
            options->arg_tours = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_tours = 1;
          break;
         case 't':
          if (option [1] != '\0')
            options->arg_time = option + 1;
          else if (++i < argc)
            options->arg_time = argv [i];
          else
            goto error_missing_arg_short;
          option = "\0";
          options->opt_time = 1;
          break;
         case 'u':
          options->opt_as = 1;
          break;
         case 'v':
          options->opt_eas = 1;
          break;
         case 'w':
          options->opt_ras = 1;
          break;
         case 'x':
          options->opt_mmas = 1;
          break;
         case 'y':
          options->opt_bwas = 1;
          break;
         case 'z':
          options->opt_acs = 1;
          break;
         default:
          fprintf (stderr, STR_ERR_UNKNOWN_SHORT_OPT, program_name, *option);
          return -1;
         error_missing_arg_short:
          fprintf (stderr, STR_ERR_MISSING_ARG_SHORT, program_name, *option);
          return -1;
        }
      } while (*++option != '\0');
  }
  return i;
}

void check_out_of_range ( double value, double MIN, double MAX, char *optionName ) 
/*    
      FUNCTION: check whether parameter values are within allowed range
      INPUT:    none
      OUTPUT:   none
      COMMENTS: none
*/
{
  if ((value<MIN)||(value>MAX)){
    fprintf(stderr,"Error: Option `%s' out of range\n",optionName);
    exit(1);
  }
}

int parse_commandline (int argc, char *argv [])
{
    int i;
    const char *progname;
    struct options options;
 
    progname = argv [0] != NULL && *(argv [0]) != '\0'
	? argv [0]
	: "acotsp";

    i = parse_options (&options, progname, argc, argv);

    if (i < 2)
    {
	fprintf (stderr, "No options are specified\n");
	fprintf (stderr, "Try `%s --help' for more information.\n",
		 progname);
	exit(1);
    }

    if (options.opt_help)
    {
	printf ("Usage: %s [OPTION]... [ARGUMENT]...\n\n"
		"Options:\n" STR_HELP, progname);
	exit(0);
    }

    puts ("\t OPTIONS:");



    if ( options.opt_time ) {
	max_time = atof(options.arg_time);
	fputs ("  -t  --time ", stdout);
	if (options.arg_time != NULL)
	    printf ("with argument \"%.3f\"\n", max_time);
	check_out_of_range( max_time, 0.0, 86400., "max_time (seconds)");
    } else {
	fprintf(stderr,"\tNote: time limit is set to default 10 seconds\n");
    }



    if ( options.opt_tries ) {
	max_tries = atol(options.arg_tries);
	fputs ("  -r  --tries ", stdout);
	if (options.arg_tries != NULL)
	    printf ("with argument \"%ld\"\n", max_tries);
	check_out_of_range( max_tries, 1, MAXIMUM_NO_TRIES, "max_tries (tries)");
    } else {
	max_tries = 10;
	fprintf(stderr,"\tNote: number or trials is set to default 10\n");
    }



    if ( options.opt_tours ) {
	max_tours = atol(options.arg_tours);
	fputs ("  -s  --tours ", stdout);
	if (options.arg_tries != NULL)
	    printf ("with argument \"%ld\"\n", max_tours);
	check_out_of_range( max_tours, 1, LONG_MAX, "max_tries (tries)");
    } else {
	max_tours = 100;
	fprintf(stderr,"\tNote: maximum number tours is set to default 100\n");
    }



    if ( options.opt_optimum )
    {
	optimal = atol(options.arg_optimum);
 	fputs ("  -o  --optimum ", stdout);
	if (options.arg_optimum != NULL)
	    printf ("with argument \"%ld\"\n", optimal);
    } else {
	optimal = 1;
	fprintf(stderr,"\tNote: optimal solution value is set to default 1\n");
    }



    if ( options.opt_tsplibfile )
    {
	strncpy( name_buf, options.arg_tsplibfile, strlen( options.arg_tsplibfile ) );
 	fputs ("  -i  --tsplibfile ", stdout);
	if (options.arg_tsplibfile != NULL)
	    printf ("with argument \"%s\"\n", name_buf );
    }



    if ( options.opt_ants ) {
	n_ants = atol(options.arg_ants);
	fputs ("  -m  --ants ", stdout);
	if (options.arg_ants != NULL)
	    printf ("with argument \"%ld\"\n", n_ants);
	check_out_of_range( n_ants, 1, MAX_ANTS-1, "n_ants");
    } else {
	n_ants = 25;
	fprintf(stderr,"\tNote: number or ants is set to default 25\n");
    }



    if ( options.opt_nnants ) {
	nn_ants = atol(options.arg_nnants);
	fputs ("  -m  --ants ", stdout);
	if (options.arg_ants != NULL)
	    printf ("with argument \"%ld\"\n", nn_ants);
	check_out_of_range( n_ants, 1, 100, "nn_ants");
    } else {
	nn_ants = 20;
	fprintf(stderr,"\tNote: number of nearest neighbours in tour construction is set to default 25\n");
    }



    if ( options.opt_alpha ) {
	alpha = atof(options.arg_alpha);
	fputs ("  -a  --alpha ", stdout);
	if (options.arg_alpha != NULL)
	    printf ("with argument \"%f\"\n", alpha);
	check_out_of_range( alpha, 0., 100., "alpha");
    } else {
	alpha = 1.0;
	fprintf(stderr,"\tNote: alpha is set to default 1.0\n");
    }



    if ( options.opt_beta ) {
	beta = atof(options.arg_beta);
	fputs ("  -b  --beta ", stdout);
	if (options.arg_beta != NULL)
	    printf ("with argument \"%f\"\n", beta);
	check_out_of_range( beta, 0., 100., "beta");
    } else {
	beta = 2.0;
	fprintf(stderr,"\tNote: beta is set to default 2.0\n");
    }



    if ( options.opt_rho ) {
	rho = atof(options.arg_rho);
	fputs ("  -e  --rho ", stdout);
	if (options.arg_rho != NULL)
	    printf ("with argument \"%f\"\n", rho);
	check_out_of_range( rho, 0., 1., "rho");
    } else {
	rho = 0.5;
	fprintf(stderr,"\tNote: rho is set to default 0.5\n");
    }



    if ( options.opt_q0 ) {
	q_0 = atof(options.arg_q0);
	fputs ("  -q  --q0 ", stdout);
	if (options.arg_q0 != NULL)
	    printf ("with argument \"%f\"\n", q_0);
	check_out_of_range( q_0, 0., 1., "q0");
    } else {
	q_0 = 0.0;
	fprintf(stderr,"\tNote: q_0 is set to default 0\n");
    }



    if ( options.opt_elitistants ) {
	elitist_ants = atol(options.arg_elitistants);
	fputs ("  -m  --ants ", stdout);
	if (options.arg_elitistants != NULL)
	    printf ("with argument \"%ld\"\n", elitist_ants);
	check_out_of_range( n_ants, 0, LONG_MAX, "elitistants");
    } else {
	elitist_ants = 100;
	fprintf(stderr,"\tNote: number of elitist ants is set to default 100\n");
    }



    if ( options.opt_rasranks ) {
	ras_ranks = atol(options.arg_rasranks);
	fputs ("  -m  --ants ", stdout);
	if (options.arg_rasranks != NULL)
	    printf ("with argument \"%ld\"\n", ras_ranks);
	check_out_of_range( n_ants, 0, LONG_MAX, "rasranks");
    } else {
	ras_ranks = 6;
	fprintf(stderr,"\tNote: number of ranks is set to default 6\n");
    }



    if ( options.opt_nnls ) {
	nn_ls = atol(options.arg_nnls);
	fputs ("  -k  --nnls ", stdout);
	if (options.arg_nnls != NULL)
	    printf ("with argument \"%ld\"\n", nn_ls);
	check_out_of_range( n_ants, 0, LONG_MAX, "nnls");
    } else {
	nn_ls = 20; 
	fprintf(stderr,"\tNote: number nearest neighbours in local search is set to default 20\n");
    }



    if ( options.opt_localsearch ) {
	ls_flag = atol(options.arg_localsearch);
	fputs ("  -l  --localsearch ", stdout);
	if (options.arg_localsearch != NULL)
	    printf ("with argument \"%ld\"\n", ls_flag);
	check_out_of_range( n_ants, 0, LONG_MAX, "ls_flag");
    } else {
	ls_flag = 3;
	fprintf(stderr,"\tNote: local search flag is set to default 3 (3-opt)\n");
    }



    if ( options.opt_dlb ) {
	dlb_flag = atol(options.arg_dlb);
	fputs ("  -d  --dlb ", stdout);
	if (options.arg_dlb != NULL)
	    printf ("with argument \"%ld\"\n", dlb_flag);
	check_out_of_range( dlb_flag, 0, 1, "dlb_flag");
    } else {
	dlb_flag = TRUE;
	fprintf(stderr,"\tNote: dlb flag is set to default 1 (use don't look bits)\n");
    }



    if ( options.opt_as ) {
	as_flag = TRUE;
	eas_flag = FALSE; ras_flag = FALSE; mmas_flag = FALSE; 
	bwas_flag = FALSE; acs_flag = FALSE;
	fprintf(stderr,"as_flag is set to 1, run Ant System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: as_flag is set to default 0 (don't run Ant System)\n"); */
    }



    if ( options.opt_eas ) {
	eas_flag = TRUE;
	as_flag = FALSE; ras_flag = FALSE; mmas_flag = FALSE; 
	bwas_flag = FALSE; acs_flag = FALSE;
	fprintf(stderr,"eas_flag is set to 1, run Elitist Ant System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: eas_flag is set to default 0 (don't run Elitist Ant System)\n"); */
    }



    if ( options.opt_ras ) {
	ras_flag = TRUE;
	as_flag = FALSE; eas_flag = FALSE; mmas_flag = FALSE; 
	bwas_flag = FALSE; acs_flag = FALSE;
	fprintf(stderr,"ras_flag is set to 1, run rank-based Ant System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: ras_flag is set to default 0 (don't run rank-based Ant System)\n"); */
    }



    if ( options.opt_mmas ) {
	mmas_flag = TRUE;
	as_flag = FALSE; eas_flag = FALSE; ras_flag = FALSE; 
	bwas_flag = FALSE; acs_flag = FALSE;
	fprintf(stderr,"mmas_flag is set to 1, run MAX-MIN Ant System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: mmas_flag is set to default 1 (run MAX-MIN Ant System!)\n"); */
    }



    if ( options.opt_bwas ) {
	bwas_flag = TRUE;
	as_flag = FALSE; eas_flag = FALSE; mmas_flag = FALSE; 
	ras_flag = FALSE; acs_flag = FALSE;
	fprintf(stderr,"bwas_flag is set to 1, run Best-Worst Ant System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: bwas_flag is set to default 0 (don't run Best-Worst Ant System)\n"); */
    }



    if ( options.opt_acs ) {
	acs_flag = TRUE;
	as_flag = FALSE; eas_flag = FALSE; mmas_flag = FALSE; 
	ras_flag = FALSE; bwas_flag = FALSE;
	fprintf(stderr,"acs_flag is set to 1, run Ant Colony System\n");
/*      } else { */
/*  	fprintf(stderr,"\tNote: acs_flag is set to default 0 (don't run Ant Colony System)\n"); */
    }


    puts ("Non-option arguments:");

    while (i < argc) {
	fprintf (stderr,"  \"%s\"\n", argv [i++]);
	fprintf (stderr,"\nThere were non-option arguments\n");
	fprintf (stderr,"I suspect there is something wrong, maybe wrong option name; exit\n");
	exit(1);
    }

    return 0;
}



