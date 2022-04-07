# Compiler
CC=g++

# Compiler options
CFLAGS = -c -std=c++11 -g -O0

INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

# Uncomment to add debugging symbols
#DEBUG=-g

HEADERS = batteryLevel.hpp vehicleSetUp.hpp position.hpp

OBJECTS = main.o dji_linux_environment.o dji_linux_helpers.o batteryLevel.o vehicleSetUp.o position.o

EXECUTABLE = mainProgram

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LINKS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
