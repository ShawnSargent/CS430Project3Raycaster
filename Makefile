CC       = gcc
DEBUG    = -g
CFLAGS   = -Wall -std=c99 -pedantic $(DEBUG)

# Grabs all .c files
CFILES   = $(wildcard *.c)

# grabs all .o files (renamed .c files)
OBJFILES = $(CFILES:.c=.o)

# executable file name
EXECFILE = v3test

# compile to executable by default 
all : $(EXECFILE)

# compiles to executable using dependancies ($@ = EXECFILE $^ = OBJFILES)
$(EXECFILE) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

# Generates .o files from .c files (to be used by OBJFILES)
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY : clean

# Deletes everything.
clean :
	rm -f $(OBJFILES) $(EXECFILE)