SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)
OBJ = $(patsubst src/%.c, %.o, $(SRC))

all: opencraft

%.o: src/%.c
	gcc -c -O2 $<

$(OBJ): $(HDR)

opencraft: $(OBJ)
	gcc -o $@ $(OBJ) -lraylib -lm

run: all
	./opencraft

clean:
	rm -f *.o opencraft

.PHONY: all run clean
