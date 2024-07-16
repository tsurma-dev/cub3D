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

int check_player_surroundings(t_map *map, int player_x, int player_y)
{
    int free_space;

	free_space = 0;
    if (player_y > 0 && map->mapp[(player_y - 1) * map->mapx + player_x] == FLOOR)
        free_space = 1;
    if (player_y < map->mapy - 1 && map->mapp[(player_y + 1) * map->mapx + player_x] == FLOOR)
        free_space = 1;
    if (player_x > 0 && map->mapp[player_y * map->mapx + (player_x - 1)] == FLOOR)
        free_space = 1;
    if (player_x < map->mapx - 1 && map->mapp[player_y * map->mapx + (player_x + 1)] == FLOOR)
        free_space = 1;
    if (!free_space)
	{
        printf("Error\nPlayer is surrounded by walls.\n");
        return (0);
    }
    return (1);
}
