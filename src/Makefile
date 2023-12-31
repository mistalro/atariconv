TARGET = ataribasictolisting

GCC = g++
LIBS = -lcurses
CFLAGS = -g 

HEADERS = \
	fileio.h \
	mem.h \
	dump.h \
	decode.h \
	tokens.h \
	process.h \
	repair.h \
	atari.h
SRC = \
	fileio.c \
	mem.c \
	dump.c \
	decode.c \
	tokdump.c \
	tokens.c \
	process.c \
	repair.c \
	main.c

HEADER = atari.h

all: $(SRC) $(TARGET)

OBJ := $(SRC:.c=.o)

$(TARGET): $(OBJ) $(HEADERS)
	$(GCC) $(SRC) $(CFLAGS) -o $(TARGET) $(LIBS)

clean: 
	rm -f $(OBJ) $(TARGET)
