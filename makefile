.PHONY: all clean

default: all

all: edf-anonymize

edf-anonymize: edf-anonymize.c
	gcc -g -Wall edf-anonymize.c -o edf-anonymize

clean: 
	rm edf-anonymize