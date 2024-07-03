/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/03 22:16:06 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(void)
{
	static t_map	map;
	int mapp[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,};

	map.mapx = 8;
	map.mapy = 8;
	map.px = 70;
	map.py = 70;
	map.pa = 0;
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
	mlx_image_to_window(map.mlx, map.test, map.px, map.py);
	mlx_key_hook(map.mlx, &keyhook, (void *)&map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}

float	distance(float ax, float ay, float bx, float by)
{
	float	tangens1;
	float	tangens2;

	tangens1 = (bx - ax) * (bx - ax);
	tangens2 = (by - ay) * (by - ay);
	// printf("t1 %f\nt2 %f\n", tangens1, tangens2);
	// printf("%f\n", sqrt(tangens1 + tangens2));
	return (sqrt(tangens1 + tangens2));
}

void	drawwall(t_map *map, int x, int y, int yend, int color)
{
	int	i;
	int	s;

	s = y;
	i = x;
	while (x < i + 10)
	{
		y = s;
		while (y <= yend)
		{
			mlx_put_pixel(map->bg, x + 700, y + 200, color);
			y++;
		}
		x++;
	}
}


void	raycaster(t_map *map)
{
	t_ray	h;
	t_ray	v;
	float	offset;
	float	dist;
	float	lineheight;
	float	lineoffset;
	float	fish;
	int		color;

	fill_background(map);
	offset = -(FOV / 2);
	while (offset < FOV / 2)
	{
		horizontal_ray(map, &h, offset);
		vertical_ray(map, &v, offset);
		if (h.dist >= v.dist)
		{
			dist = v.dist;
			draw_line(map, map->px, map->py, v.rx, v.ry, GREEN);
			fish = map->pa - v.ra;
			color = DARKBLUE;
		}
		else
		{
			dist = h.dist;
			draw_line(map, map->px, map->py, h.rx, h.ry, BLUE);
			fish = map->pa - h.ra;
			color = BLUE;
		}
		if (fish < 0)
			fish += (2 * PI);
		if (fish > (2 * PI))
			fish -= (2 * PI);
		dist = (dist * cos(fish));
		lineheight = (map->mapx * map->mapy * 640) / dist;
		if (lineheight > 640)
			lineheight = 640;
		lineoffset = 320 - lineheight / 2;

		drawwall(map, offset * 10, lineoffset, lineheight, color);
		offset += 0.3;
	}
	// printf("h: %f\nv: %f\n", h.dist, v.dist);
	// printf("hmp: %d\nvmp: %d\n", h.mp, v.mp);

}

void	vertical_ray(t_map *map, t_ray *r, float offset)
{
	r->ra = map->pa + (DR * offset);
	if (r->ra < 0)
		r->ra += 2 * PI;
	if (r->ra > 2 * PI)
		r->ra -= 2 * PI;
	r->dof = 0;
	r->atan = -tan(r->ra);
	if (r->ra < PI2 || r->ra > PI3)
	{
		r->rx = (((int)map->px >> 6) << 6);
		r->ry = (map->px - r->rx) * r->atan + map->py;
		r->xo = -64;
		r->yo = -r->xo * r->atan;
	}
	if (r->ra > PI2 && r->ra < PI3)
	{
		r->rx = (((int)(map->px) >> 6) << 6) + 64;
		r->ry = (map->px - r->rx) * r->atan + map->py;
		r->xo = 64;
		r->yo = -r->xo * r->atan;
	}
	if (r->ra == PI2)
	{
		r->rx = map->px;
		r->ry = map->py;
		r->dof = 8;
	}
	// printf("%f\n", map->px - r->rx);
	while (r->dof < 8)
	{
		r->mx = (int)(r->rx) >> 6;
		r->my = (int)(r->ry) >> 6;
		if (r->ra < PI2 || r->ra > PI3)
			r->mx--;
		r->mp = r->my * map->mapx + r->mx;
		if (r->mp > 0 && r->mp < (map->mapx * map->mapy) && map->mapp[r->mp] == 1)
			r->dof = 8;
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof++;
		}
	}
	r->dist = distance(map->px, map->py, r->rx, r->ry);
	// printf("rx=%f\nry=%f\nra=%f\nrdist=%f\n", r->rx, r->ry, r->ra, r->dist);
}

void	horizontal_ray(t_map *map, t_ray *r, float offset)
{
	r->ra = map->pa + (DR * offset);
	if (r->ra < 0)
		r->ra += 2 * PI;
	if (r->ra > 2 * PI)
		r->ra -= 2 * PI;
	r->dof = 0;
	if (r->ra == 0)
		r->atan = 0;
	else
		r->atan = (-1 / tan(r->ra));
	if (r->ra > PI)
	{
		r->ry = (((int)map->py >> 6) << 6) + 64;
		r->rx = (map->py - r->ry) * r->atan + map->px;
		r->yo = 64;
		r->xo = -r->yo * r->atan;
	}
	if (r->ra < PI)
	{
		r->ry = (((int)(map->py) >> 6) << 6);
		r->rx = (map->py - r->ry) * r->atan + map->px;
		r->yo = -64;
		r->xo = -r->yo * r->atan;
	}
	if (r->ra == 0 || r->ra == PI)
	{
		r->rx = map->px;
		r->ry = map->py;
		r->dof = 8;
	}
	while (r->dof < 8)
	{
		r->mx = ((int)(r->rx) >> 6);
		r->my = ((int)(r->ry) >> 6);
		if (r->ra < PI)
			r->my--;
		r->mp = r->my * map->mapx + r->mx;
		if (r->mp > 0 && r->mp < (map->mapx * map->mapy) && map->mapp[r->mp] == 1)
			r->dof = 8;
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			++r->dof;
		}
	}
	r->dist = distance(map->px, map->py, r->rx, r->ry);
}

void	draw_map(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->mapy)
	{
		x = -1;
		while (++x < map->mapx)
			if (map->mapp[y * map->mapx + x] == 1)
				mlx_image_to_window(map->mlx, map->no_i, x * SQUARE_SIZE, y * SQUARE_SIZE);
	}
}

void	keyhook(mlx_key_data_t keydata, void *ma)
{
	t_map	*map;

	(void)keydata;
	map = (t_map *)ma;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->px -= map->pdx * MOVE_SPEED;
		map->py -= map->pdy * MOVE_SPEED;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->px += map->pdx * MOVE_SPEED;
		map->py += map->pdy * MOVE_SPEED;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->pa -= 0.1;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
		if (map->pa < 0)
			map->pa += 2 * PI;
		map->pdx = cos(map->pa) * 5;
		map->pdy = sin(map->pa) * 5;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
		if (map->pa < 0)
			map->pa += 2 * PI;
		map->pdx = cos(map->pa) * 5;
		map->pdy = sin(map->pa) * 5;
	}
	map->test->instances[0].x = map->px;
	map->test->instances[0].y = map->py;
	raycaster(map);
}

void	draw_line(t_map	*map, float beginx, float beginy, float endx, float endy, int col)
{
	int		pixels;
	double	deltax;
	double	deltay;

	deltax = endx - beginx;
	deltay = endy - beginy;
	pixels = sqrt((deltax * deltax) + deltay * deltay);
	deltax /= pixels;
	deltay /= pixels;
	while (pixels && beginx > 0 && beginy > 0 && beginx < SCREEN_WIDTH && beginy < SCREEN_HEIGHT)
	{
		mlx_put_pixel(map->bg, beginx, beginy, col);
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

	x = SCREEN_WIDTH;
	y = SCREEN_HEIGHT;
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
	while (++y < SQUARE_SIZE - 1)
	{
		x = -1;
		while (++x < SQUARE_SIZE - 1)
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
