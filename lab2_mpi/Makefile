build-mpi:
	mpic++ main.cpp -o main.o

CFLAGS = -np 4

run-mpi: build-mpi
	mpirun $(CFLAGS) main.o
