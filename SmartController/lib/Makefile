.PHONY: all clean

all: static clean

static: obj
		ar rv libgpio2.a gpio.o && ranlib libgpio2.a

obj:
		$(CC) -c gpio.c

clean:
		rm *.o
