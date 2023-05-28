CC=cc
CFLAGS=$$(pkg-config --cflags gtk4) -O2
LDFLAGS=$$(pkg-config --libs gtk4)

SOURCE=src
PROGNAME=fan_gui
PREFIX=/usr/local

.PHONY: install

$(PROGNAME): $(SOURCE)/main.c
	$(CC) $(CFLAGS) -o $(PROGNAME) $(SOURCE)/main.c $(LDFLAGS)
	strip $(PROGNAME)

install: $(PROGNAME)
	cp $(PROGNAME) $(PREFIX)/bin
