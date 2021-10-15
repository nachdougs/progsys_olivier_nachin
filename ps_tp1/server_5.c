#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int running = 1;
int STOPCODE = -1;
int fd;

void stop_handler(int sig)
{
    printf("Signal reçu : %d, on quitte la boucle while et ferme la FIFO\n", sig);
    write(fd, &STOPCODE, sizeof(int));
    running = 0;
}

int main(void)
{
    
    int     rand_int;
    struct  sigaction action;

    action.sa_handler = stop_handler;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    printf("Démarrage du server\n");
    printf("Ouverture de la FIFO\n");
    fd = open("myfifo", O_WRONLY);
    printf("Client connecté\n");
    while (running)
    {
        rand_int = rand() % 100;
        write(fd, &rand_int, sizeof(int));
        printf("Je suis le serveur et d’écrire le nombre : %d dans la FIFO\n", rand_int);
        sleep(1);
    }
    close(fd);
    printf("FIFO fermée\n");
    return (EXIT_SUCCESS);
}