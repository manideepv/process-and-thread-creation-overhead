CC = gcc
DEBUG = 
CFLAGS =  -c $(DEBUG)
LFLAGS =  -pthread $(DEBUG)

all: Process Thread Context_Switch

Process:
	$(CC) process.c -o process

Thread: 
	$(CC) thread.c $(LFLAGS) -o thread

Context_Switch: 
	$(CC) context_switch.c -o context_switch

clean:
	rm  process thread context_switch

tar:
	tar cvf santosh.tar *.c Makefile

