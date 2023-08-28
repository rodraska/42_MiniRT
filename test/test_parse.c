#include "test.h"

void    parse_camera(char *line)
{
    t_vector coord;
    t_vector orientation;
    float fov;

    coord.x = ft_atof(&line);
    coord.y = ft_atof(&line);
    coord.z = ft_atof(&line);

    printf("%f\n", coord.x);
    printf("%f\n", coord.y);
    printf("%f\n", coord.z);

    orientation.x = ft_atof(&line);
    orientation.y = ft_atof(&line);
    orientation.z = ft_atof(&line);

    printf("%f\n", orientation.x);
    printf("%f\n", orientation.y);
    printf("%f\n", orientation.z);

    fov = ft_atof(&line);

    printf("%f\n", fov);

}

void    parse_point(char *line)
{
    t_vector coord;
    float   ratio;
    t_color color;

    coord.x = ft_atof(&line);
    coord.y = ft_atof(&line);
    coord.z = ft_atof(&line);

    printf("%f\n", coord.x);
    printf("%f\n", coord.y);
    printf("%f\n", coord.z);

    ratio = ft_atof(&line);

    printf("%f\n", ratio);

    color.r = (int)ft_atof(&line);
    color.g = (int)ft_atof(&line);
    color.b = (int)ft_atof(&line);

    printf("%d\n", color.r);
    printf("%d\n", color.g);
    printf("%d\n", color.b);
}

void    parse_ambient(char *line)
{
    float i;
    t_color color;

    i = ft_atof(&line);

    printf("%f\n", i);

    color.r = (int)ft_atof(&line);
    color.g = (int)ft_atof(&line);
    color.b = (int)ft_atof(&line);

    printf("%d\n", color.r);
    printf("%d\n", color.g);
    printf("%d\n", color.b);
}

void    parse_cylinder(char *line)
{
    //printf("%s", line);
    t_vector coord;
    t_vector axis;
    float diameter;
    float height;
    t_color color;

    coord.x = ft_atof(&line);
    coord.y = ft_atof(&line);
    coord.z = ft_atof(&line);

    printf("%f\n", coord.x);
    printf("%f\n", coord.y);
    printf("%f\n", coord.z);

    axis.x = ft_atof(&line);
    axis.y = ft_atof(&line);
    axis.z = ft_atof(&line);

    printf("%f\n", axis.x);
    printf("%f\n", axis.y);
    printf("%f\n", axis.z);

    diameter = ft_atof(&line);

    printf("%f\n", diameter);

    height = ft_atof(&line);

    printf("%f\n", height);

    color.r = (int)ft_atof(&line);
    color.g = (int)ft_atof(&line);
    color.b = (int)ft_atof(&line);

    printf("%d\n", color.r);
    printf("%d\n", color.g);
    printf("%d\n", color.b);
}

void    parse_sphere(char *line)
{
    t_vector coord;
    float   diameter;
    t_color color;

    coord.x = ft_atof(&line);
    coord.y = ft_atof(&line);
    coord.z = ft_atof(&line);

    printf("%f\n", coord.x);
    printf("%f\n", coord.y);
    printf("%f\n", coord.z);

    diameter = ft_atof(&line);

    printf("%f\n", diameter);

    color.r = (int)ft_atof(&line);
    color.g = (int)ft_atof(&line);
    color.b = (int)ft_atof(&line);

    printf("%d\n", color.r);
    printf("%d\n", color.g);
    printf("%d\n", color.b);
}

void    parse_plane(char *line)
{
    t_vector coord;
    t_vector normal;
    t_color color;

    coord.x = ft_atof(&line);
    coord.y = ft_atof(&line);
    coord.z = ft_atof(&line);

    printf("%f\n", coord.x);
    printf("%f\n", coord.y);
    printf("%f\n", coord.z);

    normal.x = ft_atof(&line);
    normal.y = ft_atof(&line);
    normal.z = ft_atof(&line);

    printf("%f\n", normal.x);
    printf("%f\n", normal.y);
    printf("%f\n", normal.z);

    color.r = (int)ft_atof(&line);
    color.g = (int)ft_atof(&line);
    color.b = (int)ft_atof(&line);

    printf("%d\n", color.r);
    printf("%d\n", color.g);
    printf("%d\n", color.b);
    
}

void    parse_next(t_type type, char *line)
{
    if (type == PLANE)
        parse_plane(line);
    if (type == SPHERE)
        parse_sphere(line);
    if (type == CYLINDER)
        parse_cylinder(line);
    if (type == AMBIENT)
        parse_ambient(line);
    if (type == POINT)
        parse_point(line);
}

t_type ft_get_type(char *line)
{
	if (line && line)
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

t_type ft_check_line(char **line)
{
	int 	i;
	t_type type;

	i = 0;
	type = ft_get_type(*line);
	if (type >= 0 && type <= 2)
		i++;
	while (*line && (*line)[++i])
	{
		if (!(*line)[i] && !ft_isdigit((*line)[i]) && (*line)[i] != '.' && (*line)[i] != ',')
			return ERROR;
	}
    i = 0;
    while ((*line)[i] && !ft_isdigit((*line)[i]) && (*line)[i] != '+' && (*line)[i] != '-')
        i++;
    (*line) += i;
	return type;
}

int main(void)
{
    int fd;
    char *line;
    t_type type;

    fd = open("scene.rt", O_RDONLY);

    line = get_next_line(fd);
    while (line != NULL)
    {
        type = ft_check_line(&line);
        parse_next(type, line);
        //printf("%d\n", type);
        line = get_next_line(fd);
    }
}