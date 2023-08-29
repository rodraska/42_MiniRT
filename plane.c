#include "includes/minirt.h"


/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_plane *this)
{
	t_values local;
	float d;

	d = -dot(this->direction, this->vector);
	rt->b = dot(this->direction, rt->D);
	rt->c = (-1)*dot(this->direction, rt->O) + d;
	if (rt->b < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = rt->c / rt->b; 
	local.t2 = rt->c / rt->b; 
	return local;
}

t_object* new_plane(t_vector coord, t_vector direction, t_color color, int specular)
{
	t_plane *plane;

	plane = new_object(sizeof(t_plane));
	plane->intersect = intersect;
	plane->type = PLANE;
	plane->vector = coord;
	plane->color = color;
	plane->direction = direction;
	plane->specular = specular;
	plane->next = NULL;
	return ((t_object *)plane);
}

t_object    *parse_plane(char *line)
{
    t_vector coord;
    t_vector normal;
    t_color color;

    coord.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    coord.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    coord.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);

    normal.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    normal.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    normal.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);

    color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);

	return (new_plane(coord, normal, color, 100));
}
	