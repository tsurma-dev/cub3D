/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:17:55 by tsurma            #+#    #+#             */
/*   Updated: 2023/11/22 13:15:22 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	dstl;
	size_t	f;
	size_t	b;
	char	*trimmed;

	if ((!s1 || !set) || (ft_strlen(set) == 0 || ft_strlen(s1) == 0))
		return (ft_strdup(s1));
	dstl = ft_strlen(s1);
	f = 0;
	b = dstl;
	while (s1[f] && ft_strchr(set, s1[f]) != 0)
		f++;
	while (b >= f && ft_strchr(set, s1[b]) != 0)
		b--;
	trimmed = malloc((b - f + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[f], (b - f + 2));
	return (trimmed);
}

/*Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.*/
