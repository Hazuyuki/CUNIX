CFILES = $(wildcard *.c) 
TARGETS = $(CFILES:.c=) 
CC ?= clang 
CFLAGS = -Wall -DDEBUG -g3 -g
all: $(TARGETS)
$(TARGETS): $(CFILES) 
	$(CC) $(CFLAGS) -o $@ $(@:=.c) -lm
clean: $(TARGETS) 
	rm $(TARGETS)
