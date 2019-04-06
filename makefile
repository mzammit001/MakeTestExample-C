CC = clang
CFLAGS =
OBJECTS = ring_queue.o
OBJECTS_TEST = $(OBJECTS) test_ring_queue.o
OBJECTS_MAIN = $(OBJECTS) queuer.o

BIN_TEST = test_ring_queue
BIN_MAIN = queuer

all: main test

main: $(OBJECTS_MAIN)
	  $(CC) -o $(BIN_MAIN) $(CFLAGS) $(OBJECTS_MAIN)

test: $(OBJECTS_TEST)
	  $(CC) -o $(BIN_TEST) $(CFLAGS) $(OBJECTS_TEST)

$(OBJECTS_MAIN): ring_queue.h queuer.h
$(OBJECTS_TEST): ring_queue.h test_ring_queue.h

clean: 
		rm *.o $(BIN_TEST) $(BIN_MAIN)