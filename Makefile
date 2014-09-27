
CC=g++ -g
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-pthread
SOURCES= $(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=mst
.PHONY: all
all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
.PHONY: run
run:
	./$(EXECUTABLE)
.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

gdb:
	gdb $(EXECUTABLE) 
