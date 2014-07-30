LEX = flex
CXX = clang
CFLAGS = -Isrc -Ibuild/src -std=c++11 -static
BUILD_DIR = build
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=build/%.o)

.PHONY: all clean

all: lib

clean:
	rm -r build

$(BUILD_DIR):
	mkdir -p $@/src/libsyntax
	mkdir -p $@/src/libutil

build/libfrontend.a: build/src/libsyntax/parser.o build/src/libsyntax/lexer.o $(OBJS)
	$(AR) rsc build/libfrontend.a $(OBJS) build/src/libsyntax/lexer.o build/src/libsyntax/parser.o
	ranlib build/libfrontend.a

lib: $(BUILD_DIR) build/libfrontend.a

build/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
	cd build/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../src/libsyntax/grammer.yy

$(BUILD_DIR)/src/libsyntax/lexer.cpp: src/libsyntax/lexer.l
	 $(LEX) $(LFLAGS) -o $(BUILD_DIR)/src/libsyntax/lexer.cpp src/libsyntax/lexer.l

$(BUILD_DIR)/src/libsyntax/%.o: build/src/libsyntax/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libutil/%.o: src/libutil/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libsyntax/%.o: src/libsyntax/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

build/test_main: build/libfrontend.a tests/integration/test_main.cpp
	$(CXX) $(CFLAGS) -o $@ tests/integration/test_main.cpp build/libfrontend.a -lstdc++ -lm


