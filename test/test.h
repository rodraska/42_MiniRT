#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>

typedef enum 	e_type t_type;
typedef struct  s_vector 	 t_vector;
typedef struct 	s_color t_color;

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	ERROR,
	EMPTY_LINE
};

struct s_vector
{
	float x;
	float y;
	float z;
};

struct  s_color {
	int r;
	int g;
	int b;
};

char	*get_next_line(int fd);
static char	*ft_strjoin(char *s1, char *s2);
static size_t	ft_strlen_nl(const char *str);
int	ft_isdigit(int i);
float ft_atof(char **line);
int is_space(char c);

#endif