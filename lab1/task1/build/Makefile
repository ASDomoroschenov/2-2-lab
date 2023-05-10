CC=g++
CFLAGS=
LDFLAGS=-lm -std=c++17
SOURCES=../src/builder/builder.cpp ../src/builder_concrete/builder_concrete.cpp ../src/logger/logger.cpp ../src/logger_concrete/logger_concrete.cpp ../src/json/json.cpp ../src/json_concrete/json_concrete.cpp ../src/task1.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=task1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)