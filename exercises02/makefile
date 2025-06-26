CFLAGS=-Wall -g
.PHONY: clean all	
targets = ex1
sources = ex1.c
objects = ex1.o
all: $(targets)
	@echo "all done"
clean:
	rm -f *.o $(targets)
%.o: %.c
	gcc -c $< -o $@
$(targets): $(objects)
	gcc $(objects) -o $@
