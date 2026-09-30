#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;

    long long total_points = 10000000;
    long long local_points;
    long long local_inside = 0;
    long long total_inside = 0;

    double x, y;
    double pi;
    double start_time, end_time;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_points = total_points / size;

    if (rank == size - 1)
    {
        local_points += total_points % size;
    }

    srand(1234 + rank);

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    for (long long i = 0; i < local_points; i++)
    {
        x = 2.0 * rand() / RAND_MAX - 1.0;
        y = 2.0 * rand() / RAND_MAX - 1.0;

        if ((x * x + y * y) <= 1.0)
        {
            local_inside++;
        }
    }

    MPI_Reduce(
        &local_inside,
        &total_inside,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    end_time = MPI_Wtime();

    if (rank == 0)
    {
        pi = 4.0 * total_inside / total_points;

        printf("Total Points = %lld\n", total_points);
        printf("Points Inside Circle = %lld\n", total_inside);
        printf("Calculated Pi = %.10f\n", pi);
        printf("Number of Processes = %d\n", size);
        printf("Execution Time = %f seconds\n",
               end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
