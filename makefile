CC := gcc # NTS overwrite with x86_64-w64-mingw32-gcc to cross-compile to 64bit Windows
CFLAGS := -g -Wall
OBJECTS := mini-hexdump.o edf-anonymizer.o edf-header.o commandline.o messages.o

.PHONY: all clean

default: all

all: edf-anonymizer

%.o: %.c
	@echo Generating object file $@...
	@$(CC) $(CFLAGS) -c $< -o $@

edf-anonymizer: $(OBJECTS)
	@echo Compiling $@...
	@$(CC) $(CFLAGS) $^ -o $@
	@echo Done!

clean:
	@echo Cleaning files...
	@rm -f *.o edf-anonymizer EDF-anonymizer.exe
	@echo Done!
