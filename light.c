#include "includes/minirt.h"

int shadow_light(t_vars *vars, t_raytracer *rt)
{
	t_object *obj;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = rt->rl.P;
	newRT.D = rt->rl.L;
	obj = closest_intersection(vars, &newRT, 0.001f, INT_MAX);
	return (obj != NULL);
}

void specular_light(t_object *tmp, t_vars *vars, t_raytracer *rt)
{
	if (rt->rl.s)
	{
		rt->rl.aux = vector(2*dot(rt->rl.N, rt->rl.L), 2.0f*dot(rt->rl.N, rt->rl.L), 2.0f*dot(rt->rl.N, rt->rl.L));
		rt->rl.R = vector_subtract(vector_multiply(rt->rl.N, rt->rl.aux), rt->rl.L);
		rt->rl.r_dot_v = dot(rt->rl.R, rt->rl.V);
		if(rt->rl.r_dot_v > 0.001f) 
			rt->rl.i += tmp->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s);
	}
}

void diffuse_light(t_object *tmp, t_vars *vars, t_raytracer *rt)
{
	rt->rl.n_dot_l = dot(rt->rl.N, rt->rl.L);
	if (rt->rl.n_dot_l > 0.001f)
		rt->rl.i += (tmp->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L));
}

float compute_light(t_vars *vars, t_raytracer *rt)
{
	t_object *tmp;

	rt->rl.i = 0.0f;
	tmp = vars->light;
 	while(tmp)
	{	
		if (tmp->type == AMBIENT)
			rt->rl.i += tmp->intensity;
		else
		{
			if (tmp->type == POINT)
				rt->rl.L = vector_subtract(tmp->vector, rt->rl.P);
			else if(tmp->type == DIRECTIONAL)
				rt->rl.L = tmp->vector;
			if (shadow_light(vars, rt))
			{
				tmp = tmp->next;
			 	continue;
			}
			diffuse_light(tmp, vars, rt);
			specular_light(tmp, vars, rt);
		}
		tmp = tmp->next;
	}
	return rt->rl.i;
}

t_object *new_light(char *line, t_type type)
{
	t_light *new_light;
	
	new_light = new_object(sizeof(t_light));
	new_light->type = type;
	if (new_light->type != AMBIENT)
	{
		new_light->vector.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	    new_light->vector.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	    new_light->vector.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	}
	new_light->intensity = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    new_light->color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    new_light->color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    new_light->color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
	return ((t_object *)new_light);
}