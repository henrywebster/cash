CC = gcc
CFLAGS = -Wall

PROGNAME = cash

DBGFLAGS = -g
NPROMPTFLAGS = -D NO_PROMPT=1

# Default
all : release

noprompt : $(PROGNAME) 
noprompt : CFLAGS += $(NPROMPTFLAGS)

debug : $(PROGNAME)
debug : CFLAGS += $(DBGFLAGS)

release : $(PROGNAME)

$(PROGNAME) : cash.o src/main.c
	$(CC) $(CFLAGS) $^ -o $@

cash.o : src/cash.h src/cash.c
	$(CC) $(CFLAGS) -c $^

.PHONY : clean debug release noprompt

clean : 
	rm *.o *~ src/*~ src/*gch $(PROGNAME)
