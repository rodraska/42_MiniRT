//#include "../includes/minirt.h"

# include <stdio.h>

int	ft_isdigit(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	return (0);
}

float ft_atof(char *line)
{
    float n;
    float sig;
    int tmp;
    float frac;
    int flag;

    sig = 1;
    
    tmp = 0;
    frac = 0;
    while (*line != ',')
    {
        if (*line == '-')
            sig *= -1;
        if (*line == '-' || *line == '+')
        {
            line++;
            if (*line == '-' || *line == '+')
                break ;
        }
        if (ft_isdigit(*line) && !flag)
            tmp = tmp * 10 + (*line - 48);
        if (ft_isdigit(*line) && flag)
            frac = frac * 10 + (*line - 48);
        if (*line == '.')
            flag = 1;
        line++;
    }
    while (frac > 1)
        frac /= 10;
    n = tmp + frac;
    return (n);
}

int main(void)
{
    printf("%.10f\n", ft_atof("50.5734644,0.0,20.32246"));
    printf("%.10f\n", 50.5734644);
    
    return (0);
}