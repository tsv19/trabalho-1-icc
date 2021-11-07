CFLAGS = -Wall

LIBS = -lm -I/usr/include -L/usr/lib -lmatheval

objects = main.o newtonSNL.o utils.o 

all: newtonSNL

newtonSNL: $(objects)
	gcc $(CFLAGS) $(objects) -o newtonSNL $(LIBS)

main.o: main.c
	gcc -c $(CFLAGS) main.c $(LIBS)

newtonSNL.o: newtonSNL.c newtonSNL.h
	gcc -c $(CFLAGS) newtonSNL.c $(LIBS)

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) utils.c $(LIBS)

clean: 
	rm $(objects)
	rm newtonSNL