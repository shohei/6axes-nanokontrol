CXX = g++
LIBSRC = solve_inverse_kinematics.cpp
SRC = $(LIBSRC) test_inverse_kinematics.cpp
TARGET = test_inverse_kinematics
LIB = mysolver
BINDIR = ../bin
LIBDIR = ../lib

UNAME_S := $(shell uname -s)

#LINUX
ifeq ($(UNAME_S),Linux)
CPPFLAGS = -std=c++11 -Wno-c++11-extensions -I/usr/include/eigen3
lib:
	$(CXX) $(CPPFLAGS) -shared -o $(LIBDIR)/$(LIB).so $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(BINDIR)/$(TARGET) $(SRC)	
endif

#OSX
ifeq ($(UNAME_S),Darwin)
CPPFLAGS = -std=c++11 -Wno-c++11-extensions 
lib:
	$(CXX) $(CPPFLAGS) -dynamiclib -o $(LIBDIR)/$(LIB).dylib $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(BINDIR)/$(TARGET) $(SRC)	
endif

.PHONY: clean
clean:
	rm $(TARGET) 
