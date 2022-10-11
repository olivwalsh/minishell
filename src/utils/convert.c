/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:43:49 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 14:34:00 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	countdigits(long n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	putnbr(long n, char *str, int size)
{
	if (n > 9)
		putnbr(n / 10, str, size - 1);
	*(str + size) = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l;
	int		size;

	size = 0;
	l = n;
	if (l < 0)
	{
		l *= -1;
		size += 1;
	}
	size += countdigits(l);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (err_msg_str(MALLOC_ERR));
	if (n < 0)
		str[0] = '-';
	putnbr(l, str, size - 1);
	str[size] = '\0';
	return (str);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		result;
	int		sign;

	sign = 1;
	result = 0;
	str = (char *)nptr;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
