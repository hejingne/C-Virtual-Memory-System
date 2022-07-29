CC = gcc
CFLAGS := -g3 -Wall -Wextra -Werror $(CFLAGS)
LDFLAGS := $(LDFLAGS)

.PHONY: all clean

all: sim

sim: clock.o fifo.o lru.o mru.o pagetable.o rand.o sim.o swap.o
	$(CC) $^ -o $@ $(LDFLAGS)

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

-include $(OBJ_FILES:.o=.d)

%.o: %.c
	$(CC) $< -o $@ -c -MMD $(CFLAGS)

clean:
	rm -f $(OBJ_FILES) $(OBJ_FILES:.o=.d) sim swapfile.*
