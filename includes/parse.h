#ifndef PARSE_H
# define PARSE_H

typedef struct s_hash   t_hash;

struct s_hash {
    int key;
    void (*ft_ptr)();
};

#endif