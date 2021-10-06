#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int running = 1;

void exit_message()
{
    printf("Fin du programme\n");
}

void stop_handler(int sig)
{
    printf("Signal reçu : %d\n--- Interruption du main ---\n", sig);
    running = 0;
    /* Si on supprime la ligne running = 0 :
    Il faut deux CTRL+C à présent pour arrêter le programme.
    Idem pour la commande kill.
    Par contre kill -9 termine toujours le programme instantanément.
    */
}

int main(void)
{
    struct  sigaction action;
    int     i;

    action.sa_handler = stop_handler;
    sigaction(SIGINT, &action, NULL);

    /* On ajoute la ligne suivante pour que stop_handler soit appelé
    lorsqu’on appelle la commande kill sans préciser de signal (envoi de SIGTERM). */

    sigaction(SIGTERM, &action, NULL);

     /* On tente d’ajouter la ligne suivante pour que stop_handler soit appelé
    lorsqu’on appelle la commande kill -9 mais ça ne fonctionne pas, le signal est "trop puissant". */

    sigaction(SIGKILL, &action, NULL);

    /* Si on execute la commande kill avec le nom du père, rien ne se passe, par contre si on appelle la commande 
    kill -9, cela quitte le terminal 1 où le programme était exécuté. */

    printf("Hello world\n");
    while (running)
    {
        printf("Mon PID est : %d\nCelui de mon père est : %d\n", getpid(), getppid());
        printf("Voici un nombre aléatoire : %d\n", rand() % 100);
        sleep(1);
    }
    printf("Fin de la boucle while\n");

    /* Si on remet la ligne running = 0, le message de fin est affiché
    si on termine le programme avec CTRL+C, kill mais pas avec un kill -9 */

    i = atexit(exit_message);
    if (i != 0)
    {
        fprintf(stderr, "Cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}