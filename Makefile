# Compiller
CC=g++

# Target
TARGET=libemulator.so

# Buld directory
SOURCEDIR=emulator

# Compiller flags
CFLAGS=-std=c++17 -c -Wall $(INCDIRS)

# Linker flags
LDFLAGS=-lstdc++ -framework OpenGL

SOURCES = $(shell find $(SOURCEDIR) -type f -iname '*.cpp')
OBJECTS = $(foreach x, $(basename $(SOURCES)), $(x).o)
INCDIRS = $(addprefix -I,$(shell find $(SOURCEDIR) -type d -print))

all: $(SOURCES) $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -shared -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: all
	@./$(TARGET)
