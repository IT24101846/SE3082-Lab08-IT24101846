#include <iostream>
#include <mpi.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int bufferSize = sizeof(int) + MPI_BSEND_OVERHEAD;
    void *buffer = malloc(bufferSize);

    MPI_Buffer_attach(buffer, bufferSize);

    if (rank != 0)
    {
        value = rank * 10;

        MPI_Bsend(
            &value,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD
        );

        cout << "Process " << rank
             << " buffered sent "
             << value << endl;
    }

    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(
                &value,
                1,
                MPI_INT,
                MPI_ANY_SOURCE,
                0,
                MPI_COMM_WORLD,
                &status
            );

            cout << "Process 0 received "
                 << value
                 << " from Process "
                 << status.MPI_SOURCE
                 << endl;
        }
    }

    MPI_Buffer_detach(&buffer, &bufferSize);
    free(buffer);

    MPI_Finalize();

    return 0;
}
