CC=g++

CFLAGS=-c -DPRINT -std=c++11 -O2 -fpic

HEADERS=receive_unix_signal.hpp send_unix_signal.hpp
OBJECTS=receive_unix_signal.o send_unix_signal.o main.o

TARGETS=test

all: $(TARGETS) 

$(TARGETS): $(OBJECTS) 
	$(CC)  $(OBJECTS) -o $(TARGETS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(TARGETS) $(OBJECTS) 
