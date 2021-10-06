#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int running = 1;

void stop_handler(int sig)
{
    printf("Signal reçu : %d\n--- Interruption du main ---\n", sig);
    running = 0;
}

int main(void)
{
    struct sigaction action;

    action.sa_handler = stop_handler;
    sigaction(SIGINT, &action, NULL);

    printf("Hello world\n");
    while (running)
    {
        printf("Mon PID est : %d\nCelui de mon père est : %d\n", getpid(), getppid());
        printf("Voici un nombre aléatoire : %d\n", rand() % 100);
        sleep(1);
    }
    printf("Fin de la boucle while\n");
    return (EXIT_SUCCESS);
}