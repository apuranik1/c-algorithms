CC = gcc
SHELL = /bin/sh
CFLAGS = -std=c99 -Wall
LDLIBS = -lpthread
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXECUTABLE = main


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDLIBS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -r $(OBJDIR)
