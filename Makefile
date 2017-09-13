CC = gcc
CFLAGS = -Wall -g

PROGNAME = cash

$(PROGNAME) : cash.o src/main.c
	$(CC) $(CFLAGS) $^ -o $@

cash.o : src/cash.h src/cash.c
	$(CC) $(CFLAGS) -c $^
.PHONY : clean

clean : 
	rm *.o *~ src/*~ $(PROGNAME)
