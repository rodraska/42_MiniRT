#include "includes/minirt.h"

static t_values intersect(t_raytracer *rt, t_cone *this)
{
    t_values local;
    t_vector p1;
    t_vector p2;
    float    value;

    rt->CO = vector_subtract(rt->O, this->vector);
    rt->a = dot(rt->D, rt->D) - this->m * pow(dot(rt->D, this->direction), 2) - pow(dot(rt->D, this->direction), 2);
    rt->b = 2 * (dot(rt->D, rt->CO) - this->m * dot(rt->D, this->direction) * dot(rt->CO, this->direction) - dot(rt->D, this->direction) * dot(rt->CO, this->direction));
    rt->c = dot(rt->CO, rt->CO) - this->m * pow(dot(rt->CO, this->direction), 2) - pow(dot(rt->CO, this->direction), 2);
    rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
    p1 = vector_add(rt->O, vector_multiply(vector(local.t1, local.t1, local.t1), rt->D));
    p2 = vector_add(rt->O, vector_multiply(vector(local.t2, local.t2, local.t2), rt->D));
    value = dot(vector_subtract(p1, this->vector), this->direction);
    if (value < 0 || value > dot(this->direction, this->direction))
        local.t1 = INT_MAX;
    value = dot(vector_subtract(p2, this->vector), this->direction);
    if (value < 0 || value > dot(this->direction, this->direction))
        local.t2 = INT_MAX; 
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
    cone->base.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->base.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->base.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->direction = vector_subtract(cone->base, cone->vector);
    cone->radius = ft_atof(&line, 1.0f, 0.0f, 0.0f) * (M_PI / 180.0);
    cone->m = pow(cone->radius / dot(cone->direction, cone->direction), 2);
    cone->color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    cone->specular = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
	cone->refletive = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	return ((t_object *)cone);
}

/* static t_values intersect(t_raytracer *rt, t_cone *this)
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
} */