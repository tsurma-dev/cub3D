/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/02 07:19:16 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(void)
{
	static t_map	map;
	int mapp[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,};

	map.mapx = 8;
	map.mapy = 8;
	map.px = 500;
	map.py = 500;
	map.pa = PI;
	window(&map);
	map.mapp = mapp;
	map.bg = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map.test = mlx_new_image(map.mlx, 2, 2);
	map.no_i = mlx_new_image(map.mlx, 64, 64);
	fill_background(&map);
	fill_test(&map);
	fill_wall(&map);
	mlx_image_to_window(map.mlx, map.bg, 0, 0);
	draw_map(&map);
	mlx_image_to_window(map.mlx, map.test, 500, 500);
	mlx_key_hook(map.mlx, &keyhook, (void *)&map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}

void	raycaster(t_map *map)
{
	int		r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, atan;

	dof = 0;
	ra = map->pa;
	r = 0;
	while (r < 1)
	{
		if (ra == 0)
			atan = -1;
		else
			atan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)map->py >> 6) << 6) - 0.001;
			rx = (map->py - ry) * atan + map->px;
			yo = -64;
			xo = -yo * atan;
		}
		if (ra < PI)
		{
			ry = (((int)(map->py) >> 6) << 6) + 64;
			rx = (map->py - ry) * atan + map->px;
			yo = 64;
			xo = -yo * atan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = map->px;
			ry = map->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map->mapx + mx;
			if (mp >= 0 && mp < (map->mapx * map->mapy) && map->mapp[mp] == 1)
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				++dof;
			}
		}
		r++;
	}
	draw_line(map, map->px, map->py, rx, ry);
}

void	draw_map(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
		{

			if (map->mapp[y * 8 + x] == 1)
			{
				mlx_image_to_window(map->mlx, map->no_i, x * 64, y * 64);
			}
		}
	}
}


void	keyhook(mlx_key_data_t keydata, void *ma)
{
	t_map	*map;

	(void)keydata;
	map = (t_map *)ma;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->px += map->pdx * MOVE_SPEED;
		map->py += map->pdy * MOVE_SPEED;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->px -= map->pdx * MOVE_SPEED;
		map->py -= map->pdy * MOVE_SPEED;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->pa -= TURN_SPEED;
		if (map->pa < 0)
			map->pa += 2 * PI;
		map->pdx = cos(map->pa) * 5;
		map->pdy = sin(map->pa) * 5;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->pa += TURN_SPEED;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
		map->pdx = cos(map->pa) * 5;
		map->pdy = sin(map->pa) * 5;
	}
	if (map->px < 0)
		map->px = 0;
	if (map->py < 0)
		map->py = 0;
	map->test->instances[0].x = map->px;
	map->test->instances[0].y = map->py;
	raycaster(map);
}

void	draw_line(t_map	*map, float beginx, float beginy, float endx, float endy)
{
	int		pixels;
	double	deltax;
	double	deltay;

	fill_background(map);
	deltax = endx - beginx;
	deltay = endy - beginy;
	pixels = sqrt((deltax * deltax) + deltay * deltay);
	deltax /= pixels;
	deltay /= pixels;
	while (pixels && beginx > 0 && beginy > 0 && beginx < SCREEN_WIDTH && beginy < SCREEN_HEIGHT)
	{
		mlx_put_pixel(map->bg, beginx, beginy, 0x1111ff);
		beginx += deltax;
		beginy += deltay;
		--pixels;
	}

}


void	fill_background(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	while (++y < 1080 / 2)
	{
		x = -1;
		while (++x < 1920)
		{
			mlx_put_pixel(map->bg, x, y, 0xa5e1f0);
		}
	}
	while (++y < 1080)
	{
		x = -1;
		while (++x < 1920)
		{
			mlx_put_pixel(map->bg, x, y, 0xf0e1a5);
		}
	}

}

void	window(t_map *map)
{
	int	x;
	int	y;

	x = 1920;
	y = 1080;
	mlx_set_setting(MLX_MAXIMIZED, true);
	map->mlx = mlx_init(x, y, "cub3D", true);
	if (!map->mlx)
		exit(EXIT_FAILURE);
}

void	fill_wall(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 63)
	{
		x = -1;
		while (++x < 63)
		{
			mlx_put_pixel(map->no_i, x, y, 0xffffff);
		}
	}
}

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