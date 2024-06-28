/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:37:41 by tsurma            #+#    #+#             */
/*   Updated: 2024/03/14 18:07:16 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	char	*dst;

	l = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	dst = malloc(l * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, (char *)s1, l);
	ft_strlcat(dst, (char *)s2, l);
	return (dst);
}
