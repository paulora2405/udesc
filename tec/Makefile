########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
WALLFLAGS = -Wall -Wextra -Wpedantic
CXXFLAGS = -std=c++14 -g $(WALLFLAGS) #-pthread
LDFLAGS =

# Makefile settings - Can be customized.
APPNAME = main
EXT = .cpp
SRCDIR = src
OBJDIR = obj
DOTDIR = dot

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
RMDIR = rm -r
TEST = test -s
DELOBJ = $(OBJ)
# GRAPHVIZ
IMG_IN = entrada
IMG_OUT = saida


########################################################################
####################### Targets beginning here #########################
########################################################################

all: mkdirs $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Building OBJ and SRC dir if they don't exist yet
.PHONY: mkdirs
mkdirs: $(OBJDIR)/ $(DOTDIR)/

$(OBJDIR)/:
	mkdir -p $@

$(DOTDIR)/:
	mkdir -p $@

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	-$(RM) $(DELOBJ) $(DEP) $(APPNAME)
	-$(RMDIR) $(OBJDIR) $(DOTDIR)
	-$(RM) output.txt

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	-$(RM) $(DEP)

# Generates GraphViz Image
.PHONY: dot
dot:
	-dot -Tpng $(DOTDIR)/$(IMG_IN).dot -o $(DOTDIR)/$(IMG_IN).png
	-dot -Tsvg $(DOTDIR)/$(IMG_IN).dot -o $(DOTDIR)/$(IMG_IN).svg
	-dot -Tpng $(DOTDIR)/$(IMG_OUT).dot -o $(DOTDIR)/$(IMG_OUT).png
	-dot -Tsvg $(DOTDIR)/$(IMG_OUT).dot -o $(DOTDIR)/$(IMG_OUT).svg