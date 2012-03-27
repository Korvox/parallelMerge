iosrcs = parsing/parsing.c
iobjs = $(iosrcs:.c=.o)
smsrcs = serialMerge.c

ptargs = -O2 -std=c1x -Wall -pthread -o
ptsrcs = pthreads/merge.c
ptprog = pthreads/merge

mpiargs = --hostfile cluster
mpisrcs = mpi/merge.c
mpiprog = mpi/merge

cudaargs = 
cudasrcs = cuda/merge.c
cudaprog = cuda/merge

serialprog = serial
serialcflags = -c -Wall -std=c1x
seriallflags = -o $(serialprog)
serialsrcs = serial/serial.c
serialobjs = $(serialsrcs:.c=.o)

rmflags = -f

# pipe compiler errors to file w/ (make serialc 3>&1 1>&2- 2>&3-) > errors.txt

ptc: $(iosrcs) $(smsrcs) $(ptsrcs)
	gcc $(ptargs) $(iosrcs) $(smsrcs) $(ptsrcs) $(ptprog)
	
mpic: $(iosrcs) $(smsrcs) $(mpisrcs) 
	mpicc $(mpiargs) $(iosrcs) $(smsrcs) $(mpisrcs) $(mpiprog)

cudac: $(iosrcs) $(smsrcs) $(cudasrcs)

serialc: $(iosrcs) $(serialsrcs)
	gcc $(serialcflags) $(iosrcs) $(serialsrcs) serialTesting.c

$(serialprog): $(seriallflags) $(serialobjs) 
	gcc $(seriallflags) $(serialobjs) $(ioobjs) serialTesting.o

serialtest: $(serialprog)
	./$(serialprog) 1024
	
.PHONY: clean
clean:
	rm $(rmflags) $(ptprog) $(mpiprog) $(cudaprog) $(serialprog) $(ioprog)
