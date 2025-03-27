CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS =
SOURCES = arithmetic.c other.c service_fun.c sup_arithmetic.c test.c
OBJECTS = $(SOURCES:.c.h = .o)
EXECUTABLE = my_decimal

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(OBJECTS) -o $@

clang:
	clang-format -i $(SOURCES)

rebuild: clean $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)