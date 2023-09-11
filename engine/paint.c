/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:49 by duarte33          #+#    #+#             */
/*   Updated: 2023/09/11 16:55:30 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	get_timestamp(void)
{
	static struct timeval	init;
	struct timeval			curr;
	double					time;

	gettimeofday(&curr, NULL);
	if (init.tv_sec == 0 && init.tv_usec == 0)
		init = curr;
	time = curr.tv_sec * 1000 + curr.tv_usec / 1000.0 \
	- init.tv_sec * 1000 - init.tv_usec / 1000.0;
	if (time < 0)
		return (0);
	return (time);
}

static void	my_sleep(double duration)
{
	double	now;

	now = get_timestamp();
	while (get_timestamp() - now < duration);
}

static void paint_chunk(t_ray_thread *thread)
{
	t_chunk s;

	s.sx = 0;
    s.x = thread->x_i - 1;
	pthread_mutex_lock(&thread->th_mut);
	while (++s.x < thread->x_f)
	{
        s.sy = 0;
        s.y = -HEIGHT_2 - 1;
		while (++s.y < HEIGHT_2)
			my_mlx_pixel_put(&vars()->img, s.x + WIDTH_2, \
				s.y + HEIGHT_2, thread->color[s.sy++ * thread->delta + s.sx]);
        s.sx++;
	}
	//usleep(50);
	pthread_mutex_unlock(&thread->th_mut);
}

void paint()
{
	int	n;
	static int cnt;
	double	time;
	double  fps;

	pthread_mutex_lock(&vars()->mut);
    if (vars()->count != vars()->n_threads)
	{
		pthread_mutex_unlock(&vars()->mut);
		return ;
	}
	vars()->count = 0;
	n = -1;
	while (++n < vars()->n_threads)
		paint_chunk(&vars()->threads[n]);
	pthread_mutex_unlock(&vars()->mut);
	mlx_put_image_to_window(vars()->mlx, vars()->win, vars()->img.img, 0, 0);
	time = get_timestamp();
	cnt++;
	fps = ((double)cnt / time) * 1000;
	//printf("fps %f\n", fps);
}