#need to add support for cross compile
COMP=g++

#we'll want to try and use C11 threads if the cross compiler can do it
FLAGS= -c -lpthreads
OUT= NetComm.o

all : NetComm.cpp NetComm.h
	$(COMP) NetComm.cpp NetComm.h $(FLAGS) -o $(OUT)

clean :
	rm *.o
