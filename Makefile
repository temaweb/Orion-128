# Compiller
CC=g++

# Target
TARGET=libemulator.so

# Buld directory
SOURCEDIR=emulator

# Compiller flags
CFLAGS = -std=c++17 -O3 -c -Wno-unknown-pragmas -Wall $(INCDIRS)

# Linker flags
LDFLAGS = -lstdc++

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif

ifeq ($(detected_OS),Darwin)

	# MacOS min version
	MACOSMIN=10.13

	TARGET = libemulator.dylib
    CFLAGS += -mmacosx-version-min=$(MACOSMIN) -D OSX
    
    LDFLAGS += \
		-dynamiclib \
		-mmacosx-version-min=$(MACOSMIN) \
		-install_name "@executable_path/../Frameworks/$(TARGET)" \
		-framework OpenGL \
		-framework CoreFoundation
		
endif
ifeq ($(detected_OS),Linux)

	TARGET = libemulator.so
	CFLAGS += -D LINUX -DGL_GLEXT_PROTOTYPES -fPIC
	
    LDFLAGS += \
		-shared \
		-lGL
		
endif

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
