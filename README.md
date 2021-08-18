# Project Shackleton

![alt text](img/shackleton.jpg "The Endurance")

**Synopsis**


*  **Project Shackleton** goal is to build a modular designed Linear Genetic Programming (LGP) framework to automate the discovery of optimal software solutions for hard low-level software optimization problems. Idea to is a apply LGP to a Generic Genetic Object (GGO). The GGO by default is set to AArch64 instructions but support is in place for LLVM Intermediate Code.
*  Once complete the Shackleton framework can be used to explore any low-level software optimization problem as long as the optimal answer can be defined either as an objective or multi-objectives (pareto curve) with constraints. The framework itself works with GGO’s.
*  Challenges revolve around interfacing, variable setting, define goal/s, testing environment and inserting constraints. Also a complicated part is understand the methods of outputting correct LLVM IR code or simply even outputting AArch64 code directly from the GGO.
*  A dynamic method of playing with the LGP algorithm variables i.e. population size, maximum generations, recombination %, mutation %, output size, variable constraints, etc. would be advantageous since this would allow more complicated search models could be adopted. 


**Description**


*  Shackleton is designed to be highly adaptive framework targeting AArch64, LLVM IR, …
*  Using population based optimization and exploration
*  Frameworks is designed to speed up automated software production
*  Either taking existing code (GI) or creating entirely new code (GP)
*  Broken into a module design with specific methods of communication
*  Each module can be developed independently providing the I/O rules are adhered-to
*  Designed to be run in hosted (x86) or native, in continuous or fixed fashion

**Genetic Programming**

Genetic Programming (GP) by contrast to Genetic Algorithms (GA) manipulates structures and in-particular programs that are executable or mathematical equations i.e. symbolic regression.  Traditionally GP used a tree-based representation and used the LISP programming language, in more recent times Python is extremely popular.  Relies more on crossover than mutation as the method of evolution. GPs handle manipulating structures so any problems which is structurally based can be tackled by this algorithm i.e. linear, tree and direct-graph. GPs can produce original source code and in fact can find new novel solutions to any structural style problems.  In industry GP to mostly used to discover best fit mathematical equations.

**Genetic Improvement**

Genetic Improvement (GI) is a subclass of GP (section 4.3), where instead of a random initial seeded population, a working program is inserted as the starting point to spawn the children entities of the first population.  This is a powerful concept since it does not only search for a better optimized solution but also has the potential to discover and correct faults in the original” working” code. Solves an interesting problem, where either the working code is potentially un-optimized, and a more optimized version is required or bringing legacy code up to current standards.

**Linear Genetic Programming**
Linear Genetic Programming (LGP) is a subclass of GP and as the name implies uses a linear structure representation. The linear structure has some advantages over the more complicated tree or directed-graph structures. LGP is particularly useful for problems which are more sequential. For example, optimizing low level assembly output. It also makes the problem of manipulating complex structures easier since it is a linear flow that is being evolved.  Constructs like if-style control flow or loops are superimposed onto the linear structure.

LPG solves problems that are sequential.  This is useful for optimizing programs and low-level assembly style output.  Or any problem-domain where the problem being explored is about sequential ordering

--------

# LLVM Optimization using Shackleton

Shackleton comes pre-built with an LLVM optimizer optimizer (say that 5 times fast) baked into the framework. What that means is that one of the default object types (modules) available to the user is the LLVM_PASS module. Each instance of this module represents a single LLVM_PASS, while an Osaka List Structure (OSL) of this module represents a sequence of LLVM optimization passes that can be applied to a program. The framework iterates through its generations by creating new optimization sequences, applying them to inputted source code, and measuring their fitness by the amount of compute time. The optimization sequence that results in optimized code with the shortest time to run is considered the "best individual".

When the -llvm_optimize flag is provided to the tool, it automatically takes you through a series of questions to input a series of source files to be tested against different optimization sequences.All source files used with this portion of the tool should be placed in src/files/llvm. The tool looks for files in relation to that directory, so if you input a file as "test.cpp" then the tool will look for that file in src/files/llvm/test.cpp. 

--------

# Requirements for use, Installation Instructions

Shackleton comes in the form of a code repository that can be made and then run from the command line using the "make" command and then run with the call "./shackleton". The tool can be run with a number of available flags, listed here with their descriptions:

-   -help : Offers information on inputs to the command line interface for using the tool. Does not initiate a run, exits after displaying the information.
-   -parameters_file : Specifies that an input file at src/files/parameters.txt will be used to change some of the parameter values for evolution. An example parameters.txt file is provided in src/files/.
-   -test : Enables the testing script for Shackleton to be run. Will be run regardless of other parameters specified.
-   -llvm_optimize : Specifies that the LLVM integrated portion of the tool will be used to optimize LLVM using evolution of LLVM transform and analysis passes. This option automatically sets the object type needed to LLVM_PASS.
-   -cache : Caches information for each evolutionary run into files. The information provided in these files is dependent on the object type being used. (Work in Progress, WIP)

If no flags are provided, then the tool will show all default values for parameters and prompt the user if they want to change any of the default values. After choosing an object type to evolve, the tool will run as usual with the parameters provided. Additional information for some of these flags that enable creating or reading from files can be found in READMEs in the subdirectories of this project. 

In order to fully make and run Shackleton with LLVM integration, you will need the following:

-   svn
-   Cmake
-   Make
-   A C compiler (GNU, GCC, clang)

You will also need to use some of these commands to get a copy of LLVM for your machine. The LLVM optimization portion of this tool cannot be used without a fully compiled LLVM isntallation on your machine. Follow these steps to get a copy of your own:

1. Create a folder where you want LLVM to be stored. It is recommended to name it with the following convention: llvm_MM_DD_YY and to place it in your desktop directory
2. Within that newly created folder, make two subdirectories: "build" and "source"

the following steps are run from terminal

3. cd llvm_MM_DD_YY/source
4. svn co https://user@llvm.org/svn/llvm-project/llvm/tags/RELEASE_500/final llvm
4. cd llvm/tools
5. svn co http://llvm.org/svn/llvm-project/cfe/tags/RELEASE_500/final clang
6. cd clang/tolls # (You should now be in llvm/tools/clang/tools)
7. svn co http://llvm.org/svn/llvm-project/clang-tools-extra/tags/RELEASE_500/final extra
8. cd ../../../../llvm/projects (you should now be in llvm/projects)
9. svn co http://llvm.org/svn/llvm-project/compiler-rt/tags/RELEASE_500/final compiler-rt
10. cd ../../.. (You should now be in llvm_MM_DD_YY directory)
11. mkdir build (if you haven't already done so)
12. cd build
13. cmake -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_TARGET_ARCH=X86 -DCMAKE_BUILD_TYPE="Release" -DLLVM_BUILD_EXAMPLES=1 -DCLANG_BUILD_EXAMPLES=1 -G "Unix Makefiles" ../source/llvm/
14. make -j 8 (from within the build directory. This fully builds LLVM, and can take a considerable amount of time)

Once the build completes, check to make sure that your build/bin directory has been populated by a number of tools, including llc, lli, llvm-link, clang specifically. If the make and build was successful, please add the full path to the build/bin directory to the PATH variable on your machine. If you are new to LLVM and want to follow the instructional guide that was the main source of the steps listed below, you can find the presentation here as a recorded lecture and as slides: http://www.mshah.io/fosdem18.html.

You are now ready to build the Shackleton tool. In the terminal, go to the top level directory of Shackleton (where you can see folders bin/, build/, docs/, img/, obj/, and src/). From there you run "make" and Shackleton should be fully built and ready to run! Happy Experimenting!

--------

For any questions or comments for the creator of this tool, please message hpeeler@utexas.edu. This tool was intially created during a summer internship at Arm Ltd. in collaboration with professor [Wolfgang Banzhaf](http://www.cse.msu.edu/~banzhafw/) and postdoc [Yuan Yuan](https://www.researchgate.net/profile/Yuan_Yuan73) out of Michigan State University.

Stella Li (John Hopkins University, sli136@jhu.edu) enhanced this framework during her 2021 summer internship in collaboration between Arm and Michigan State Unviversity. Below is a list of enhancements in Shackleton 2.0: 

- Elitism (percentage specified as parameter)
- New randomly generated individuals
- New offspring selection mechanism
- Unique ID for each individual
- Data structure containing individual information
- Fitness lookup from table
- Overhead runtime evaluation
- Noise reduction by increasing number of evalutaions
- Early termination mechanism
- Genetic Improvement
