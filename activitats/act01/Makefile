CC=gcc
CFLAGS=-c -Wall
SOURCES=rmsf.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rmsf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
        $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
        $(CC) $(CFLAGS) $< -o $@

execute: $(EXECUTABLE)
         ./rmsf

install: $(EXECUTABLE)
        su root -c "cp $(EXECUTABLE) /usr/bin"
remove:
        su root -c "rm /usr/bin/rmsf"

clean:
        /bin/rm -rf *.o *~
        /bin/rm -rf $(EXECUTABLE)