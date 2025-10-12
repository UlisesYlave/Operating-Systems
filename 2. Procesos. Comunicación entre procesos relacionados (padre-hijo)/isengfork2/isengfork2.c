#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int ii = 0;
    pid_t val1, val2, val3;

    printf("Proceso padre PID: %d\n", getpid());

    // Primer fork - equivalente al primer fork() del código original
    val1 = fork();
    if (val1 == 0) {
        // Hijo 1
        ii++;
        printf("Hijo 1 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);

        // Segundo fork dentro del hijo 1
        val2 = fork();
        if (val2 == 0) {
            // Hijo 11
            ii++;
            printf("Hijo 11 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);

            // Tercer fork dentro del hijo 11
            val3 = fork();
            if (val3 == 0) {
                // Hijo 111
                ii++;
                printf("Hijo 111 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);
                sleep(5);
                exit(0);
            }
            waitpid(val3, NULL, 0);
            sleep(5);
            exit(0);
        }
        waitpid(val2, NULL, 0);
        sleep(5);
        exit(0);
    }

    // Segundo fork en el padre principal
    val2 = fork();
    if (val2 == 0) {
        // Hijo 2
        ii++;
        printf("Hijo 2 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);

        // Fork dentro del hijo 2
        val3 = fork();
        if (val3 == 0) {
            // Hijo 21
            ii++;
            printf("Hijo 21 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);
            sleep(5);
            exit(0);
        }
        waitpid(val3, NULL, 0);
        sleep(5);
        exit(0);
    }
    // Tercer fork en el padre principal
    val3 = fork();
    if (val3 == 0) {
        // Hijo 3
        ii++;
        printf("Hijo 3 - PID: %d, PPID: %d, ii: %d\n", getpid(), getppid(), ii);
        sleep(5);
        exit(0);
    }
    char command[100];
    snprintf(command, sizeof(command), "pstree -p %d > isengfork2.txt", (int)getpid());
    system(command);

    // El padre principal espera a todos los hijos
    waitpid(val1, NULL, 0);
    waitpid(val2, NULL, 0);
    waitpid(val3, NULL, 0);

    printf("Padre final - PID: %d, Result = %3.3d\n", getpid(), ii);
    return 0;
}