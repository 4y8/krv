CC ?= cc
PREFIX ?= /usr/local
MANPREFIX ?= $(PREFIX)/share/man

all: krv

krv: main.c src/as.c src/dis.c src/run.c src/common.c
	$(CC) main.c src/as.c src/dis.c src/run.c src/common.c -o krv $(CFLAGS)

install: krv
	install -Dm 755 krv $(PREFIX)/bin/krv
	install -Dm 644 krv.1 $(MANPREFIX)/man1/krv.1

uninstall: 

.PHONY: install uninstall all
