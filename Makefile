LEX = flex
CC = g++
CFLAGS = -Isrc -Ibuild/src -std=c++11
BUILD_DIR = build
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=build/%.o)

all: lib

$(BUILD_DIR):
	mkdir -p $@/src/libsyntax
	mkdir -p $@/src/libutil

build/libfrontend.a: build/src/libsyntax/parser.o build/src/libsyntax/lexer.o $(OBJS)
	$(AR) cr build/libfrontend.a $(OBJS) build/src/libsyntax/lexer.o build/src/libsyntax/parser.o
	ranlib build/libfrontend.a

lib: build/libfrontend.a

build/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
	cd build/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../$^

$(BUILD_DIR)/src/libsyntax/lexer.cpp: $(BUILD_DIR) src/libsyntax/lexer.l
	 $(LEX) $(LFLAGS) -o $(BUILD_DIR)/src/libsyntax/lexer.cpp src/libsyntax/lexer.l

$(BUILD_DIR)/src/libsyntax/%.o: build/src/libsyntax/%.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libutil/%.o: src/libutil/%.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libsyntax/%.o: src/libsyntax/%.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

build/test_main: build/libfrontend.a tests/integration/test_main.cpp
	$(CC) $(CFLAGS) build/libfrontend.a tests/integration/test_main.cpp -o $@
