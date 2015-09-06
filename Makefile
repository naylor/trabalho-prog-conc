# MAKEFILE #

#The Directories, Source, Includes, Objects, Binary and Resources
CC=gcc
G=g++
SRCDIR=src/
SRCEXT=c
OBJEXT=o
PROG=trabalho

#Flags, Libraries and Includes
CFLAGS=-Wall -Wextra 
LIB=-lpthread

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES=$(wildcard $(SRCDIR)*.c)
HEADERS=$(wildcard $(SRCDIR)*.h)


all: $(PROG)

$(PROG): $(SOURCES:.c=.o)
	$(G) -o $@ $^ $(LIB) 

%.o: %.c $(HEADERS)
	$(CC) -g -c $< -o $@

clean:
	rm -f $(SRCDIR)*.o
	rm -f $(PROG)
