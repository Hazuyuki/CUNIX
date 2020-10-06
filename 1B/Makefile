CFILES = $(wildcard *.c) 
TARGETS = $(CFILES:.c=) 
CC ?= clang
CFLAGS = -Wall -DDEBUG -g3
all: $(TARGETS)
$(TARGETS): $(CFILES) 
	$(CC) $(CFLAGS) -o $@ $(@:=.c) -lm
clean: $(TARGETS) 
	rm $(TARGETS)
