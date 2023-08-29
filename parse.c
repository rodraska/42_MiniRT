#include "includes/minirt.h"

t_object    *parse_next(t_type type, char *line)
{
    if (type == PLANE)
        return (parse_plane(line));
    if (type == SPHERE)
        return (parse_sphere(line));
    /* if (type == CYLINDER)
        return (parse_cylinder(line)); */
    if (type == AMBIENT)
        return (parse_ambient(line));
    if (type == POINT)
        return (parse_point(line));
	else
		return (parse_plane(line));
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

void ft_check_line(t_vars *vars, char *line)
{
	int 	i;
	t_type type;

	i = 0;
	type = ft_get_type(line);
	if (type >= 0 && type <= 2)
		i++;
	while (line && line[++i])
	{
		if (!line[i] && !ft_isdigit(line[i]) && line[i] != '.' && line[i] != ',')
			return ;
	}
    i = 0;
    while (line[i] && !ft_isdigit(line[i]) && line[i] != '+' && line[i] != '-')
        i++;
	if (type != AMBIENT && type != POINT && type != DIRECTIONAL)
		lst_add_back(vars, type, (line + i)) ;
	else
		light_add_back(vars, type, (line + i));
}

int	map_loading(t_vars *vars, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);	
	ft_check_line(vars, line);
	free(line);
	return (1);
}

int	strcmp_rt(char *a, char *extension)
{
	int		size;
	int		j;

	j = -1;
	size = ft_strlen(a) - (ft_strlen(extension) + 1);
	if (size < 0)
		return 0;
	while (a[++size])
	{
		if (a[size] != extension[++j])
			return (0);
	}
	return (1);
}

/* Check if the file is empty */
int	check_empty(t_vars *vars, char *line)
{
	if (line == NULL)
	{
		write (1, "Empty file. Try again please.\n", 31);
		ft_close (vars);
	}
}

/* Verifica todas as possibilidades para que o mapa pode falhar */
int	check_map(t_vars *vars)
{
	int	fd;
	int i;

	i = 0;
	if (!strcmp_rt(vars->map_file, "rt"))
	{
		write(1, "That file is not a .rt file\n", 29);
		ft_close(vars);
	}
	else
	{
		fd = open(vars->map_file, O_RDONLY);
		printf("fd1: %d\n", fd);
		if (fd == -1)
		{
			write(1, "That file is not in the repository.\n", 37);
			ft_close (vars);
		}
		//check_empty(vars, get_next_line(fd));
		return (fd);
	}
	return (0);
}

int		check_float(char **line)
{
	int	i;

	i = 0;
	if (!ft_isdigit(*line) && *line != '+' && *line != '-')
		return (0);
	while (*line != ',')
	{
		if (!ft_isdigit(*line) && *line != '.')
			return (0);
		(*line)++;
	}
	return (1);
}

void	check_syntax(t_vars *vars)
{
	int fd;
	char *line;
	t_type type;

	fd = open(vars->map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		type = ft_get_type(line);
		check_syntax2(type);
		line = get_next_line(fd);
		
	}
}

int	main(void)
{
	char *line = "4.67,3.87,9.0";
	printf("%d\n", check_float(&line));
	return (0);
}
