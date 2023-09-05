#include "includes/minirt.h"

static t_values intersect(t_raytracer *rt, t_cone *this)
{
    t_values local;

    rt->CO = vector_subtract(rt->O, this->vector);
    rt->a = pow(dot(rt->D, this->direction), 2) - pow(cos(this->theta), 2);
    rt->b = 2 * dot(rt->D, this->direction) * dot(rt->CO, this->direction) - dot(rt->D, rt->CO) * pow(cos(this->theta), 2);
    rt->c = pow(dot(rt->CO, this->direction), 2) - dot(rt->CO, rt->CO) * pow(cos(this->theta), 2);
    rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	return local;
}

t_object* new_cone(char *line)
{
    t_cone *cone;

    cone = new_object(sizeof(t_cone));
    cone->intersect = intersect;
    cone->type = CONE;
    cone->vector.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->vector.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->vector.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->direction.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->direction.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->direction.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->theta = ft_atof(&line, 1.0f, 0.0f, 0.0f) * (M_PI / 180.0);
    cone->color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->specular = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
	cone->refletive = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	return ((t_object *)cone);
}