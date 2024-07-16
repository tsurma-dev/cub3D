/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:55:34 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/15 14:07:49 by tsurma           ###   ########.fr       */
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
	if (!content_check(map, player_x, player_y))
	{
		printf("Error\nMap contains unreachable areas\n");
		return (0);
	}
	return (1);
}

void	flood_fill(int x, int y, int *tiles, t_map *map)
{
	if (x < 0 || y < 0 || y >= map->mapy || x >= map->mapx || tiles[y
			* map->mapx + x] == WALL || tiles[y * map->mapx + x] == -2)
		return ;
	tiles[y * map->mapx + x] = -2;
	flood_fill(x + 1, y, tiles, map);
	flood_fill(x - 1, y, tiles, map);
	flood_fill(x, y + 1, tiles, map);
	flood_fill(x, y - 1, tiles, map);
}

int	process_rgb_component(char *line, int *i)
{
	int	value;

	if (ft_isdigit(line[*i]) == FALSE)
		return (UNEX_CHAR);
	value = ft_atoi(&line[*i]);
	if (value > 255 || value < 0)
		return (RGB_OOR);
	while (ft_isdigit(line[*i]) == TRUE)
		++(*i);
	if (line[*i] == ',')
		++(*i);
	return (value);
}

int	rgb_extractor(char *line)
{
	int	i;
	int	rgb;
	int	component;
	int	c;

	if (!line)
		return (-1);
	i = 0;
	rgb = 0;
	c = 3;
	while (line[i] && line[i] == ' ')
		++i;
	if (line[i] == 'C' || line[i] == 'F')
		i++;
	while (line[i] && line[i] == ' ')
		++i;
	while (--c >= 0)
	{
		component = process_rgb_component(line, &i);
		if (component < 0)
			return (component);
		rgb = (rgb << 8) + component;
	}
	rgb = (rgb << 8) + 0xff;
	return (rgb);
}

int	valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}
