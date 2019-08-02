This folder contains all the source code for the tool itself. Any additional code that does not factor into the top-level tool will be located outside of this folder. Please refer to the READMEs of the subdirectories for more information on their contents.

Subdirectories and a summary of their contents:

-   editor_tool : The editor tool serves as a "tool within the tool" to aide in adding new object types to the top-level Shackleton tool. Adding a new object type allows for more fine-grained usage for a given application.
-   evolution : This folder contains all information for each of the "evolutionary operators" included in the tool (such as crossover, selection, etc.). The entire evolutionary process is contained within the files in this folder.
-   files : Any files that are treated as inputs or outputs of the Shackleton code are housed here. This folder is especially important for include LLVM files when using the LLVM-integrated portions of the tool.
-   module : The "object types" available for use with the Shackleton tool are here. If you use the editor tool, then you will be editing the files contained in this directory.
-   osaka : The "Osaka Structure" and its implementation are in this directory. The Osaka Structure is a doubly linked list where each node of the list if a wrapper for an internal object type, the object that contains the pertinent information for any evolutionary run.
-   support : Any files that have utility functions and are used in different places throughout the source code is found here. This is also where the testing code can be found.