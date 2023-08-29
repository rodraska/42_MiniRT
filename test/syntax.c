#include "test.h"

int		check_float(char **line)
{
	int	i;

	i = 0;
	if (!ft_isdigit(**line) && **line != '+' && **line != '-')
		return (0);
    (*line)++;
	while (**line && **line != ',')
	{
		if (!ft_isdigit(**line) && **line != '.')
			return (0);
		(*line)++;
	}
	return (1);
}

int	main(void)
{
	char *line = "+4.67,3.87,-9.0";
    printf("%s\n", line);
	printf("%d\n", check_float(&line));
    line++;
    printf("%s\n", line);
    printf("%d\n", check_float(&line));
    line++;
    printf("%s\n", line);
    printf("%d\n", check_float(&line));
	return (0);
}