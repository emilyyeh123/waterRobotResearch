# Compiler
CC=g++

# Compiler options
CFLAGS = -c -std=c++11 -g -O0

INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

HEADERS = receive_unix_signal.hpp send_unix_signal.hpp batteryLevel.hpp position.hpp

OBJECTS = main.o dji_linux_environment.o dji_linux_helpers.o receive_unix_signal.o send_unix_signal.o batteryLevel.o position.o

EXECUTABLE = mainProgram

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LINKS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
