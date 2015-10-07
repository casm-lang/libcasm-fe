LEX = flex
CXX = clang
CFLAGS = -Isrc -Ibuild/src -std=c++11 -O0 -g
# -stdlib=libstdc++
BUILD_DIR = build
AR = /usr/bin/ar

SRC = $(shell find src -name '*.cpp' | cut -d'.' -f1)

OBJS = $(SRC:%=build/%.o)

.PHONY: all clean test

all: lib

clean:
	rm -rf build

test: build/test_parse build/test_typecheck
	python tests/integration/test_runner.py

$(BUILD_DIR):
	mkdir -p $@/src/libsyntax
	mkdir -p $@/src/libutil
	mkdir -p $@/src/libmiddle

build/libfrontend.a: build/src/libsyntax/parser.o build/src/libsyntax/lexer.o $(OBJS)
	@echo "AR  " $@
	@$(AR) rsc build/libfrontend.a $(OBJS) build/src/libsyntax/lexer.o build/src/libsyntax/parser.o
	@ranlib build/libfrontend.a

lib: $(BUILD_DIR) build/libfrontend.a

build/src/libsyntax/parser.cpp: src/libsyntax/grammer.yy
	@echo "YAC " $<
	@cd build/src/libsyntax && bison --output parser.cpp --defines=parser.tab.h ../../../src/libsyntax/grammer.yy

$(BUILD_DIR)/src/libsyntax/lexer.cpp: src/libsyntax/lexer.l
	@echo "LEX " $<
	@$(LEX) $(LFLAGS) -o $(BUILD_DIR)/src/libsyntax/lexer.cpp src/libsyntax/lexer.l

$(BUILD_DIR)/src/libsyntax/%.o: build/src/libsyntax/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libutil/%.o: src/libutil/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/src/libsyntax/%.o: src/libsyntax/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(build_dir)/src/libmiddle/%.o: src/libmiddle/%.cpp
	@echo "CPP " $<
	@$(cxx) $(cflags) -c $< -o $@

$(BUILD_DIR)/src/%.o: src/%.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -c $< -o $@

build/test_parse: $(BUILD_DIR) build/libfrontend.a tests/integration/test_parse.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_parse.cpp build/libfrontend.a -lstdc++ -lm

build/test_typecheck: $(BUILD_DIR) build/libfrontend.a tests/integration/test_typecheck.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_typecheck.cpp build/libfrontend.a -lstdc++ -lm

build/test_dump: $(BUILD_DIR) build/libfrontend.a tests/integration/test_dump.cpp
	@echo "CPP " $<
	@$(CXX) $(CFLAGS) -o $@ tests/integration/test_dump.cpp build/libfrontend.a -lstdc++ -lm
