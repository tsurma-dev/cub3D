/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:34:38 by tsurma            #+#    #+#             */
/*   Updated: 2024/01/26 20:11:27 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		output;

	i = 0;
	output = 0;
	va_start(args, input);
	if (!input)
		return (-1);
	while (input[i])
	{
		if (input[i] == '%')
		{
			output = ft_crossroads(args, input[++i], output);
			++i;
		}
		else
		{
			write(1, &input[i], 1);
			++i;
			++output;
		}
	}
	return (output);
}
