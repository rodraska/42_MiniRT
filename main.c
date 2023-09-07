#include "includes/minirt.h"

t_vars *vars()
{
	static t_vars my_vars;
	return (&my_vars);
}

double	get_timestamp(void)
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

void	my_sleep(double duration)
{
	double	now;

	now = get_timestamp();
	while (get_timestamp() - now < duration);
}

void paint_chunk(t_ray_thread *thread)
{
	int	x;
	int	y;
	int	sx;
	int sy;

	sx = 0;
    x = thread->x_i;
	while (x < thread->x_f)
	{
        sy = 0;
        y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
			my_mlx_pixel_put(&vars()->img, x + WIDTH_2, y + HEIGHT_2, thread->color[sy * thread->delta + sx]);
			y++;
            sy++;
		}
        sx++;
        x++;
	}
}

void paint()
{
	int	n;
	static int cnt;
	double	time;
	double  fps;
	static double	wait;

	
	pthread_mutex_lock(&vars()->mut);
    if (vars()->count != vars()->n_threads)
	{
		pthread_mutex_unlock(&vars()->mut);
		return;
	}
	vars()->count = 0;

	n = -1;
	while (++n < vars()->n_threads)
		paint_chunk(&vars()->thread[n]);
	
	mlx_put_image_to_window(vars()->mlx, vars()->win, vars()->img.img, 0, 0);

	time = get_timestamp();
	if (cnt == 0)
		cnt = 1;
	else
		cnt++;
	fps = ((double)cnt / time) * 1000;
	//printf("cnt %d\n", cnt);
	//printf("time %f\n", time);
	printf("fps %f\n", fps);
	//wait = ((1.0 / 5.0) - (1 / fps)) * 1000.0;
	if (wait == 0)
		wait = 50;
	if (fps > 5)
	{
		H;
		wait += 10;
	}
	else
	{
		T;
		wait -= 10;
	}
		
	printf("wait %f\n", wait);
	if (wait > 0)
	{
		//usleep(wait * 1000);
		my_sleep(wait);
	}
	n = -1;
	while (++n < vars()->n_threads)
		pthread_mutex_unlock(&vars()->thread[n].th_mut);
	pthread_mutex_unlock(&vars()->mut);
}


void init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->	//vars->objects[0] = new_object(sizeof(t_object));
	img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, ft_key, NULL);
	mlx_hook(vars->win, 4, 1L<<2, ft_mouse_down, NULL);
	//mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);
}

int create_scene(char *arg)
{
	int fd;
	static t_scene *end_scene;
	t_scene *head;

	head = ft_calloc(sizeof(t_scene), 1);
	vars()->map_file = arg;
	fd = check_map();
	if (fd == -1)
	{
		printf("Error openning the file!");
		return 3;
	}
	while (map_loading(head, fd))
		;
	close(fd);
	if (!vars()->scene)
		vars()->scene = head;
	else 
		end_scene->next = head;
	end_scene = head;
	return 0;
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 2)
	{
		if (!test_syntax(av[1]))
		{
			close(&vars);
			printf("Bad Map\n");
			return (0);
		}
		while (av[++i])
			create_scene(av[i]);
		init_window(vars());
		vars()->n_threads = 10;
		ft_init_threads();
		mlx_loop_hook(vars()->mlx, paint, NULL);
		mlx_loop(vars()->mlx);
		pthread_mutex_destroy(&vars()->mut);
		free(vars()->thread);
	}
	else
		write(1, "Not enough arguments\n", 22);
}