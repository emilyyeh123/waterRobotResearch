CC=g++

CFLAGS=-c -DPRINT -std=c++11 -O2 -fpic

INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

HEADERS=receive_unix_signal.hpp send_unix_signal.hpp ../batteryLevel.hpp ../position.hpp
OBJECTS=receive_unix_signal.o send_unix_signal.o main.o
DJI_OBJ=dji_linux_environment.o dji_linux_helpers.o batteryLevel.o position.o
DJI_CPP=../dji_linux_environment.cpp ../dji_linux_helpers.cpp ../batteryLevel.cpp ../position.cpp

TARGETS=test

all: $(TARGETS) 

$(TARGETS): $(OBJECTS) 
	$(CC)  $(OBJECTS) -o $(TARGETS) $(LINKS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

compile_DJI_CPP:
	$(CC) $(CFLAGS) -o $(DJI_OBJ) $(DJI_CPP)

clean:
	rm $(TARGETS) $(OBJECTS)
