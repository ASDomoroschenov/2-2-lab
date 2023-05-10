CC=g++
CFLAGS=
LDFLAGS=-lm -w -std=c++20
SOURCES=../../task1/src/logger/logger.cpp ../../task1/src/builder/builder.cpp ../../task1/src/logger_concrete/logger_concrete.cpp ../../task1/src/builder_concrete/builder_concrete.cpp ../src/allocator/allocator.cpp ../src/memory/memory.cpp ../src/task5.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=task5

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) ../src/*/*.o