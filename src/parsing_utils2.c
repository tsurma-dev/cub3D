/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olobresh <olobresh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:44:59 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/08 12:45:02 by olobresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_valid_tile(int tile, int *player_count)
{
	if (tile == FLOOR || tile == WALL || tile == NOTHING)
	{
		return (1);
	}
	else if (tile == N || tile == S || tile == E || tile == W)
	{
		(*player_count)++;
		return (1);
	}
	return (0);
}

int	valid_map(int *map, int width, int height)
{
	int	player_count;
	int	y;
	int	x;

	player_count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (!is_valid_tile(map[y * width + x], &player_count))
			{
				return (0);
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

int	*matrix_dup(int *map, int width, int height)
{
	int	*dup;
	int	i;

	dup = malloc(width * height * sizeof(int));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < width * height)
	{
		dup[i] = map[i];
		i++;
	}
	return (dup);
}

int	validate_map_copy(int *copy, t_map *map, int player_x, int player_y)
{
	int	y;
	int	x;

	flood_fill(player_x, player_y, copy, map);
	y = 0;
	while (y < map->mapy)
	{
		x = 0;
		while (x < map->mapx)
		{
			if (map->mapp[y * map->mapx + x] == FLOOR && copy[y * map->mapx
					+ x] != -2)
			{
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	content_check(t_map *map, int player_x, int player_y)
{
	int	*copy;
	int	result;

	copy = matrix_dup(map->mapp, map->mapx, map->mapy);
	if (!copy)
		return (0);
	result = validate_map_copy(copy, map, player_x, player_y);
	free(copy);
	return (result);
}
