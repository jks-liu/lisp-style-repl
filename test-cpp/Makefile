# Makefile for test ccgi and flate.
#
# Test feature: upload file, cookie and encrypt.

TARGET = test_lsr_cpp

all: begin $(TARGET)
	@echo --------------------Built successfully--------------------
begin:
	@echo --------------------Begin buinding--------------------

CFLAGS += -I..
CFLAGS += -std=c99
CFLAGS += -Wall -Wextra
CFLAGS += -O2

CPPFLAGS += -I..
CPPFLAGS += -std=c++11
CPPFLAGS += -Wall -Wextra
CPPFLAGS += -O2
CPPFLAGS += -Drestrict=__restrict__

CSRCS = ../lisp-style-repl.c

CPPSRCS =  $(TARGET).cpp

$(TARGET): $(CSRCS) $(CPPSRCS)
	gcc -c -o $(patsubst %.c, %.o, $(CSRCS))  $(CSRCS) $(CFLAGS)
	gcc -c -x c++ -o $(patsubst %.cpp, %.o, $(CPPSRCS)) $(CPPSRCS) $(CPPFLAGS)
	gcc -o $(TARGET) $(patsubst %.c, %.o, $(CSRCS)) $(patsubst %.cpp, %.o, $(CPPSRCS))  $(CFLAGS)
	

clean:
	rm -rf $(TARGET)
	rm -rf $(patsubst %.c, %.o, $(CSRCS))
	rm -rf $(patsubst %.cpp, %.o, $(CPPSRCS))

run:
	./$(TARGET)

.PHONY: all begin clean run

