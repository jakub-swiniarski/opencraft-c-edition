SOURCES=$(wildcard src/*.c)
HEADERS=$(wildcard src/*.h)
OBJECTS=$(patsubst src/%.c,%.o,$(SOURCES))

opencraft: $(OBJECTS)
	gcc -o $@ $(OBJECTS) -lraylib

$(OBJECTS): $(SOURCES) $(HEADERS)
	gcc -c $(SOURCES) -O2

.PHONY: clean run install uninstall

clean:
	rm *.o opencraft

run: opencraft
	./opencraft

install: opencraft res
	mkdir -p /usr/local/share/opencraft/
	cp opencraft /usr/local/bin/
	cp res/* /usr/local/share/opencraft/

uninstall:
	rm /usr/local/bin/opencraft
	rm -rf /usr/local/share/opencraft
