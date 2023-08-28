/* //#include "../includes/minirt.h"

# include <stdio.h>

int	ft_isdigit(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	return (0);
}
 */

#include "test.h"

int is_space(char c)
{
    if (c == 32 || c <= 9)
        return (1);
    return (0);
}

float ft_atof(char **line)
{
    float n;
    float sig;
    int tmp;
    float frac;
    int flag;

    sig = 1;
    
    tmp = 0;
    frac = 0;
    flag = 0;
    while (**line != ',' && **line != 32 && **line != 9)
    {
        if (**line == '-')
            sig *= -1;
        if (**line == '-' || **line == '+')
        {
            (*line)++;
            if (**line == '-' || **line == '+')
                break ;
        }
        if (ft_isdigit(**line) && !flag)
            tmp = tmp * 10 + (**line - 48);
        if (ft_isdigit(**line) && flag)
            frac = frac * 10 + (**line - 48);
        if (**line == '.')
            flag = 1;
        (*line)++;
    }
    while (**line && (**line == 32 || **line == 9))
        (*line)++;
    if (*line && **line == ',')
        (*line)++;
    while (frac > 1)
        frac /= 10;
    n = (tmp + frac) * sig;
    return (n);
}

/* int main(void)
{
    //char *line = "50.5734644,0.0,20.32246";
    char *line = "50.5734644,2.578,20.32246";
    printf("%s\n", line);
    printf("%.10f\n", ft_atof(&line));
    printf("%s\n", line);
    printf("%.10f\n", ft_atof(&line));
    printf("%s\n", line);
    printf("%.10f\n", ft_atof(&line));
    printf("%s\n", line);
    
    return (0);
} */