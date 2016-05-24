CXX = g++
LIBSRC = solve_inverse_mechanism.cpp
SRC = $(LIBSRC) test.cpp
TARGET = test 
LIB = mysolver

UNAME_S := $(shell uname -s)

#LINUX
ifeq ($(UNAME_S),Linux)
CPPFLAGS = -std=c++11 -Wno-c++11-extensions -I/usr/include/eigen3
lib:
	$(CXX) $(CPPFLAGS) -shared -o $(LIB).so $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(SRC)	
endif

#OSX
ifeq ($(UNAME_S),Darwin)
CPPFLAGS = -std=c++11 -Wno-c++11-extensions 
lib:
	$(CXX) $(CPPFLAGS) -dynamiclib -o $(LIB).dylib $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(SRC)	
endif

.PHONY: clean
clean:
	rm $(TARGET) 
