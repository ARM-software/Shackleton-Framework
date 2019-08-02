This directory houses any files that act as input to the Shackleton tool, either for parameters for a run of the tool or files that will be interacted with over the course of a run.

If you would like to use a parameters file rather than using the default parameters of the tool or entering them through the tool's command line interface, then you can use a parameters file. When the -parameters_file flag is used when calling the tool, the code will look in this directory for a file title parameters.txt. The paramaters.txt file's contents must be of this form:

------

num_generations: 20

num_population_size: 30

percent_crossover: 85

percent_mutation: 30

tournament_size: 5

visualization: true

-------

where each line shows a parameter flag and its desired value. If you want to know what flags are available, start the Shackleton tool with the -help flag to see your options and not run the tool, or start the Shackleton tool with no flags and you will recieve information on the available flags/parameters and their default values, with the option to still run the tool with user-inputed parameter values.

If you are using the LLVM-integrated portion of the tool for optimizing C or C++ code, you must start the tool with the -llvm_optimize flag. Any C or C++ files to be used in the tool should be put inside the llvm/ subdirectory in this directory. Any temporary output files created by using the Shackleton tool will appear in the llvm/junk_output subdirectory. Build files created that are permanant will remain in the llvm/ subdirectory along side the files that were created and put there before ever running the Shackleton tool.

The -cache option enables the code to cache information on each generation during an evolutionary run into a series of files. Some sample runs have been provided to illustrate the expected file structure that will result from runs. Each directory created is marked with the date and time that the run was completed. This functionality is a work in progress.

(Not fully implemented yet) I you want to use the Shackleton framwork for genetic improvement, you must provide the -improvement flag upon starting the tool. You will be prompted when starting the tool with this flag to give the name of the file being used as the base for genetic improvement. Any file that needs to be used for this purpose should be located in the inputs/ subdirectory here.

This directory is subject to change and may have additional directories and subdirectories added to it with additional functions. Please refer to this README often for any updates.