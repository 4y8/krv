CC ?= "cc"
all: krv

krv: main.c src/as.c src/dis.c src/run.c
	$(CC) main.c src/as.c src/dis.c src/run.c -o krv $(CFLAGS)
