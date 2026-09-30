#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0)
    {
        value = rank * 10;

        MPI_Send(
            &value,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD
        );

        cout << "Process " << rank
             << " sent " << value << endl;
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

    MPI_Finalize();

    return 0;
}
