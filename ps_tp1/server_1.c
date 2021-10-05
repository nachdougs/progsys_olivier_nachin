#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello world\n");
    while (1)
    {
        printf("Mon PID est : %d\nCelui de mon père est : %d\n", getpid(), getppid());
        printf("Voici un nombre aléatoire : %d\n", rand() % 100);
        sleep(1);
    }
    printf("Fin de la boucle while\n");
    return (EXIT_SUCCESS);
}