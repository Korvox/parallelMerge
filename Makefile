$CC = gcc
SRCS = ptMerge.c
HEADERS = ptMerge.h
PROG = ptMerge
CFLAGS = -O2 -std=c1x -Wall
LFLAGS = -pthread -o $(PROG)
RMFLAGS = -f

$(NUMTHREADS) = 8
FILEPARAS = $(NUMTHREADS) data.txt
RNGPARAS = $(NUMTHREADS) 4096

compile:$(CC) $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(LFLAGS) $(SRCS)

test: $(PROG)
	./$(PROG) $(FILEPARAS) > fileOut.txt
	./$(PROG) $(RNGPARAS) > rngOut.txt

clean:
	rm $(RMFLAGS) $(PROG)
