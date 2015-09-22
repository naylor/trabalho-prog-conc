# MAKEFILE #

#INFORMANDO O COMPILADOR, 
#DIRETÓRIOS E O 
#NOME DO PROGRAMA
CC=gcc
G=g++
SRCDIR=src/
SRCEXT=c
OBJEXT=o
PROG=trabalho-prog-conc

# FLAGS NECESSARIAS
# PARA COMPILACAO
CFLAGS=-Wall -Wextra 
LIB=-lpthread 

#-------------------------------
# CARREGA AUTOMATICAMENTE OS
# ARQUIVOS .C E .H
#-------------------------------
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
