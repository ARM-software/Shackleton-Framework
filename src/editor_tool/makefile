 ################################################################################ \
 Name        : src/editor_tool/makefile											  \
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
 Description : Makefile for main of the editor_tool in the Shackleton Framework	  \
 #################################################################################

SRCDIR := .

OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/,main.o create.o edit.o utility.o cJSON.o)

osaka : $(OBJS)
	cc -o shackleton_editor_tool $(OBJS)
	cp shackleton_editor_tool $(SRCDIR)/bin/init


$(OBJDIR)/main.o : $(SRCDIR)/main.c
	cc -c $? -o $@

$(OBJDIR)/create.o : $(SRCDIR)/support/create.c $(SRCDIR)/support/create.h 
	cc -c $(SRCDIR)/support/create.c -o $@

$(OBJDIR)/edit.o : $(SRCDIR)/support/edit.c $(SRCDIR)/support/edit.h 
	cc -c $(SRCDIR)/support/edit.c -o $@

$(OBJDIR)/utility.o : $(SRCDIR)./support/utility.c $(SRCDIR)./support/utility.h 
	cc -c $(SRCDIR)./support/utility.c -o $@

$(OBJDIR)/cJSON.o : $(SRCDIR)./support/cJSON.c $(SRCDIR)./support/cJSON.h 
	cc -c $(SRCDIR)./support/cJSON.c -o $@


clean :
	rm $(OBJS)