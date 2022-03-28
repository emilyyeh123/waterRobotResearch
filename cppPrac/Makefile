# Compiler
CC = g++

# Compiler Options
CFLAGS = -c -Wall -std=c++11

HEADERS = hello.hpp

OBJECTS = main.o hello.o

EXECUTABLE = mainProgram

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
 
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	rm -rf *.o $(EXECUTABLE)


