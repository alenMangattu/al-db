# List of source files
SOURCES := main.c connectdb.c connectdb.h
CC := gcc
CFLAGS := -Wall -Wextra -g -Wpedantic
LIBS = -lpq

TARGET := build/server

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@