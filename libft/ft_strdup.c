/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:43 by tsurma            #+#    #+#             */
/*   Updated: 2024/02/19 16:09:06 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	sl;
	char	*dest;

	sl = 0;
	sl = ft_strlen(s) + 1;
	dest = ft_calloc(sizeof(char), sl);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, sl);
	return (dest);
}
