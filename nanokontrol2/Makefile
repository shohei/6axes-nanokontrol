CXX = g++
LIBSRC = solve_inverse_mechanism.cpp
SRC = $(LIBSRC) test.cpp
TARGET = test 
CPPFLAGS = -std=c++11 -Wno-c++11-extensions 
LIB = mysolver

UNAME_S := $(shell uname -s)

#LINUX
ifeq ($(UNAME_S),Linux)
lib:
	$(CXX) $(CPPFLAGS) -shared -o $(LIB).so $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(SRC)	
endif

#OSX
ifeq ($(UNAME_S),Darwin)
lib:
	$(CXX) $(CPPFLAGS) -dynamiclib -o $(LIB).dylib $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(SRC)	
endif

.PHONY: clean
clean:
	rm $(TARGET) 
