#include "../includes/minirt.h"

void    lst_add_back(t_vars *vars, t_type type, char *line)
{
    t_object *new;
    static t_object *end;
    
    new = parse_next(type, line);
    if (vars->begin == NULL)
        vars->begin = new;
    else
        end->next = new;
    end = new;
}

void    light_add_back(t_vars *vars, t_type type, char *line)
{
    t_object *new;
    static t_object *end;
    
    new = parse_next(type, line);
    if (vars->light == NULL)
        vars->light = new;
    else
        end->next = new;
    end = new;
}