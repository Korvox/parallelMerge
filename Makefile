$CC = gcc
PTSRCS = pthreads/merge.c pthreads/merge.h

CFLAGS = -O2 -std=c1x -Wall
LFLAGS = -pthread -o $(PROG)
RMFLAGS = -f

$(NUMTHREADS) = 8
FILEPARAS = $(NUMTHREADS) data.txt
RNGPARAS = $(NUMTHREADS) 4096

ptc:$(CC) $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(LFLAGS) $(SRCS)
	
mpic:

cudac:

	
test: $(PROG)
	$(PROG) $(FILEPARAS) > fileOut.txt
	$(PROG) $(RNGPARAS) > rngOut.txt

	
clean:
	rm $(RMFLAGS) $(PROG)
