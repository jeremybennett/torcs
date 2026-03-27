# Makefile for tmath unit tests
#
# Usage:
#   make        - build and run tests
#   make build  - build only
#   make run    - run tests (builds first if needed)
#   make clean  - remove build artifacts

SRCROOT  = ../..
MATHDIR  = $(SRCROOT)/src/libs/math

CXX      = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -I.

TARGET   = test_math

.PHONY: all build run clean

all: run

# Create a 'tmath' symlink so that <tmath/v2_t.h> etc. resolve correctly
# without requiring a full install of the project headers.
tmath:
	ln -sf $(MATHDIR) tmath

build: tmath $(TARGET)

$(TARGET): test_math.cpp tmath
	$(CXX) $(CXXFLAGS) -o $@ test_math.cpp

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) tmath
