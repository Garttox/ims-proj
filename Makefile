CC = g++
CXXFLAGS = -std=c++11 -Wall
CXXFLAGS += -lsimlib #simlib
EXECUTABLE = isa
ARCHIVE_NAME = 09_xtrlic02_xlukes07

compile:
	@$(CC) -o $(EXECUTABLE) src/*.cpp $(CXXFLAGS)

run: compile
	@./$(EXECUTABLE)

clean:
	@rm -r $(EXECUTABLE) $(ARCHIVE_NAME).zip

pack:
	zip $(ARCHIVE_NAME).zip src Makefile
