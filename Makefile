iosrcs = parsing.c
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

rmflags = -f

ptc: $(iosrcs) $(smsrcs) $(ptsrcs)
	gcc $(ptargs) $(iosrcs) $(smsrcs) $(ptsrcs) $(ptprog)
	
mpic: $(iosrcs) $(smsrcs) $(mpisrcs) 
	mpicc $(mpiargs) $(iosrcs) $(smsrcs) $(mpisrcs) $(mpiprog)

cudac: $(iosrcs) $(smsrcs) $(cudasrcs)
	
.PHONY: clean
clean:
	rm $(rmflags) $(ptprog) $(mpiprog) $(cudaprog)
