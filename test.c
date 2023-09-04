#include <stdio.h>

void    raytracer_threads(int i)
{
	int			x;
	int			y;
    int         buf[1000];

    x = 0;
	while (x < 1000)
	{
        buf[x] = x;
        printf("x: %d\n", x);
        printf("buf: %d\n", buf[x]);
		x++;
	}
}

int main(void)
{
    raytracer_threads(0);
    return (0);
}