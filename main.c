#include "includes/minirt.h"

t_vars *vars()
{
	static t_vars my_vars;
	return (&my_vars);
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
	mlx_hook(vars->win, 2, 1L<<0, ft_key, vars);
	mlx_hook(vars->win, 4, 1L<<2, ft_mouse_down, vars);
	//mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		vars()->n_threads = 5;
		vars()->thread = (pthread_t *)malloc(sizeof(pthread_t) * vars()->n_threads);
		ft_init_threads();
		ft_join_threads();
	}
	else
		write(1, "Not enough arguments\n", 22);
}