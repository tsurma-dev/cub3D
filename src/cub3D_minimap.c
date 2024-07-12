/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:44:19 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/12 13:54:56 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	draw_map(t_map *map)
{
	int	y;
	int	x;
	int	cube;


	if (SCREEN_HEIGHT / map->mapy < SCREEN_WIDTH * 0.666 / map->mapx)
		cube = SCREEN_HEIGHT / map->mapy;
	else
		cube = SCREEN_WIDTH * 0.666 / map->mapx;
	mlx_resize_image(map->wall, cube, cube);

	y = -1;
	while (++y < map->mapy)
	{
		x = -1;
		while (++x < map->mapx)
			if (map->mapp[y * map->mapx + x] == 1)
				mlx_image_to_window(map->mlx, map->wall, x * cube, y * cube);
	}
}
