CC=gcc
CFLAGS=-c -Wall -O3 -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion
pipes= pipes.c
OBJECTS_pipes=$(pipes:.c=.o)
pipes_EXECUTABLE=pipes

all: $(pipes) $(pipes_EXECUTABLE) 
	
$(pipes_EXECUTABLE): $(OBJECTS_pipes)
	$(CC) $(OBJECTS_pipes) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

execute: $(pipes_EXECUTABLE)
	 ./$(pipes_EXECUTABLE)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf $(pipes_EXECUTABLE) 