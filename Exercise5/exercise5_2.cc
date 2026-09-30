#include <iostream>
#include <mpi.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int value = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int bufferSize = sizeof(int) + MPI_BSEND_OVERHEAD;
    void *buffer = malloc(bufferSize);

    MPI_Buffer_attach(buffer, bufferSize);

    if (rank == 0)
    {
        cout << "Process 0 sending value: " << value << endl;

        MPI_Bsend(
            &value,
            1,
            MPI_INT,
            1,
            0,
            MPI_COMM_WORLD
        );

        cout << "Buffered send completed." << endl;
    }

    else if (rank == 1)
    {
        MPI_Recv(
            &value,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );

        cout << "Process 1 received value: " << value << endl;
    }

    MPI_Buffer_detach(&buffer, &bufferSize);
    free(buffer);

    MPI_Finalize();

    return 0;
}
