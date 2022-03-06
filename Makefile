# Compiler
CC=g++

# Compiler options
CFLAGS=-c -std=c++11 -02 -fpic

# Everywhere else
INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

# Debugging Symbols
DEBUG=-g

# .hpp header files to use as dependencies
HEADERS=dji_osdk/dji_vehicle.hpp dji_osdk/dji_linux_environment.hpp dji_osdk/dji_linux_helpers.hpp dji_osdk/dji_status.hpp batteryLevel.hpp

# .o object files
OBJECTS=batteryLevel.o dji_osdk/dji_vehicle.o dji_osdk/dji_linux_environment.o dji_osdk/dji_linux_helpers.o dji_osdk/dji_status.o

# --------------------------------------------------------

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
  $(CC) -shared -Wl,-soname,$@ $(OBJECTS) -o $@ $<

clean:
  rm $(TARGETS) $(OBJECTS)

