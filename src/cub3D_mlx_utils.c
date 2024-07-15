/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_mlx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:05 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/15 14:23:19 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	fill_background(t_map *map)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (y < map->bg->height / 2)
	{
		x = 0;
		while (x < map->bg->width)
		{
			mlx_put_pixel(map->bg, x, y, map->colour_c);
			x++;
		}
		y++;
	}
	while (y < map->bg->height)
	{
		x = 0;
		while (x < map->bg->width)
		{
			mlx_put_pixel(map->bg, x, y, map->colour_f);
			x++;
		}
		y++;
	}
}

void	window(t_map *map)
{
	map->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!map->mlx)
		exit(EXIT_FAILURE);
}
