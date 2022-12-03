CC = g++
CXXFLAGS = -std=c++11 -Wall
CXXFLAGS += -lsimlib #simlib
CXXFLAGS += -lm #math
EXECUTABLE = ims
ARCHIVE_NAME = 09_xtrlic02_xlukes07

compile:
	@$(CC) -o $(EXECUTABLE) src/*.cc $(CXXFLAGS)

run: compile
	@./$(EXECUTABLE) -a 45 -h 0

clean:
	@rm -r $(EXECUTABLE) $(ARCHIVE_NAME).zip

pack:
	zip $(ARCHIVE_NAME).zip src Makefile
