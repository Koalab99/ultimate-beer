#  Universal Makefile
#   Works well almost everywhere
#   If you're lucky, he might wave you sometimes !
#

CC=g++ 
FILETYPE=cpp

CCFLAG=-Wall -I$(INCDIR) --std=c++17 -g $(shell sdl2-config --cflags)
LDFLAG=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lstdc++fs

EXE=ultimateBeer

SRCDIR:=src/
OBJDIR:=obj/
DOCDIR:=doc/
DATADIR:=data/
BINDIR:=bin/
INCDIR:=inc/
DEPDIR:=dep/

DIRS:=$(SRCDIR) $(OBJDIR) $(DOCDIR) $(DATADIR) $(BINDIR) $(INCDIR) $(DEPDIR)

SRC:=$(wildcard $(SRCDIR)*.$(FILETYPE))
OBJ:=$(patsubst $(SRCDIR)%.$(FILETYPE), $(OBJDIR)%.o, $(SRC))
DEP:=$(patsubst $(OBJDIR)%.o, $(DEPDIR)%.d, $(OBJ))

.PHONY: all clean mrproper regtest doc

all: $(DIRS) $(BINDIR)$(EXE) $(DOCDIR)html/index.html

-include $(wildcard $(DEPDIR)*.d)

$(DIRS): 
	@mkdir -p $(DIRS)

$(BINDIR)$(EXE): $(OBJ)
	@echo "Linking all object files together..."
	@$(CC) $^ -o $@ $(LDFLAG)
	@echo "OK!"

$(OBJDIR)%.o: $(SRCDIR)%.$(FILETYPE)
	@echo "Creating the $* object file..."
	@$(CC) -c -o $(OBJDIR)$*.o $(SRCDIR)$*.$(FILETYPE) $(CCFLAG)
	@echo "Generating the dependancy file for $*"
	@echo -n "$(OBJDIR)" > $(DEPDIR)$*.d
	@$(CC) -MM $(CCFLAG) $(SRCDIR)$*.$(FILETYPE) >> $(DEPDIR)$*.d

$(DOCDIR)html/index.html: $(DATADIR)doxyconfig.conf
	@echo "Generating doxygen confind in $(DOCDIR)"
	@doxygen $^ >$(DOCDIR)doxy.out

doc:
	@doxygen $(DATADIR)doxyconfig.conf 

regtest:
	@g++ regtest/LevelFile.cpp -o regtest/testFile
	@./regtest/testFile data/map/*

clean:
	@echo "Deleting temporary files..."
	@rm -f $(OBJDIR)*.o $(DEPDIR)*.d

mrproper:
	@echo "Deleting all unnecessary directories..."
	@rm -rf $(OBJDIR) $(BINDIR) $(DEPDIR) $(DOCDIR)
