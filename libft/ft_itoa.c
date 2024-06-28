/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:00 by tsurma            #+#    #+#             */
/*   Updated: 2023/11/22 15:37:25 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_length(unsigned int nbr)
{
	int	digits;

	digits = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		digits++;
	}
	return (digits);
}

static char	*write_nbr(char *array, int digits, int m, unsigned long t)
{
	while ((digits + m) > 0 + m)
	{
		digits--;
		array[digits + m] = t % 10 + '0';
		t /= 10;
	}
	return (array);
}

char	*ft_itoa(int n)
{
	signed long	t;
	int			m;
	int			digits;
	char		*array;

	m = 0;
	t = n;
	if (t < 0)
	{
		t = -t;
		m = 1;
	}
	digits = nbr_length(t);
	if (n == 0)
		digits++;
	array = ft_calloc((digits + 1 + m), sizeof(char));
	if (!array)
		return (NULL);
	write_nbr(array, digits, m, t);
	if (m == 1)
		array[0] = '-';
	return (array);
}

/*Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.*/
