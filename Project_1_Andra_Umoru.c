#include <stdio.h>     //including the C standard library
#include <mpi.h>      //Including the MPI library 

// C Language main function
int main (int argc, char** argv) {
	MPI_Request request;
	
	//Declaring the size and the rank variables
	int the_size,the_rank;
	
	//Initializing the MPI API
	MPI_Init(&argc, &argv);
 	
 	// Getting number of process
	MPI_Comm_size(MPI_COMM_WORLD, &the_size); 
    
    // Getting rank of process
	MPI_Comm_rank(MPI_COMM_WORLD, &the_rank); 
	
	//Declaring and setting the message variables to be sent over the processes
 	char right_message = 'R';
 	char left_message = 'L';
 	
 	//Initializing and setting the movement between the processes
 	int next_proc= (the_rank+1) % the_size;
 	int prev_proc = 0;
		if (the_rank == 0)
			prev_proc = the_size - 1;
		else
			prev_proc = the_rank -1;
 
 	//Sending and printing the message to the process on the right
 	MPI_Isend(&right_message, 1, MPI_UNSIGNED_CHAR, next_proc, 1, MPI_COMM_WORLD, &request);
 	printf("Process %d sent message \"%c\" to right process %d\n", the_rank, right_message, next_proc);
 
 	//Sending and printing the message to the process on the left (in a way, forming the ring)
 	MPI_Isend(&left_message, 1, MPI_UNSIGNED_CHAR, prev_proc, 2, MPI_COMM_WORLD, &request);
 	printf("Process %d sent message \"%c\" to left process %d\n", the_rank, left_message, prev_proc);
 
 	//Receiving and printing the message received from the intializing process
	MPI_Irecv(&left_message, 1, MPI_UNSIGNED_CHAR, next_proc, 1, MPI_COMM_WORLD, &request);
 	printf("Process %d received message \"%c\" from process %d\n", the_rank, left_message, next_proc);
 
 	//Receiving and printing the message received from the first process (in a way, forming the ring)
 	MPI_Irecv(&right_message, 1, MPI_UNSIGNED_CHAR, prev_proc, 2, MPI_COMM_WORLD, &request);
 	printf("Process %d received message \"%c\" from process %d\n", the_rank, right_message, prev_proc);

	//Exiting MPI routine
	MPI_Finalize();
	
	return 0;
}
