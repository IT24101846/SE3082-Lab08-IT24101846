#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int value = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        cout << "Process 0 is sending to Process 1" << endl;

        MPI_Send(
            &value,
            1,
            MPI_INT,
            1,
            0,
            MPI_COMM_WORLD
        );
    }

    else if (rank == 1)
    {
        cout << "Process 1 is waiting for Process 2" << endl;

        MPI_Recv(
            &value,
            1,
            MPI_INT,
            2,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );

        cout << "Received value = " << value << endl;
    }

    MPI_Finalize();

    return 0;
}
