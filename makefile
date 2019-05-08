CC=gcc
CFLAGS=-O3 -W
TARGET=simulador
HDR=$(wildcard *.h)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
HDRC=$(HDR:.h=.h.gch)

all: $(TARGET)
# regras para gerar o executavel
$(TARGET) : .c
	$(CC) -o $@ $(OBJ) $(CFLAGS)

# regras de compilação
.c:
	$(CC) -c $(SRC) $(CFLAGS)

# .h:
# 	$(CC) -c $(HDR) $(CFLAGS)

clean:
	rm -rf $(OBJ) $(HDRC)

clear:
	rm -rf $(TARGET)
