#include "includes/minirt.h"

void    raytracer_threads(t_ray_thread *thread)
{
	int			x;
	int			sx;
    int         sy;

	int			y;
    t_raytracer rt;
    t_scene *scene;

    //printf("index %d\n", thread->index);
    scene = vars()->scene;
    bzero(&rt, sizeof(t_raytracer));
    rt.O = vector(0, 0, 0);
    sx = 0;
    x = thread->x_i;
	while (x < thread->x_f)
	{
        sy = 0;
        y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
            rt.closest_obj = NULL;
			canvas_to_viewport(&rt, x, y); //get D
			thread->color[sy * thread->delta + sx] = new_trace_ray(NULL, rt.O, rt.D, scene, &rt, 1);
			y++;
            sy++;
		}
        sx++;
        x++;
	}
}

void    *routine(void *arg)
{
    t_ray_thread *thread;

    thread = (t_ray_thread*)arg;
    while (1)
    {  
        //printf("OLA %d %d\n", thread->x_i, thread->x_f);
        pthread_mutex_lock(&thread->th_mut);
        raytracer_threads(thread);
        pthread_mutex_lock(&vars()->mut);
        vars()->count++;
        pthread_mutex_unlock(&vars()->mut);
        usleep(100);
    }
    free(thread->color);
    if (pthread_join(thread->thread, NULL))
    {
        printf("Error joining threads\n");
        return (-1);
    }
    return (NULL);
}

int ft_init_threads()
{
    int i;
    t_ray_thread *thread;

    thread = calloc(sizeof(t_ray_thread), vars()->n_threads);
    vars()->thread = thread;
    vars()->count = 0;
    pthread_mutex_init(&vars()->mut, NULL);
    i = -1;
    while (++i < vars()->n_threads)
    {
        pthread_mutex_init(&vars()->thread[i].th_mut, NULL);
        thread[i].index = i;
        thread[i].x_i = -WIDTH_2 + WIDTH * i / vars()->n_threads;
        thread[i].x_f = -WIDTH_2 + WIDTH * (i + 1) / vars()->n_threads;
        thread[i].color = calloc(sizeof(int), (int)(HEIGHT) * (int)WIDTH / vars()->n_threads);
        thread[i].delta = WIDTH / vars()->n_threads;
        if (pthread_create(&(vars()->thread[i].thread), NULL, \
        &routine, (void *)(&thread[i])) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
    }
    return (0);
}