#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define DISPLAY1 "PID INDUK** ** pid (%5.5d) ** ***********\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) -- val3(%5.5d)\n"

int main (void) {
    pid_t val1, val2, val3;
    printf(DISPLAY1, (int) getpid());
    fflush(stdout);
    // Crear árbol de procesos
    val1 = fork();
    if (val1 == 0) {
        // Hijo 1
        val2 = fork();
        if (val2 == 0) {
            // Hijo 11
            val3 = fork();
            if (val3 == 0) {
                // Hijo 111
                sleep(5);  // Tiempo para ejecutar pstree
                exit(0);
            }
            sleep(5);
            waitpid(val3, NULL, 0);
            exit(0);
        }
        sleep(5);
        waitpid(val2, NULL, 0);
        exit(0);
    }
    val2 = fork();
    if (val2 == 0) {
        // Hijo 2
        val3 = fork();
        if (val3 == 0) {
            // Hijo 23
            sleep(5);
            exit(0);
        }
        sleep(5);
        waitpid(val3, NULL, 0);
        exit(0);
    }
    val3 = fork();
    if (val3 == 0) {
        // Hijo 3
        sleep(5);
        exit(0);
    }
    // Automáticamente ejecutar pstree y guardar en archivo
    char command[100];
    snprintf(command, sizeof(command), "pstree -p %d > multifork2.txt", (int)getpid());
    system(command);
    printf("Árbol de procesos guardado en 'arbol.txt'\n");
    // Esperar a todos los hijos
    waitpid(val1, NULL, 0);
    waitpid(val2, NULL, 0);
    waitpid(val3, NULL, 0);
    printf(DISPLAY2, (int) val1, (int) val2, (int) val3);
    return 0;
}