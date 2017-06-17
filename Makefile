FONTES=$(wildcard *.c)
OBJECTS=$(FONTES:.c=.o)
FLAGS= -lm -I.

.PHONY: all clean

all: solver

%.o: %.c
	gcc -g -c $< -o $@ $(FLAGS)

solver: $(OBJECTS)
	gcc -g -o $@ $^ $(FLAGS)

clean:
	rm $(OBJECTS) solver
