# Compiller
CC=g++

# Target
TARGET=libemulator.dylib

# Buld directory
SOURCEDIR=emulator

# MacOS min version
MACOSMIN=10.13

# Compiller flags
CFLAGS=-std=c++17 -O3 -c -mmacosx-version-min=$(MACOSMIN) -Wall $(INCDIRS)

# Linker flags
LDFLAGS=-lstdc++ \
	-dynamiclib \
	-mmacosx-version-min=$(MACOSMIN) \
	-install_name "@executable_path/../Frameworks/$(TARGET)" \
	-framework OpenGL \
	-framework CoreFoundation

SOURCES = $(shell find $(SOURCEDIR) -type f -iname '*.cpp')
OBJECTS = $(foreach x, $(basename $(SOURCES)), $(x).o)
INCDIRS = $(addprefix -I,$(shell find $(SOURCEDIR) -type d -print))

all: $(SOURCES) $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: all
	@./$(TARGET)
