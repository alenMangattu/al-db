# List of source files
SOURCES := connectdb.c connectdb.h loop.c loop.h main.c
CC := gcc
CFLAGS := -Wall -Wextra -g -Wpedantic
LIBS = -lpq

TARGET := build/server

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@