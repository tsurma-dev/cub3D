/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:55:34 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/17 14:13:13 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_valid_map(t_map *map, int player_x, int player_y)
{
	if (!valid_map(map->mapp, map->mapx, map->mapy))
	{
		printf("Error\nMap has invalid chars or mult/no player start pos\n");
		return (0);
	}
	if (!check_player_surroundings(map, player_x, player_y))
	{
		printf("Error\nMap contains unreachable areas\n");
		return (0);
	}
	return (1);
}

int	process_rgb_component(char *line, int *i, int *value)
{
	*value = 0;
	if (ft_isdigit(line[*i]) == FALSE)
		return (UNEX_CHAR);
	*value = ft_atoi(&line[*i]);
	if (*value > 255 || *value < 0)
		return (-RGB_OOR);
	while (ft_isdigit(line[*i]) == TRUE)
		++(*i);
	if (line[*i] == ',')
		++(*i);
	return (EXIT_SUCCESS);
}

int	rgb_extractor(char *line, int *rgb)
{
	int	i;
	int	component;
	int	c;

	if (!line)
		return (-1);
	i = 0;
	*rgb = 0;
	c = 3;
	while (line[i] && line[i] == ' ')
		++i;
	if (line[i] == 'C' || line[i] == 'F')
		i++;
	while (line[i] && line[i] == ' ')
		++i;
	while (--c >= 0)
	{
		if (process_rgb_component(line, &i, &component) != 0)
			return (EXIT_FAILURE);
		*rgb = (*rgb << 8) + component;
	}
	*rgb = (*rgb << 8) + 0xff;
	return (EXIT_SUCCESS);
}

int	valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}
