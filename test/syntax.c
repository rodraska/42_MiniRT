#include "test.h"

int		check_vector(char **line)
{
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (check_float(line) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int		check_float(char **line)
{
	int	f;

	f = 0;
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

int		check_color(char **line)
{
	if (check_int(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (check_int(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (check_int(line) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int		check_int(char **line)
{
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

int		check_plane(char **line)
{
	(*line) += 2;
	while (ft_isspace(**line))
		(*line)++;
	if (check_vector(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_vector(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_sphere(char **line)
{
	(*line) += 2;
	while (ft_isspace(**line))
		(*line)++;
	if (check_vector(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_light(char **line)
{
	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (check_vector(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
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
	while (ft_isspace(**line))
		(*line)++;
	if (check_float(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

t_type ft_get_type(char *line)
{
	if (line)
    {
        if (line[0] == '\n')
            return EMPTY_LINE;
        if (line[0] == 'A')
            return AMBIENT;
        if (line[0] == 'L')
            return POINT;   
        if ((line)[0] == 's' && (line)[1] == 'p') 
            return SPHERE;
        if ((line)[0] == 'p' && (line)[1] == 'l') 
            return PLANE;
        if ((line)[0] == 'c' && (line)[1] == 'y') 
            return CYLINDER;
    }
	return ERROR;
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

int		test_syntax2(char *line, char **head, t_type type, int fd)
{
	while (line != NULL)
	{
		if (check_repeat(type) == 0 || type == ERROR)
			return (0);
		if (type == PLANE && check_plane(&line) == 0)
			return (0);
		else if (type == SPHERE && check_sphere(&line) == 0)
			return (0);
		else if (type == AMBIENT && check_ambient(&line) == 0)
			return (0);
		else if (type == POINT && check_light(&line) == 0)
			return (0);
		free(*head);
		line = get_next_line(fd);
		*head = line;
		type = ft_get_type(line);
	}
	free(*head);
	return (1);
}

int		test_syntax(int fd)
{
	char *line;
	char *head;
	t_type type;
	int	 	test;

	line = get_next_line(fd);
	head = line;
	type = ft_get_type(line);
	test = test_syntax2(line, &head, type, fd);
	if (test == 0)
		free(head);
	return (test);
}

int	main(void)
{
	int fd = open("scene.rt", O_RDONLY);
	printf("%d\n", test_syntax(fd));
	return (0);
}