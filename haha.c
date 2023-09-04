#include <stdio.h>
#include <unistd.h>

int main()
{
    long numThreads = sysconf(_SC_NPROCESSORS_ONLN); // Obtém o número de threads disponíveis
    if (numThreads == -1)
    {
        perror("Erro ao obter o número de threads disponíveis");
        return 1;
    }

    printf("Número de threads disponíveis: %ld\n", numThreads);

    return 0;
}