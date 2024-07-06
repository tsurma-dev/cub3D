/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olobresh <olobresh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:18:52 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/01 17:18:54 by olobresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
void check_ext(const char *filename)
{
    const char *extension;

    extension = ft_strrchr(filename, '.');
    if (!extension || ft_strcmp(extension, ".cub") != 0)
    {
        printf("Error: Map file must have a .cub extension\n");
        exit(EXIT_FAILURE);
    }
}


