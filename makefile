#need to add support for cross compile
COMP=g++

#we'll want to try and use C11 threads if the cross compiler can do it
FLAGS=-lpthreads --std=c++11
OUT= NetComm.o

all : Test.cpp NetComm.cpp NetComm.h 
	$(COMP) Test.cpp NetComm.cpp NetComm.h -o test

#kest.o : Test.cpp
	#$(COMP) -c Test.cpp -o Test.o

#NetComm.o: NetComm.cpp NetComm.h
	#$(COMP) -c NetComm.cpp NetComm.h -o NetComm.o

clean :
	rm test
