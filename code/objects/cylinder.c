/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:58:25 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 17:39:02 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
/* Esta funcao recebe uma cilindro e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/

float	distance(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) \
		+ pow(v1.z - v2.z, 2)));
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

static t_values check_height(t_raytracer *rt, t_cylinder *this, t_values t)
{
	t_vector p;
	t_vector b;
	float	 k;

	p = vector_add(rt->o, vector_mult_const(rt->d, t.t1));
	k = dot(p, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	b = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (abs(distance(b, this->vector)) > this->height / 2 )
		t.t1 = INT_MAX;
	p = vector_add(rt->o, vector_mult_const(rt->d, t.t2));
	k = dot(p, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	b = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (abs(distance(b, this->vector)) > this->height/2)
		t.t2 = INT_MAX;
	return t;
}

static void rotate(t_cylinder *this)
{	
    rotation_x(&this->axis, this->theta);
	rotation_y(&this->axis, this->phi);
	rotation_z(&this->axis, this->qsi);

	this->theta = 0.0f;
	this->phi = 0.0f;
	this->qsi = 0.0f;
}

static t_values intersect(t_raytracer *rt, t_cylinder *this)
{
	t_values local;
	t_values local_up_cap;
	t_values local_down_cap;
	t_vector co;

	co = vector_subtract(rt->o, this->vector);
	rt->a = dot(rt->d, rt->d) * pow(module(this->axis), 2) - \
		pow(dot(rt->d, this->axis), 2);
	rt->b = 2.0f * dot(co, rt->d) * pow(module(this->axis), 2) - \
		2.0f * dot(rt->d, this->axis) * dot(co, this->axis);
	rt->c = (dot(co, co) - pow(this->diameter / 2, 2)) * pow(module(this->axis), 2) - \
		pow(dot(co, this->axis), 2);
	rt->discriminant = rt->b * rt->b - 4.0f * rt->a * rt->c;
	if (rt->discriminant < 0.001f) // No solution
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-rt->b + sqrt(rt->discriminant)) / (2.0f * rt->a));
	local.t2 = ((-rt->b - sqrt(rt->discriminant)) / (2.0f * rt->a));
	local = check_height(rt, this, local);
	return local;
}

t_object* new_cylinder(char* line)
{
	t_cylinder	*cylinder;
	float 		t[2];

	cylinder = new_object(sizeof(t_cylinder));
	cylinder->intersect = intersect;
	cylinder->rotate = rotate;
	cylinder->type = CYLINDER;
	cylinder->vector.x = ft_atof(&line);
	cylinder->vector.y = ft_atof(&line);
	cylinder->vector.z = ft_atof(&line);
	cylinder->axis.x = ft_atof(&line);
	cylinder->axis.y = ft_atof(&line);
	cylinder->axis.z = ft_atof(&line);
	cylinder->diameter = ft_atof(&line);
	cylinder->height = ft_atof(&line);
	cylinder->color.r = (int)ft_atof(&line);
    cylinder->color.g = (int)ft_atof(&line);
    cylinder->color.b = (int)ft_atof(&line);
	cylinder->specular = (int)ft_atof(&line);
	cylinder->refletive = ft_atof(&line);
	cylinder->intensity = ft_atof(&line);
	cylinder->checkerboard = (int)ft_atof(&line);
	cylinder->theta = 0.0f;
	cylinder->phi = 0.0f;
	cylinder->qsi = 0.0f;
	return ((t_object *)cylinder);
}
	