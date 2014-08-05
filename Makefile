LEX = flex
CXX = clang
CFLAGS = -Isrc -Ibuild/src -std=c++11 -stdlib=libstdc++
BUILD_DIR = build
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=build/%.o)

.PHONY: all clean test

all: lib

clean:
	rm -r build

test: build/test_parse build/test_typecheck
	python tests/integration/test_runner.py

$(BUILD_DIR):
	mkdir -p $@/src/libsyntax
	mkdir -p $@/src/libutil
	mkdir -p $@/src/libmiddle

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

$(build_dir)/src/libmiddle/%.o: src/libmiddle/%.cpp
	$(cxx) $(cflags) -c $< -o $@

$(BUILD_DIR)/src/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

build/test_parse: $(BUILD_DIR) build/libfrontend.a tests/integration/test_parse.cpp
	$(CXX) $(CFLAGS) -o $@ tests/integration/test_parse.cpp build/libfrontend.a -lstdc++ -lm

build/test_typecheck: $(BUILD_DIR) build/libfrontend.a tests/integration/test_typecheck.cpp
	$(CXX) $(CFLAGS) -o $@ tests/integration/test_typecheck.cpp build/libfrontend.a -lstdc++ -lm
