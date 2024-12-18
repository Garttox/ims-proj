CC = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -lsimlib  #simlib
CXXFLAGS += -lm #math
SRCFILES = src/ims.cc src/vector.cc src/projectile.cc
EXECUTABLE = ims
ARCHIVE_NAME = 09_xtrlic02_xlukes07

compile:
	@$(CC) -o $(EXECUTABLE) $(SRCFILES) $(CXXFLAGS)

run: compile
	@./$(EXECUTABLE) -a 45 -c 0.3 -m 43.2 -s 0.0765 -t 15 -v 827 -h 100

plot:
	gnuplot plot.plt

plot3d:
	gnuplot plot3d.plt

clean:
	@rm -r $(EXECUTABLE) $(ARCHIVE_NAME).zip trajectory.dat

pack:
	zip -r $(ARCHIVE_NAME).zip src Makefile plot.plt plot3d.plt doc experiments README.md
