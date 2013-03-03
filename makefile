#need to add support for cross compile
COMP=g++

#we'll want to try and use C11 threads if the cross compiler can do it
FLAGS=-lpthread --std=c++11
OUT=test

all : Test.o NetComm.o
	$(COMP) Test.o NetComm.o $(FLAGS) -o $(OUT)

Test.o : Test.cpp
	$(COMP) -c Test.cpp $(FLAGS)

NetComm.o: NetComm.cpp NetComm.h
	$(COMP) -c NetComm.cpp NetComm.h $(FLAGS)

clean :
	rm test *.o
