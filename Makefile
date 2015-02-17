# Makefile for CPSC 221, Programming Project #1.
# With many thanks to: http://wiki.osdev.org/Makefile


# Names of projects for handin.
# Needs to be changed for different projects!
# It might be reasonable to pull these directly from the handin -l command.
HANDIN_NAMES = milestone1 proj1

# Files besides source and header files that participate in the project.
# Needs to be changed for different projects!
AUXFILES := HANDIN.txt Makefile MILESTONE1.txt

# The programs to make (i.e., filenames of files whose .cpp versions
# contain a main function).  Needs to be changed for different projcets!
MAINS := solve # for students, should be ordered so least buggy goes first


# Variables to refer to the remove command (and "forced" remove). 
RM = rm
RMF = $(RM) -f  # $(RM) is the value of the variable RM.

# Our compiler
CC = g++

# The extensions being used for source and header files.
CPP_EXTENSION = cpp
HPP_EXTENSION = hpp

# Warnings to include during compilation.  
# -Weffc++ gives some great warnings.. but more than we wanted to deal with.
# Feel free to turn it on.  -Werror turns all warnings into errors, which is
# good practice as well.
WARNINGS = -Wall -Wextra -Wwrite-strings -Wconversion -Wnon-virtual-dtor # -Weffc++ -Werror

# Compile and link flags.
CFLAGS = $(WARNINGS) -g -c
LFLAGS = -g

# The full list of source files and header files in the project.
SRCFILES := $(wildcard *.$(CPP_EXTENSION))  # $(wildcard ...) matches files using
HDRFILES := $(wildcard *.$(HPP_EXTENSION))  # e.g., *, and gives back the result.
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)  # all files together

#For SRC/HDR files, used to use:
# $(shell find . -type f -name '*.cpp')
# $(shell find . -type f -name '*.hpp')

# The object files in the project, the object files without the ones
# that include main functions (because we cannot link together two
# objects that both define a main function), and the dependency files
# auto-generated by g++ (things ending in .d).
OBJFILES := $(patsubst %.$(CPP_EXTENSION),%.o,$(SRCFILES))
OBJFILES_NOMAINS := $(filter-out $(patsubst %,%.o,$(MAINS)),$(OBJFILES))
DEPFILES := $(patsubst %.o,%.d,$(OBJFILES))

# Note: $(patsubst a,b,c) replaces instances of a with b in the text c.
# The % character is a wildcard matching text that's left unchanged.

# Note: $(filter-out a,b) removes instances of a from the text b.


# Should be the first target, since we want it to be the default.
# When you type make alone, it will automatically try to make the
# first target (first thing that goes before a : at the start of a
# line).  This ensures that we make the todolist and all of the main
# programs.
all: $(MAINS)

# Import all of the autogenerated dependency files.
-include $(DEPFILES)

# To make one of the main targets (e.g., something like solve), we
# need to make the object files first.  (The stuff after the : is what
# make needs to ensure is up-to-date prior to making the target.)
# Then, we execute the command below, which links together all the
# object files including the .o matching the target we're currently
# making.  ($@ is a special variable referring to the target of the
# current command.)  The executable uses the target as its name (which
# is the job of the -o flag).
$(MAINS): $(OBJFILES)
	$(CC) $(LFLAGS) -o $@ $(OBJFILES_NOMAINS) $@.o

# A target to clean out the directory.  The $(wildcard ...) isn't used
# but certainly could be! :) The - in front means that make doesn't
# bother stopping if the command fails.
clean:
	-$(RMF) $(wildcard $(OBJFILES) $(DEPFILES) $(MAINS))

# An implicit rule.  We can always make a .o file from a .cpp file.
# The -MMD and -MP flags create the dependency file that "magically"
# makes the Makefile work correctly.  The -c flag compiles to an
# object file.  $< is a special variable referring to the first
# dependency (the .cpp file).  
%.o: %.$(CPP_EXTENSION) Makefile
	$(CC) $(LFLAGS) $(CFLAGS) -MMD -MP -c $<

# Outputs a list of tasks.  The - at the start of the line means not
# to stop on failure.  The @ at the start of the line means not to
# print this command out.  The rest is mostly a little shell script
# that uses grep to pull out the TODO items; however, the syntax
# $(a:b=c) replaces the textb b with the text c when supplying the
# contents of the variable a.  In this case, it elides the Makefile
# from the list of files to loop over.
todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO\: $$file; done; true

# The patsubst at the start generates a list of targets that look like
# handin-proj1.  The remainder is a little shell script that makes a
# temporary directory, storing its value in a temporary variable.
# Copies all the files (not directories.. done sloppily) into the
# temporary directory, goes into the temporary directory and cleans,
# zips up a handin archive, hands it in, checks the handin listing,
# and finally destroys the temporary directory.
$(patsubst %,handin-%,$(HANDIN_NAMES)):
	@$(eval $@_TMP_DIR := $(shell mktemp -d handin.XXXXXXXX))
	@cp `ls -p | grep -v '/'` $($@_TMP_DIR)
	@cd $($@_TMP_DIR); \
	  $(RMF) $(wildcard $(OBJFILES) $(DEPFILES) $(MAINS) *~ *.bak *.old)
	@cd $($@_TMP_DIR); \
	  zip handin.zip *
	@cd $($@_TMP_DIR); \
	  handin -o -f handin.zip cs221 $(patsubst handin-%,%,$@)
	handin -c cs221 $(patsubst handin-%,%,$@)
	@rm -Rf $($@_TMP_DIR)

.PHONY: all clean todolist

