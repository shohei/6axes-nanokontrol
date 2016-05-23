CXX = g++
LIBSRC = solve_inverse_mechanism.cpp
SRC = $(LIBSRC) test.cpp
TARGET = test 
CPPFLAGS = -std=c++11 -Wno-c++11-extensions \
	-I/usr/local/opt/eigen/include/eigen3/ 
LIB = mysolver

lib:
	$(CXX) $(CPPFLAGS) -dynamiclib -o $(LIB).dylib $(LIBSRC)

test:
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(SRC)	


.PHONY: clean
clean:
	rm $(TARGET) 
