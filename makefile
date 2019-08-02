 ################################################################################ \
 Name        : makefile															  \
 Author      : Hannah M. Peeler													  \
 Version     : 1.0																  \
 Copyright   : 																	  \
																				  \
    Copyright 2019 Arm Inc., Andrew Sloss, Hannah Peeler						  \
																				  \
    Licensed under the Apache License, Version 2.0 (the "License");				  \
    you may not use this file except in compliance with the License.			  \
    You may obtain a copy of the License at										  \
																				  \
       http://www.apache.org/licenses/LICENSE-2.0								  \
																				  \
    Unless required by applicable law or agreed to in writing, software			  \
    distributed under the License is distributed on an "AS IS" BASIS,			  \
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.	  \
    See the License for the specific language governing permissions and			  \
    limitations under the License.												  \
																				  \
    Please refer to 															  \
    https://github.com/ARM-software/Shackleton-Framework/blob/master/LICENSE.TXT  \
    for a full overview of the license covering this work.						  \
																				  \
 Description : Makefile for main of Shackleton Framwork							  \
 #################################################################################


DIR := .
SRCDIR := ./src

OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/,main.o osaka.o modules.o simple.o osaka_test.o assembler.o osaka_string.o autogen_test.o llvm_pass.o binary_up_to_512.o evolution.o crossover.o mutation.o generation.o fitness.o selection.o utility.o cJSON.o visualization.o llvm.o test.o)
                
osaka : $(OBJS)
	cc -o shackleton $(OBJS)
	cp shackleton $(DIR)/bin/init


$(OBJDIR)/main.o : $(DIR)/main.c
	cc -c $? -o $@

$(OBJDIR)/osaka.o : $(SRCDIR)/osaka/osaka.c $(SRCDIR)/osaka/osaka.h 
	cc -c $(SRCDIR)/osaka/osaka.c -o $@

$(OBJDIR)/osaka_test.o : $(SRCDIR)/osaka/osaka_test.c $(SRCDIR)/osaka/osaka_test.h 
	cc -c $(SRCDIR)/osaka/osaka_test.c -o $@ 	
	
$(OBJDIR)/modules.o : $(SRCDIR)/module/modules.c $(SRCDIR)/module/modules.h
	cc -c $(SRCDIR)/module/modules.c -o $@ 

$(OBJDIR)/simple.o : $(SRCDIR)/module/simple.c $(SRCDIR)/module/simple.h
	cc -c $(SRCDIR)/module/simple.c -o $@

$(OBJDIR)/assembler.o : $(SRCDIR)/module/assembler.c $(SRCDIR)/module/assembler.h
	cc -c $(SRCDIR)/module/assembler.c -o $@ 

$(OBJDIR)/osaka_string.o : $(SRCDIR)/module/osaka_string.c $(SRCDIR)/module/osaka_string.h
	cc -c $(SRCDIR)/module/osaka_string.c -o $@ 

$(OBJDIR)/llvm_pass.o : $(SRCDIR)/module/llvm_pass.c $(SRCDIR)/module/llvm_pass.h
	cc -c $(SRCDIR)/module/llvm_pass.c -o $@

$(OBJDIR)/binary_up_to_512.o : $(SRCDIR)/module/binary_up_to_512.c $(SRCDIR)/module/binary_up_to_512.h
	cc -c $(SRCDIR)/module/binary_up_to_512.c -o $@

$(OBJDIR)/evolution.o : $(SRCDIR)/evolution/evolution.c $(SRCDIR)/evolution/evolution.h
	cc -c $(SRCDIR)/evolution/evolution.c -o $@ 

$(OBJDIR)/crossover.o : $(SRCDIR)/evolution/crossover.c $(SRCDIR)/evolution/crossover.h
	cc -c $(SRCDIR)/evolution/crossover.c -o $@ 

$(OBJDIR)/mutation.o : $(SRCDIR)/evolution/mutation.c $(SRCDIR)/evolution/mutation.h
	cc -c $(SRCDIR)/evolution/mutation.c -o $@ 

$(OBJDIR)/generation.o : $(SRCDIR)/evolution/generation.c $(SRCDIR)/evolution/generation.h
	cc -c $(SRCDIR)/evolution/generation.c -o $@ 

$(OBJDIR)/fitness.o : $(SRCDIR)/evolution/fitness.c $(SRCDIR)/evolution/fitness.h
	cc -c $(SRCDIR)/evolution/fitness.c -o $@ 

$(OBJDIR)/selection.o : $(SRCDIR)/evolution/selection.c $(SRCDIR)/evolution/selection.h
	cc -c $(SRCDIR)/evolution/selection.c -o $@ 

$(OBJDIR)/utility.o : $(SRCDIR)/support/utility.c $(SRCDIR)/support/utility.h
	cc -c $(SRCDIR)/support/utility.c -o $@ 

$(OBJDIR)/cJSON.o : $(SRCDIR)/support/cJSON.c $(SRCDIR)/support/cJSON.h
	cc -c $(SRCDIR)/support/cJSON.c -o $@ 

$(OBJDIR)/visualization.o : $(SRCDIR)/support/visualization.c $(SRCDIR)/support/visualization.h
	cc -c $(SRCDIR)/support/visualization.c -o $@ 

$(OBJDIR)/llvm.o : $(SRCDIR)/support/llvm.c $(SRCDIR)/support/llvm.h
	cc -c $(SRCDIR)/support/llvm.c -o $@ 

$(OBJDIR)/test.o : $(SRCDIR)/support/test.c $(SRCDIR)/support/test.h
	cc -c $(SRCDIR)/support/test.c -o $@ 

clean :
	rm $(OBJS)