.PHONY: all clean

default: all

all: edf-anonymizer

edf-anonymize: edf-anonymizer.c
	gcc -g -Wall edf-anonymizer.c -o edf-anonymizer

clean: 
	rm edf-anonymizer