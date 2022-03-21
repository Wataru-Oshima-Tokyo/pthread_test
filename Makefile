CC = g++
LIBS = -pthread

all: create_thread

create_thread: pthread_test.cpp
	$(CC) pthread_test.cpp -Wall -o $@ $(LIBS)