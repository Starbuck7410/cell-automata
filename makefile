CC = gcc
LDFLAGS = -lX11

HDR = $(wildcard headers/*)
SRC = $(wildcard src/*)
TARGET = cell-automata

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CC) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean