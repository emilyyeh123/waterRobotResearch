# Compiler
CC=g++

# Compiler options
CFLAGS = -std=c++11 -g -O0

INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

# Uncomment to add debugging symbols
#DEBUG=-g

OBJECTS = main.o #dji_linux_environment.o dji_linux_helpers.o batteryLevel.o

TARGETS = main

# --------------------------------------------

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -shared -Wl,-soname,$@ $(OBJECTS) -o $@ $(LINKS)

#%.o: %.cpp $(HEADERS)
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(DEBUG) -c $@ $<

clean:
	rm $(TARGETS) $(OBJECTS)
