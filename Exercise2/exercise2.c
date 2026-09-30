#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;

    long long N = 10000000;

    long long start;
    long long end;
    long long local_sum = 0;
    long long total_sum = 0;

    double start_time;
    double end_time;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long chunk = N / size;

    start = rank * chunk + 1;

    if (rank == size - 1)
        end = N;
    else
        end = (rank + 1) * chunk;

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    for (long long i = start; i <= end; i++)
    {
        local_sum += i;
    }

    MPI_Reduce(
        &local_sum,
        &total_sum,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    end_time = MPI_Wtime();

    printf(
        "Process %d calculated %lld to %lld, Local Sum = %lld\n",
        rank,
        start,
        end,
        local_sum
    );

    if (rank == 0)
    {
        printf("\nTotal Sum = %lld\n", total_sum);
        printf("Number of Processes = %d\n", size);
        printf("Execution Time = %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
