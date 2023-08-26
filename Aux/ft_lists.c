#include "../includes/minirt.h"

t_object *lstlast(t_object *lst)
{
    t_object *last;

    last = lst;
    while (lst != NULL)
    {
        last = lst;
        lst = lst->next;
    }
    return (last);
}

void    lst_add_back(t_object **lst, t_type type)
{
    t_object *new;
    t_object *last;

    new = lstnew(type);
    if (*lst)
    {
        last = lstlast(*lst);
        last->next = new;
    }
    else
        *lst = new;
}

t_object    *lstnew(t_type type)
{
    t_object *object;

    if (type == PLANE)
        object = new_plane();
    else if (type == SPHERE)
        object = new_sphere();
    object->next = NULL;
    return (object);
}

/* t_object    *lstnew(t_type type)
{
    t_object *object;
    int i;

    t_hash hashmap[] = {
        {0, new_plane},
        {1, new_sphere}
    };

    i = -1;
    while (++i < 2)
    {
        if (hashmap[i].key == type)
        {
            object = hashmap[i].function();
            break ;
        }
    }
    object->next = NULL;
    return (object);
} */