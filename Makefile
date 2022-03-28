# Compiler
CC=g++

# Compiler options
CFLAGS = -c -Wall -std=c++11 -g -O0

INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

# Uncomment to add debugging symbols
#DEBUG=-g

HEADERS = batteryLevel.hpp

OBJECTS = main.o dji_linux_environment.o dji_linux_helpers.o batteryLevel.o

EXECUTABLE = mainProgram

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LINKS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
