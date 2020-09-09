CC ?= "cc"
all: krv

krv: main.c src/as.c src/dis.c src/run.c src/common.c
	$(CC) main.c src/as.c src/dis.c src/run.c src/common.c -o krv $(CFLAGS)
