# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=archiver

build: $(TARGETS)

archiver: archiver.c
	$(CC) $(CFLAGS) archiver.c -o archiver


clean: 
	rm -f $(TARGETS)
