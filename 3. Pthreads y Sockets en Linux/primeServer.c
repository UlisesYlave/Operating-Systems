#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define SOCKET_PATH "/tmp/prime_socket"

// Función para verificar si un número es primo usando factor
int es_primo(int numero) {
    int pipefd[2];
    pid_t pid;
    char command[100];
    char buffer[100];
    int es_primo = 0;

    if (pipe(pipefd) == -1) {
        return 0;
    }

    pid = fork();
    if (pid == 0) {
        // Proceso hijo
        close(pipefd[0]); // Cerrar lectura
        dup2(pipefd[1], STDOUT_FILENO); // Redirigir salida al pipe
        close(pipefd[1]);

        execl("/usr/bin/bash", "bash", "-c", "factor", (char*)NULL);
        exit(1);
    } else if (pid > 0) {
        // Proceso padre
        close(pipefd[1]); // Cerrar escritura

        // Escribir número al proceso factor
        FILE *fp = fdopen(pipefd[0], "r");
        if (fp != NULL) {
            fprintf(fp, "%d\n", numero);
            fflush(fp);

            // Leer resultado
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                // Analizar resultado: contar factores
                char *token;
                int count = 0;

                token = strtok(buffer, " :\n");
                while (token != NULL) {
                    count++;
                    token = strtok(NULL, " :\n");
                }

                es_primo = (count == 2); // Solo el número y él mismo
            }
            fclose(fp);
        }

        waitpid(pid, NULL, 0); // Esperar al hijo
        close(pipefd[0]);
    }

    return es_primo;
}

void *manejar_cliente(void *socket) {
    int client_sock = *(int*)socket;
    free(socket);
    int cantidad_numeros;

    // Leer cantidad de números
    if (read(client_sock, &cantidad_numeros, sizeof(cantidad_numeros)) != sizeof(cantidad_n>        close(client_sock);
        pthread_exit(NULL);
    }

    printf("Cliente solicita procesar %d números\n", cantidad_numeros);

    int numeros_primos[100]; // Máximo 100 números primos
    int contador_primos = 0;

    // Leer y procesar cada número
    for (int i = 0; i < cantidad_numeros; i++) {
        int numero;
        if (read(client_sock, &numero, sizeof(numero)) != sizeof(numero)) {
            break;
        }

        printf("Procesando número: %d\n", numero);

        // Verificar si es primo
        if (es_primo(numero)) {
            numeros_primos[contador_primos++] = numero;
            printf("  → %d es PRIMO\n", numero);
        } else {
            printf("  → %d NO es primo\n", numero);
        }
    }

    // Enviar cantidad de primos encontrados
    write(client_sock, &contador_primos, sizeof(contador_primos));

    // Enviar los números primos
    for (int i = 0; i < contador_primos; i++) {
        write(client_sock, &numeros_primos[i], sizeof(numeros_primos[i]));
    }

    printf("Enviados %d números primos al cliente\n", contador_primos);
    close(client_sock);
    pthread_exit(NULL);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    // Crear socket
    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket");
        exit(1);
    }

    // Eliminar socket anterior si existe
    unlink(SOCKET_PATH);

    // Configurar dirección
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_sock);
        exit(1);
    }
    // Listen
    if (listen(server_sock, 5) == -1) {
        perror("listen");
        close(server_sock);
        exit(1);
    }

    printf("Servidor de números primos iniciado en %s\n", SOCKET_PATH);
    printf("Usando 'factor' para determinar números primos\n");

    while (1) {
        client_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock == -1) {
            perror("accept");
            continue;
        }

        printf("Nuevo cliente conectado\n");

        // Crear thread para manejar cliente
        pthread_t thread_id;
        int *client_sock_ptr = malloc(sizeof(int));
        *client_sock_ptr = client_sock;

        if (pthread_create(&thread_id, NULL, manejar_cliente, client_sock_ptr) != 0) {
            perror("pthread_create");
            free(client_sock_ptr);
            close(client_sock);
        } else {
            pthread_detach(thread_id);
        }
    }

    close(server_sock);
    unlink(SOCKET_PATH);
    return 0;
}