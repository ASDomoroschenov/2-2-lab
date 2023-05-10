CC=g++
CFLAGS=
LDFLAGS=-w -lm -std=c++17
SOURCES=../../task1/src/logger/logger.cpp ../../task1/src/builder/builder.cpp ../../task1/src/logger_concrete/logger_concrete.cpp ../../task1/src/builder_concrete/builder_concrete.cpp ../src/memory/memory.cpp ../src/allocator/allocator.cpp ../src/task2.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=task2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) ../src/*/*.o