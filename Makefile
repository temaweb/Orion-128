# Compiller
CC=g++

# Target
TARGET=libemulator.so

# Buld directory
BUILDDIR=build
SOURCEDIR=emulator

# Compiller flags
CFLAGS=-std=c++17 -c -Wall -I/**

# Linker flags
LDFLAGS=-lstdc++

SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(SOURCES) $(BUILDDIR)/$(TARGET)

dir:
	mkdir -p $(BUILDDIR)
    
.PHONY: all clean

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ -shared -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILDDIR)/*o $(BUILDDIR)/$(TARGET)
	
run: all
	@./$(BUILDDIR)/$(TARGET)