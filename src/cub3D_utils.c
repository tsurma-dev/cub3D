/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:53:53 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/08 11:20:19 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**ft_pointjoin(char **dest, char *src)
{
	char	**ret;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	if (dest != NULL)
	{
		while (dest[i] != NULL)
			++i;
	}
	ret = ft_calloc(sizeof(char *), i + 2);
	if (!ret)
		return (NULL);
	ret[i] = src;
	while (i > 0)
	{
		i--;
		ret[i] = dest[i];
	}
	free(dest);
	return (ret);
}
