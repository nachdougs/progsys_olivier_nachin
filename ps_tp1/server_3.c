#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
    int     id;
    pid_t   pid;

    printf("Hello world\n");
    id = fork();
    if (id < 0)
    {
        printf("Impossible de fork le processus\n");
        return (EXIT_FAILURE);
    }

    while (1)
    {
        if (id == 0)
        {
            /* On rajoute -- avant les messages du fils afin de les distinguer de ceux du père. Les deux processus
            sont tués avec CTRL+C.
            On utilise kill pour tuer uniquement le fils :
            - cela semble arrêter le programme fils mais la ligne suivante reste visible avec ps a :
            12644 s000  Z+     0:00.00 (main)
            - cette ligne disparait lorsqu’on tue le père.
            */
            printf("-- Je suis le fils\n");
            printf("-- Mon PID est : %d\n-- Celui de mon père est : %d\n", getpid(), getppid());
            printf("-- Voici un nombre aléatoire : %d\n", rand() % 100);
            sleep(1);
        }
        else
        {
            pid = wait(NULL);
            if (pid >= 0)
                printf("Le fils vient de se terminer, avec le code retour : %d\n", pid);
            else
                printf("Mon fils est déjà terminé, pid a la valeur : %d\n", pid);
            printf("Je suis le père !\n");
            printf("Mon PID est : %d\nCelui de mon père est : %d\n", getpid(), getppid());
            printf("Voici un nombre aléatoire : %d\n", rand() % 100);
            sleep(1);
        }
    }
    printf("Fin de la boucle while\n");

    return (EXIT_SUCCESS);
}