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

int	valid_map(int *map, int width, int height)
{
	int	player_count;
	int	y;
	int	x;
	int	tile;

	player_count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			tile = map[y * width + x];
			if (tile == FLOOR || tile == WALL || tile == NOTHING)
			{
				x++;
				continue ;
			}
			else if (tile == N || tile == S || tile == E || tile == W)
			{
				player_count++;
				x++;
				continue ;
			}
			else
			{
				return (0);
			}
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

int	content_check(t_map *map, int player_x, int player_y)
{
	int	*copy;
	int	y;
	int	x;

	copy = matrix_dup(map->mapp, map->mapx, map->mapy);
	if (!copy)
		return (0);
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
				free(copy);
				return (0);
			}
			x++;
		}
		y++;
	}
	free(copy);
	return (1);
}

int	check_valid_map(t_map *map, int player_x, int player_y)
{
	if (!valid_map(map->mapp, map->mapx, map->mapy))
	{
		printf("Error: Map has invalid chars or mult/no player start pos\n");
		return (0);
	}
	if (!content_check(map, player_x, player_y))
	{
		printf("Error: Map is not enclosed fully/contains unreachable areas\n");
		return (0);
	}
	return (1);
}
