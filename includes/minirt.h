/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/08/29 18:21:05 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "color.h"
# include "raytracer.h"
# include "get_next_line.h"
# include "parse.h"

# define WHITE 0xFFFFFF
# define HEIGHT 1000.0f
# define WIDTH 1000.0f
# define HEIGHT_2 500.0f
# define WIDTH_2 500.0f

typedef struct  s_data	 t_data;
typedef struct	s_vars	 t_vars;
typedef struct 	s_object t_object;
typedef struct 	s_plane  t_plane;
typedef struct 	s_sphere t_sphere;
typedef enum 	e_type t_type;
typedef struct 	s_light t_light;
typedef struct	s_obj_list t_obj_list;

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

struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	 img;
	t_object *begin;
	t_light  *light;
	t_object *select;
	char 	 *map_file;
};

struct 	s_object {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
};

struct 	s_light {
	t_object	*next;
	t_vector position;
	t_type type;
	t_color	color;
	int specular;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	//
	float  intensity;
};

struct 	s_plane {
	t_object	*next;
	t_vector direction;
	t_type type;
	t_color	color;
	int specular;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	t_vector vector;
};

struct 	s_sphere {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	//
	float diameter;
};



//Hook's
int			ft_key(int keycode, t_vars *vars);
int 		ft_mouse_scroll(int button, int x, int y, t_vars *vars);
int 		ft_mouse_up(int button, int x, int y, t_vars *vars);
int 		ft_mouse_down(int button, int x, int y, t_vars *vars);
int			ft_close(t_vars *vars);

//Draw
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void* 		new_object(int size);
t_object*	new_plane(t_vector coord, t_vector v, t_color color, int specular);
t_object* 	new_sphere(t_vector coord, float diameter, t_color color, int specular);
t_object	*parse_sphere(char *line);
t_object    *parse_plane(char *line);
t_object	*parse_point(char *line);
t_object	*parse_ambient(char *line);

void 		raytracer(t_vars *vars);
void 		canvas_to_viewport(t_raytracer *rt, float x, float y);
t_object 	*trace_ray(t_vars* vars ,t_raytracer* rt, float t_min, float t_max);

//Light
t_light 	*new_light(float intensity, t_vector pos, t_type type);
float 		compute_light(t_vars *vars, t_light *this, t_raylight *rl);

//Parse
t_object	*parse_next(t_type type, char *line);
int		map_loading(t_vars *vars, int fd);
int		strcmp_rt(char *a, char *extension);
int		check_map(t_vars *vars);
void	check_syntax(t_vars *vars);
int		test_syntax(char *str);

//Aux
void	*ft_calloc(size_t nelem, size_t elsize);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int i);
char	*ft_strchr(const char *s, int c);
double  ft_atof(char **line, double sig, double tmp, double frac);
int ft_isspace(char c);

void    lst_add_back(t_vars *vars, t_type type, char *line);
void    light_add_back(t_vars *vars, t_type type, char *line);

#endif