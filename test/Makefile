# Makefile for test ccgi and flate.
#
# Test feature: upload file, cookie and encrypt.

TARGET = test_lsr

all: begin $(TARGET)
	@echo --------------------Built successfully--------------------
begin:
	@echo --------------------Begin buinding--------------------

CFLAGS += -I..
CFLAGS += -std=c99
CFLAGS += -Wall -Wextra

CSRCS = $(TARGET).c ../lisp-style-repl.c

$(TARGET): $(CSRCS)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(TARGET)

run:
	./$(TARGET)

.PHONY: all begin clean run

