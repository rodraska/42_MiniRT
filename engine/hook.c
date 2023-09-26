/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/09/11 00:58:29 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_object *mouse_trace_ray(t_vars *vars ,t_raytracer *rt)
{
	float 	 dotN_R;
	float	 r;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = rt->O;
	newRT.D = rt->D;
	newRT.closest_obj = closest_intersection(&newRT);
    if (!(newRT.closest_obj))
       return NULL;
	light_prepare(&newRT, newRT.closest_obj);
	newRT.local_color = color_multiply(newRT.closest_obj->color, compute_light(&newRT));
	return (newRT.closest_obj);
}

static int ft_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	if (scene->select)
		scene->select->vector.z +=  ((button == 5) - (button == 4)) * 0.05;
	else 
		scene->camera->vector.z +=  ((button == 4) - (button == 5)) * 0.05;
	return 0;
}

int	ft_close(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	//mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

static void camera_move(int keycode)
{
	if (keycode == XK_w || keycode == XK_s)
		vars()->scene->camera->vector.z += ((keycode == XK_w) - (keycode == XK_s))*0.05;
	if (keycode == XK_a || keycode == XK_d)
		vars()->scene->camera->vector.x += ((keycode == XK_d) - (keycode == XK_a))*0.05;
	if (keycode == XK_1 || keycode == XK_2)
		vars()->scene->camera->vector.y += ((keycode == XK_1) - (keycode == XK_2)) * 0.05;
	if (keycode == XK_q || keycode == XK_e)
	 	vars()->scene->camera->phi += ((keycode == XK_e) - (keycode == XK_q)) * 0.01;
	if (keycode == XK_3 || keycode == XK_4)
	 	vars()->scene->camera->theta += ((keycode == XK_3) - (keycode == XK_4)) * 0.01;
}

int	ft_key(int keycode)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars()->mlx, vars()->win);
		free(vars()->mlx);
		exit(0);
	}
	if (vars()->scene->select)
	{
		vars()->scene->select->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
		vars()->scene->select->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
		vars()->scene->select->vector.z +=  ((keycode == 'z') - (keycode == 'x')) * 0.05;
		// if (keycode == XK_6)
		// 	vars()->scene->select->rotate(vars()->scene->select, X_theta_2);
		//printf("y: %f, x: %f z: %f\n", vars->select->vector.y, vars->select->vector.x, vars->select->vector.z);
	}
	camera_move(keycode);
	if (keycode == XK_8 && vars()->scene->next)
	{
		//printf("ola %d\n", vars()->scene->next);
		vars()->scene = vars()->scene->next;
	}
	if (keycode == XK_9 && vars()->scene->prev)
		vars()->scene = vars()->scene->prev;
	return (0);
}

int ft_mouse_down(int button, int x, int y)
{
	t_raytracer rt;
	x -= WIDTH_2;
	y -= HEIGHT_2;

	if ((button == 5) || (button == 4))
		return (ft_mouse_scroll(button, x, y, vars()->scene));
	if (vars()->scene->select && button == 3)
	{
		vars()->scene->select->vector.x = ((float)(x))*(1.5f/WIDTH_2);
		vars()->scene->select->vector.y = -((float)(y))*(1.5f/HEIGHT_2);
		return (0);
	}
	rt.O = vars()->scene->camera->vector;	
	canvas_to_viewport(&rt, x, y); //get D
	vars()->scene->select = mouse_trace_ray(vars, &rt); //get color
	return 0;
}