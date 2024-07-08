/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:18:52 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/08 12:02:53 by tsurma           ###   ########.fr       */
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

void	check_ext(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".cub") != 0)
	{
		printf("Error: Map file must have a .cub extension\n");
		exit(EXIT_FAILURE);
	}
}

void	initiate_cub3dmap(t_map *map)
{
	map->mlx = NULL;
	map->no_i = NULL;
	map->so_i = NULL;
	map->we_i = NULL;
	map->ea_i = NULL;
	map->no_t = NULL;
	map->so_t = NULL;
	map->we_t = NULL;
	map->ea_t = NULL;
	map->bg = NULL;
	map->p_layer = NULL;
	map->test = NULL;
	map->px = 0;
	map->py = 0;
	map->pa = 0;
	map->pdx = 0;
	map->pdy = 0;
	map->plane_x = 0;
	map->plane_y = 0;
	map->mapx = 0;
	map->mapy = 0;
	map->mapp = NULL;
	map->colour_c = -1;
	map->colour_f = -1;
}

int	find_player_position(t_map *map, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->mapy)
	{
		x = 0;
		while (x < map->mapx)
		{
			if (map->mapp[y * map->mapx + x] == N || map->mapp[y * map->mapx + x] == S ||
				map->mapp[y * map->mapx + x] == E || map->mapp[y * map->mapx + x] == W)
			{
				*player_x = x;
				*player_y = y;

				if (map->mapp[y * map->mapx + x] == N)
					map->pa = 3 * PI / 2;
				else if (map->mapp[y * map->mapx + x] == S)
					map->pa = PI / 2;
				else if (map->mapp[y * map->mapx + x] == E)
					map->pa = 0;
				else if (map->mapp[y * map->mapx + x] == W)
					map->pa = PI;

				map->px = x * TEXTURE_SIZE + TEXTURE_SIZE / 2;
				map->py = y * TEXTURE_SIZE + TEXTURE_SIZE / 2;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	flood_fill(int x, int y, int *tiles, t_map *map)
{
	if (x < 0 || y < 0 || y >= map->mapy || x >= map->mapx
		|| tiles[y * map->mapx + x] == WALL || tiles[y * map->mapx + x] == -2)
		return ;

	tiles[y * map->mapx + x] = -2;

	flood_fill(x + 1, y, tiles, map);
	flood_fill(x - 1, y, tiles, map);
	flood_fill(x, y + 1, tiles, map);
	flood_fill(x, y - 1, tiles, map);
}
