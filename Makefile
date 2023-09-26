# Copyright Razvan-Constantin Rus 312CAa 2022-2023

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) *.c -o my_octave

pack:
	zip -FSr 312CA_RusRazvan-Constantin_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
