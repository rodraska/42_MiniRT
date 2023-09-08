#include "includes/minirt.h"

int		check_float(char **line)
{
	int	f;

	f = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '+' && **line != '-')
		return (0);
    (*line)++;
	while (**line && **line != ',' && !ft_isspace(**line))
	{
		if (**line == '.' && f == 0)
			f = 1;
		else if (**line == '.' && f == 1)
			return (0);
		else if (!ft_isdigit(**line) && **line != '.')
			return (0);
		(*line)++;
	}
	return (1);
}

int		check_int(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '+' && **line != '-')
		return (0);
	(*line)++;
	while (**line && **line != ',' && !ft_isspace(**line))
	{
		if (!ft_isdigit(**line))
			return (0);
		(*line)++;
	}
	return (1);
}

int		check_vector(char **line)
{
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int		check_color(char **line)
{
	if (check_int(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_int(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_int(line) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int     check_spec_ref(char **line)
{
    if (check_float(line) == 0)
		return (0);
    if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
    return (1);
}

int		check_plane(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
    if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_sphere(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line) == 0)
		return (0);
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
	if (check_float(line) == 0)
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
	if (check_float(line) == 0)
		return (0);
	if (check_float(line) == 0)
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
	if (check_float(line) == 0)
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
	if (check_float(line) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_camera(char **line, int *f)
{
	(*line)++;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	*f = 1;
	return (1);
}

int		check_repeat(t_type type)
{
	static int l;
	static int a;

	if (type == AMBIENT && a == 0)
		a = 1;
	else if (type == AMBIENT && a == 1)
		return (0);
	else if (type == POINT && l == 0)
		l = 1;
	else if (type == POINT && l == 1)
		return (0);
	return (1);
}

void	test_syntax_helper(char **line, char **head, t_type *type, int fd)
{
	free(*head);
	*line = get_next_line(fd);
	*head = *line;
	*type = ft_get_type(*line);
}

int		test_syntax2(char *line, char **head, t_type type, int fd)
{
	static int f;

	while (line != NULL)
	{
		if (check_repeat(type) == 0)
			return (0);
		if (type == PLANE && check_plane(&line) == 0)
			return (0);
		else if (type == SPHERE && check_sphere(&line) == 0)
			return (0);
		else if (type == AMBIENT && check_ambient(&line) == 0)
			return (0);
		else if (type == CONE && check_cone(&line) == 0)
			return (0);
		else if (type == CAMERA && check_camera(&line, &f) == 0)
			return (0);
		else if ((type == POINT || type == DIRECTIONAL) && check_light(&line) == 0)
			return (0);
		test_syntax_helper(&line, head, &type, fd);
	}
	free(*head);
	/* if (f == 0)
		return (0); */
	return (1);
}

int		test_syntax(char *str)
{
	int	fd;
	char *line;
	char *head;
	t_type type;
	int	 	test;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	head = line;
	type = ft_get_type(line);
	test = test_syntax2(line, &head, type, fd);
	if (test == 0)
		free(head);
	return (test);
}