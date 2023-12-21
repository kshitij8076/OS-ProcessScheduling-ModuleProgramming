#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <math.h>


int main()
{
    FILE *file = fopen("../src/output.csv", "w");
    pid_t pid1, pid2, pid3;
    struct timespec start_timeA, end_timeA, start_timeB, end_timeB, start_timeC, end_timeC;
    double execution_timeA, execution_timeB, execution_timeC;
    clock_gettime(CLOCK_MONOTONIC, &start_timeA);

    pid1 = fork();
    if (pid1 == 0)
    {
        nice(0);
        sched_setscheduler(pid1, SCHED_OTHER, &(struct sched_param){.sched_priority = 0});
        execl("./count", "./count", (char *)NULL);
        perror("execl");
        exit(1);
    }
    else if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }

    else
    {
        clock_gettime(CLOCK_MONOTONIC, &start_timeB);
        pid2 = fork();
        if (pid2 == 0)
        {
            sched_setscheduler(pid2, SCHED_RR, NULL);
            execl("./count", "./count", (char *)NULL);
            perror("execl");
            exit(1);
        }
        else if (pid2 < 0)
        {
            perror("fork");
            exit(1);
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC, &start_timeC);
            pid3 = fork();
            if (pid3 == 0)
            {
                sched_setscheduler(pid3, SCHED_FIFO, NULL);
                execl("./count", "./count", (char *)NULL);
                perror("execl");
                exit(1);
            }
            else if (pid3 < 0)
            {
                perror("fork");
                exit(1);
            }
            else
            {
                waitpid(pid3, NULL, 0);
                clock_gettime(CLOCK_MONOTONIC, &end_timeC);
                execution_timeC = (end_timeC.tv_sec - start_timeC.tv_sec) +
                                  (end_timeC.tv_nsec - start_timeC.tv_nsec) / 1e9;
                fprintf(file, "Exection time of FIFO is : %.2lf", execution_timeC);
                fprintf(file, "\n");
            }

            waitpid(pid2, NULL, 0);
            clock_gettime(CLOCK_MONOTONIC, &end_timeB);
            execution_timeB = (end_timeB.tv_sec - start_timeB.tv_sec) +
                              (end_timeB.tv_nsec - start_timeB.tv_nsec) / 1e9;
            fprintf(file, "Exection time of RR is : %.2lf", execution_timeB);
            fprintf(file, "\n");
        }

        waitpid(pid1, NULL, 0);
        clock_gettime(CLOCK_MONOTONIC, &end_timeA);
        execution_timeA = (end_timeA.tv_sec - start_timeA.tv_sec) +
                          (end_timeA.tv_nsec - start_timeA.tv_nsec) / 1e9;
        fprintf(file, "Exection time of OTHER is : %.2lf", execution_timeA);
        fprintf(file, "\n");
    }


    printf("Total execution time of Other: %.2lf seconds\n", execution_timeA);
    printf("Total execution time of RR: %.2lf seconds\n", execution_timeB);
    printf("Total execution time of FIFO:  %.2lf seconds\n", execution_timeC);

    return 0;
}
