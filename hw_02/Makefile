CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = hw_02
TESTEXE = test_hw_02
SRCDIR = src
OBJDIR = obj
TESTDIR = test

OBJECTS = obj/Board.o obj/StdioBoardView.o obj/GameController.o obj/test.o obj/NcursesBoardView.o

all: $(EXE) $(TESTEXE)

$(EXE): $(OBJECTS) obj/main.o
	$(CXX) $(OBJECTS) obj/main.o -o $(EXE) $(LDFLAGS) -lncurses

$(TESTEXE): $(OBJECTS) obj/BoardTest.o
	$(CXX) $(OBJECTS) obj/BoardTest.o -o $(TESTEXE) $(LDFLAGS) -lncurses

	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $< -lncurses

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $< -lncurses

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TESTEXE)

.PHONY: clean all
