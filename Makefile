iosrcs = parsing.c parsing.h

ptargs = -O2 -std=c1x -Wall -pthread -o
ptsrcs = pthreads/merge.c pthreads/merge.h
ptprog = pthreads/merge

mpiargs = --hostfile cluster
mpisrcs = mpi/merge.c mpi/merge.h
mpiprog = mpi/merge

cudaargs = 
cudasrcs = cuda/merge.c cuda/merge.h
cudaprog = cuda/merge

rmflags = -f

ptc: $(iosrcs) $(ptsrcs)
	gcc $(ptargs) $(iosrcs) $(ptsrcs) $(ptprog)
	
mpic: $(iosrcs) $(mpisrcs) 
	mpicc $(mpiargs) $(iosrcs) $(mpisrcs) $(mpiprog)

cudac: $(iosrcs) $(cudasrcs)
	

clean:
	rm $(rmflags) $(ptprog) $(mpiprog) $(cudaprog)
