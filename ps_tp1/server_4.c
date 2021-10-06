#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/* Lorsqu’on quitte le programme avec CTRl+C, cela fonctionne comme souhaité : père et fils sont tués. 
Lorsqu’on tue le fils, le père est tué automatiquement. 
Par contre, lorsqu’on tue le père, le fils n’est pas tué !
Il faut donc faire en sorte que lorsqu’on tue le père, le fils soit tué aussi.
*/


void stop_handler(int sig)
{
    printf("Signal reçu : %d\nOn tue le fils\n", sig);
    kill(getpid() + 1, SIGTERM); // je n’ai pas trouvé comment faire pour tuer le fils plus proprement...
    printf("On tue le père à présent\n");
    exit (EXIT_SUCCESS);
}


int main(void)
{
    int     id;
    int     rand_int_p;
    int     rand_int_c;
    int     tube[2];
    struct  sigaction action;

    printf("Démarrage du programme\n");
    pipe(tube);
    id = fork();
    if (id < 0)
    {
        printf("Impossible de fork le processus\n");
        return (EXIT_FAILURE);
    }
    else if (id > 0)
    {
        // Code père
        close(tube[0]);

        action.sa_handler = stop_handler;
        sigaction(SIGTERM, &action, NULL);
        
        while (1)
        {
        rand_int_p = rand() % 100;
        write(tube[1], &rand_int_p, sizeof(int));
        printf("Je suis le père et je viens d’envoyer un nombre aléatoire à mon fils.\n");
        sleep(1);
        }
    }
    else
    {
        // Code fils
        
        close(tube[1]);
        while (1)
        {
        sleep(1);
        read(tube[0], &rand_int_c, sizeof(int));
        printf("Je suis le fils et le père m’a envoyé la valeur : %d\n", rand_int_c);
        }
    }
    return (EXIT_SUCCESS);
}