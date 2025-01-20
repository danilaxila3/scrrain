CC := gcc
CFLAGS := -Wall -Wextra
LFLAGS := $(shell pkgconf --cflags --libs ncursesw)
SRC_DIR := src
SRC := scrrain.c
BIN_DIR := bin
BIN := scrrain

all: $(BIN_DIR)/$(BIN)

$(BIN_DIR)/$(BIN): $(SRC_DIR)/$(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $< $(LFLAGS) -o $@

clean:
	rm -r bin
