#include "includes/minirt.h"

static int	check_camera(char **line, int *f)
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

static int	check_repeat(t_type type)
{
	static int l;
	static int a;
	static int c;

	if (type == AMBIENT && a == 0)
		a = 1;
	else if (type == AMBIENT && a == 1)
		return (0);
	else if (type == POINT && l == 0)
		l = 1;
	else if (type == POINT && l == 1)
		return (0);
	else if (type == CAMERA && l == 0)
		c = 1;
	else if (type == CAMERA && c == 1)
		return (0);
	return (1);
}

static void	test_syntax_helper(char **line, char **head, t_type *type, int fd)
{
	free(*head);
	*line = get_next_line(fd);
	*head = *line;
	*type = ft_get_type(*line);
}

static int	test_syntax2(char *line, char **head, t_type type, int fd)
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