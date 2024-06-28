/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:04:04 by tsurma            #+#    #+#             */
/*   Updated: 2024/01/26 20:11:31 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_p(char s);
static int	ft_putstr_p(char *s);
static int	ft_puthex(unsigned long int nbr, char d, int b);
static int	ft_putnbr_u(long long int n);

int	ft_crossroads(va_list args, char d, int output)
{
	if (d == 'c')
		output = output + ft_putchar_p(va_arg(args, int));
	else if (d == 's')
		output = output + ft_putstr_p(va_arg(args, char *));
	else if (d == 'i' || d == 'd')
		output = output + ft_putnbr_u(va_arg(args, int));
	else if (d == 'u')
		output = output + ft_putnbr_u(va_arg(args, unsigned int));
	else if (d == 'x' || d == 'X')
		output = output + ft_puthex(va_arg(args, unsigned int), d, 0);
	else if (d == 'p')
		output = output + ft_puthex(va_arg(args, unsigned long int), d, 0);
	else if (d == '%')
		output = output + ft_putchar_p('%');
	return (output);
}

static int	ft_putchar_p(char s)
{
	write(1, &s, 1);
	return (1);
}

static int	ft_putstr_p(char *s)
{
	int	l;

	l = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	l = ft_strlen(s);
	write(1, s, l);
	return (l);
}

static int	ft_puthex(unsigned long int nbr, char d, int b)
{
	int					l;
	unsigned long int	t;
	char				*base;

	l = 0;
	if (d == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (d == 'p' && b == 0)
	{
		if (nbr == 0)
			return (ft_putstr_p("(nil)"));
		else
			l += ft_putstr_p("0x");
	}
	t = nbr / 16;
	if (t >= 16)
		l += ft_puthex(t, d, 1);
	else if (t != 0)
		l += ft_putchar_p(base[t]);
	l += ft_putchar_p(base[nbr % 16]);
	return (l);
}

static int	ft_putnbr_u(long long int n)
{
	int	l;

	l = 0;
	if (n < 0)
	{
		l += ft_putchar_p('-');
		n = -n;
	}
	if (n > 9)
	{
		l += ft_putnbr_u(n / 10);
		l += ft_putnbr_u(n % 10);
	}
	else
		l += ft_putchar_p(n + '0');
	return (l);
}
