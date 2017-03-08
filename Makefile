CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lhidapi-libusb
SOURCES=main.cpp Keyboard.cpp Color.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=msi-keyboard

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

