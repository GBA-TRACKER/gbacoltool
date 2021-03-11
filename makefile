## ---------------------------------------------------------------------
## Set phony & default targets, and override the default suffix rules.
## ---------------------------------------------------------------------
.PHONY: build install clean
.SUFFIXES:

.DEFAULT_GOAL := build

## ---------------------------------------------------------------------
## Setup project details.
## ---------------------------------------------------------------------

TARGET   := $(shell basename ${CURDIR})
BUILD    := 
SOURCES  := obj
DATA     := 
INCLUDES := inc
DEST     ?= /bin/

LIBS     := 
LIBDIRS  := 

OBJS     := ${TARGET}.o

## ---------------------------------------------------------------------
## Set flags for code generation.
## ---------------------------------------------------------------------

CC       := gcc
LD       := gcc
OBJCOPY  := objcopy

CFLAGS   =  -Wall -O3\
	-funsigned-char\
	-fomit-frame-pointer -fno-strict-aliasing -fshort-enums\
	-fno-printf-return-value

ifdef INCLUDE
	CFLAGS += ${INCLUDE}
endif

LDFLAGS  := ${CFLAGS}

## ---------------------------------------------------------------------
## Compilation rules.
## ---------------------------------------------------------------------

.INTERMEDIATE: ${TARGET}.elf
.DELETE_ON_ERROR: ${OBJS} ${TARGET}.elf

build: ${TARGET}
	chmod +x $<

## Strip binaries.
${TARGET}: ${TARGET}.elf
	-@echo 'Stripping symbols from "$<"... ("$<"->"$@")'
	${OBJCOPY} -vgO elf64-x86-64 $< $@

## Link objects.
${TARGET}.elf: ${TARGET}.o ${OBJS}
	-@echo 'Linking objects... ("$^"->"$@")'
	${LD} $^ $(LDFLAGS) -o $@

## Compile objects.
${OBJS}: %.o : %.c
	-@echo 'Compiling object "$@"... ("$<"->"$@")'
	${CC} ${CFLAGS} -c $< -o $@

## Install built file.
install: ${TARGET}
	-@echo 'Installing "$<"...'
	chmod +x $<
	chown root:root $<
	cp -vf $< ${DEST}

## Remove unnecessary binary files.
.IGNORE: clean
clean:
	-@echo 'Cleaning up intermediary files...'
	@rm -vf ${SOURCES}/*.o *.o *.elf

## EOF
