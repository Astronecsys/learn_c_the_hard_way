CFLAGS=-Wall -g
.PHONY: clean all

SOURCES := $(wildcard ex*.c)
OBJECTS := $(SOURCES:.c=.o)
TARGETS := $(SOURCES:.c=)

all: $(TARGETS)
	@echo "Build complete: $(TARGETS)"
	
clean:
	rm -f $(TARGETS) $(OBJECTS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(CFLAGS) $< -o $@

