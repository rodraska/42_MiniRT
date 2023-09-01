#include "includes/minirt.h"

void    raytracer_threads(int i)
{
    int x;
    int y;

    x = -WIDTH_2 + WIDTH * i / vars->n_threads;
    while (x < -WIDTH_2 + WIDTH * (i + 1) / vars->n_threads)
    {   
        y = -HEIGHT_2;
        while (++y < HEIGHT_2)
        {
            vars->buf[x][y] = y;
            y++;
        }
        x++;
    }
}

void    *routine(void *arg)
{
    int i;

    i = (int)arg;
    while (1)
    {
        //raytracer_threads()
        printf("%d\n", i);
    }
    return (NULL);
}

int ft_join_threads()
{
    int i;

    i = -1;
    while (++i < vars->n_threads)
    {
        if (pthread_join(vars->thread[i], NULL))
        {
            printf("Error joining threads\n");
            return (-1);
        }
    }
    return (0);
}

int ft_init_threads()
{
    int i;

    i = -1;
    
    while (++i < vars->n_threads)
    {
        printf("hehe\n");
        if (pthread_create(&(vars->thread[i]), NULL, \
        &routine, (void *)(intptr_t)i) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
    }
    return (0);
}