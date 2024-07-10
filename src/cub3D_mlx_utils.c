/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_mlx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:05 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/10 15:40:21 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	fill_test(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 2)
	{
		x = -1;
		while (++x < 2)
		{
			mlx_put_pixel(map->test, x, y, 0x0000ff);
		}
	}
}

// void	fill_wall(t_map *map)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (++y < 63)
// 	{
// 		x = -1;
// 		while (++x < 63)
// 		{
// 			mlx_put_pixel(map->no_i, x, y, 0xffffff);
// 		}
// 	}
// }

void	fill_background(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(map->bg, x, y, map->colour_c);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(map->bg, x, y, map->colour_f);
			x++;
		}
		y++;
	}
}

// void	draw_map(t_map *map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	x = 0;
// 	while (y < map->mapy)
// 	{
// 		x = 0;
// 		while (x < map->mapx)
// 		{
// 			if (map->mapp[y * map->mapx + x] == 1)
// 			{
// 				mlx_image_to_window(map->mlx, map->no_i,
// 					x * TEXTURE_SIZE, y * TEXTURE_SIZE);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	window(t_map *map)
{
	map->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!map->mlx)
		exit(EXIT_FAILURE);
}
