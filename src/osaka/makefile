 ################################################################################ \
 Name        : makefile															  \
 Author      : Andrew Sloss														  \
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
 Description : Makefile for the Osaka Structure									  \
 #################################################################################

SRCDIR := .

OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/,main.o osaka.o modules.o simple.o osaka_test.o)

osaka : $(OBJS)
	cc -o osaka $(OBJS)
	cp osaka $(SRCDIR)/bin/init



$(OBJDIR)/main.o : $(SRCDIR)/main.c
	cc -c $? -o $@

$(OBJDIR)/osaka.o : $(SRCDIR)/osaka.c $(SRCDIR)/osaka.h 
	cc -c $(SRCDIR)/osaka.c -o $@

$(OBJDIR)/osaka_test.o : $(SRCDIR)/osaka_test.c $(SRCDIR)/osaka_test.h 
	cc -c $(SRCDIR)/osaka_test.c -o $@ 	
	
$(OBJDIR)/modules.o : $(SRCDIR)/module/modules.c $(SRCDIR)/module/modules.h
	cc -c $(SRCDIR)/module/modules.c -o $@ 

$(OBJDIR)/simple.o : $(SRCDIR)/module/simple.c $(SRCDIR)/module/simple.h
	cc -c $(SRCDIR)/module/simple.c -o $@ 

clean :
	rm $(OBJS)