#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* Même principe que précédemment, lorsqu’on quitte le client, le serveur est automatiquement arrêté car l’OS considère que 
ça ne sert à rien de continuer à écrire dans la FIFO s’il n’y a personne pour lire. A contrario, si on quitte d’abord le serveur
le client peut continuer à lire, nous devons donc faire en sorte qu’il soit arrêté automatiquement, pour cela, on écrit -1
dans la FIFO, et on fait en sorte que le client s’arrête lorsqu’il lit -1.*/

int STOPCODE = -1;

int main(void)
{
    int fd;
    int rand_int;

    printf("Démarrage du client\n");
    printf("Ouverture de la FIFO\n");
    fd = open("myfifo", O_RDONLY);
    printf("FIFO ouverte en lecture\n");
    while (1)
    {
        read(fd, &rand_int, sizeof(int));
        if (rand_int != STOPCODE)
            printf("Je suis le client et je viens de lire le nombre : %d dans la FIFO\n", rand_int);
        else
        {
            printf("Le serveur est arrêté, le client s’arrête aussi\n");
            break;
        }
        sleep(1);
    }
    close(fd);
    printf("FIFO fermée\n");
    return (EXIT_SUCCESS);
}