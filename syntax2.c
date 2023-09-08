#include "includes/minirt.h"

int		check_sphere(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	T;
	if (check_color(line) == 0)
		return (0);
    if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_cone(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_cylinder(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_light(char **line)
{
	(*line)++;
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 0) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_ambient(char **line)
{
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}