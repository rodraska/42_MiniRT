/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:41:14 by duarte33          #+#    #+#             */
/*   Updated: 2023/09/11 00:20:17 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

void choose_normal(t_raytracer* rt, t_object *obj)
{
	if (obj->type == SPHERE)
		rt->rl.N = vector_subtract(rt->rl.P, obj->vector);
	else if (obj->type == PLANE)
		rt->rl.N = obj->vector;
	else if (obj->type == CYLINDER)
		rt->rl.N = vector_subtract(rt->rl.P, obj->vector);
}

t_vector reflected_ray(t_vector R, t_vector N)
{
	double 	 dotN_R;
	t_vector Rfinal;

	dotN_R = 2.0f*dot(N, R);
	Rfinal = vector_subtract(vector_mult_const(N, dotN_R), R);
	return Rfinal;
}