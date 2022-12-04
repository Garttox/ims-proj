CC = g++
CXXFLAGS = -std=c++11 -Wall
CXXFLAGS += -lsimlib  #simlib
CXXFLAGS += -lm #math
EXECUTABLE = ims
ARCHIVE_NAME = 09_xtrlic02_xlukes07

compile:
	@$(CC) -o $(EXECUTABLE) src/*.cc $(CXXFLAGS)

run: compile
	@./$(EXECUTABLE) -a 20 -c 0.3 -m 43.2 -s 0.0765 -t 15 -v 250

plot:
	gnuplot plot.plt

plot3d:
	gnuplot plot3d.plt

clean:
	@rm -r $(EXECUTABLE) $(ARCHIVE_NAME).zip

pack:
	zip $(ARCHIVE_NAME).zip src Makefile
