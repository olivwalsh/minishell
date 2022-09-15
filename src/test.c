#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void	ft_minus(int *str, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		str[i] = -2;
		i++;
	}
	str[n] = -1;
}

int	ft_tabint(int *table, int c)
{
	int		i;

	i = 0;
	while (table && table[i] && table[i] != -2)
	{
		if (table[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	main()
{
	int		*stop;
	char	*value;

	value = "hello";
	stop = malloc(sizeof(int) * (strlen(value) + 1));
	if (!stop)
		return (EXIT_FAILURE);
	memset(stop, 0, sizeof(int));
	ft_minus(stop, strlen(value));
	printf("return is %d\n", ft_tabint(stop, -1));
	return (0);
}