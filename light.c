#include "includes/minirt.h"

float compute_light(t_vars *vars, t_light *this, t_raylight *rl)
{
	int j;
	t_light *tmp;

	rl->i = 0.0f;
	tmp = vars->light;
 	while(tmp)
	{
		if (tmp->type == AMBIENT)
			rl->i += tmp->intensity;
		else
		{
			if (tmp->type == POINT)
				rl->L = vector_subtract(tmp->position, rl->P);
			else if(tmp->type == DIRECTIONAL)
				rl->L = tmp->position;

			//Diffuse
			rl->n_dot_l = dot(rl->N, rl->L);
			if (rl->n_dot_l > 0.001f)
				rl->i += (tmp->intensity * rl->n_dot_l)/(module(rl->N)*module(rl->L));
			
			//Specular
			if (rl->s)
			{
				rl->aux = vector(2*dot(rl->N, rl->L), 2*dot(rl->N, rl->L), 2*dot(rl->N, rl->L));
				rl->R = vector_subtract(vector_multiply(rl->N, rl->aux), rl->L);
				rl->r_dot_v = dot(rl->R, rl->V);
				if(rl->r_dot_v > 0.001f) 
					rl->i += tmp->intensity * pow(rl->r_dot_v / (module(rl->R)*module(rl->V)), rl->s);
			}
		}
		tmp = tmp->next;
	}
	return rl->i;
}

t_light *new_light(float intensity, t_vector pos, t_type type)
{
	t_light *new_light;
	
	new_light = (t_light*)new_object(sizeof(t_light));
	new_light->intensity = intensity;
	new_light->position = vector(pos.x, pos.y, pos.z);
	new_light->type = type;
	return (new_light);
}

t_object	*parse_point(char *line)
{
    t_vector coord;
    float   ratio;
    t_color color;

    coord.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    coord.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    coord.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);

    ratio = ft_atof(&line, 1.0f, 0.0f, 0.0f);

    color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);

	return (new_light(ratio, coord, POINT));
}

t_object	*parse_ambient(char *line)
{
    float i;
    t_color color;
	t_vector coord;

    i = ft_atof(&line, 1.0f, 0.0f, 0.0f);

    color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);

	coord.x = 0;
	coord.y = 0;
	coord.z = 0;

	return (new_light(i, coord, AMBIENT));
}