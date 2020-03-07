CXX = g++ -std=c++11 -O2

all: Hashtable

Hashtable: main.o Utility.o tests.o
	$(CXX) main.o Utility.o tests.o -o Hashtable

main.o: main.cpp
	$(CXX) -c main.cpp

Utility.o: Utility.cpp
	$(CXX) -c Utility.cpp

tests.o: tests.cpp
	$(CXX) -c tests.cpp

.PHONY: clean

clean:
	rm -rf *o Hashtable
