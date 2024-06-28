/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:28:30 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/28 14:30:35 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trimspace(char const *s1)
{
	size_t	dstl;
	size_t	f;
	size_t	b;
	char	*trimmed;

	if ((!s1) || ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	dstl = ft_strlen(s1);
	f = 0;
	b = dstl;
	while (s1[f] && s1[f] == ' ')
		f++;
	while (b >= f && s1[f] == ' ')
		b--;
	trimmed = malloc((b - f + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[f], (b - f + 2));
	return (trimmed);
}
