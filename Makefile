LEX = flex
CC = clang
CFLAGS = -Isrc -Ibuild/src -std=c++11
BUILD_DIR = build
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=build/%.o)


$(BUILD_DIR)/:
	mkdir -p $@src/libsyntax
	mkdir -p $@src/libutil

build/libfrontend.a: build/src/libsyntax/lexer.o build/src/libsyntax/parser.o $(OBJS)
	$(AR) cr build/libfrontend.a $(OBJS)


lib: build/libfrontend.a


build/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
	cd build/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../$^

build/src/libsyntax/lexer.cpp: src/libsyntax/lexer.l
	 $(LEX) $(LFLAGS) -o $@ $^

build/src/libsyntax/%.o: build/src/libsyntax/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

build/src/libutil/%.o: src/libutil/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

build/src/libsyntax/%.o: src/libsyntax/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
