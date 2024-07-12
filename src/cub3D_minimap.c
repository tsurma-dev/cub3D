/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:44:19 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/12 17:23:00 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	draw_map(t_map *map)
{
	int	y;
	int	x;


	if (SCREEN_HEIGHT / map->mapy < SCREEN_WIDTH * 0.8 / map->mapx)
		map->cube = SCREEN_HEIGHT / map->mapy;
	else
		map->cube = SCREEN_WIDTH * 0.8 / map->mapx;
	mlx_resize_image(map->wall, map->cube, map->cube);

	map->minx = SCREEN_WIDTH / 2 - (map->cube * map->mapx / 2);
	map->miny = SCREEN_HEIGHT / 2 - (map->cube * map->mapy / 2) - (SCREEN_HEIGHT * 0.1);
	y = -1;
	while (++y < map->mapy)
	{
		x = -1;
		while (++x < map->mapx)
			if (map->mapp[y * map->mapx + x] == 1)
				mlx_image_to_window(map->mlx, map->wall, map->minx + (x * map->cube), map->miny + (y * map->cube));
	}
	draw_player(map);
}

void	draw_player(t_map *map)
{
	static int	prev_x;
	static int	prev_y;

	if (prev_x == 0)
		prev_x = 10;
	if (prev_y == 0)
		prev_y = 10;

	mlx_put_pixel(map->m_layer, prev_x, prev_y, 0);
	mlx_put_pixel(map->m_layer, prev_x - 1, prev_y, 0);
	mlx_put_pixel(map->m_layer, prev_x, prev_y - 1, 0);
	mlx_put_pixel(map->m_layer, prev_x + 1, prev_y, 0);
	prev_x = map->px * map->cube + map->minx;
	prev_y = map->py * map->cube + map->miny;
	// ((int *)map->m_layer)[prev_y * map->mapx + prev_x] = 255;
	mlx_put_pixel(map->m_layer, prev_x, prev_y, 0xffffff);
	mlx_put_pixel(map->m_layer, prev_x - 1, prev_y, 0xffffff);
	mlx_put_pixel(map->m_layer, prev_x, prev_y - 1, 0xffffff);
	mlx_put_pixel(map->m_layer, prev_x + 1, prev_y, 0xffffff);
}
