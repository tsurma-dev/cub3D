/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/08 12:02:33 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	/*int mapp[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1};

	map.mapx = 8;
	map.mapy = 8;
	*/

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	initiate_cub3dmap(&map);
	if (parser(argv[1], &map) != 0)
	{
		printf("Error\nFailed to parse map file.\n");
		return (EXIT_FAILURE);
	}
	window(&map);

	update_player_direction(&map);
	printf("Player direction vectors: pdx = %f, pdy = %f\n", map.pdx, map.pdy);

	//map.mapp = mapp;
	map.bg = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map.p_layer = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// map.test = mlx_new_image(map.mlx, 2, 2);
	// map.no_i = mlx_new_image(map.mlx, 64, 64);

	fill_background(&map);
	// fill_test(&map);
	// fill_wall(&map);

	mlx_image_to_window(map.mlx, map.bg, 0, 0);
	mlx_image_to_window(map.mlx, map.p_layer, 0, 0);

	// draw_map(&map);
	// mlx_image_to_window(map.mlx, map.test, map.px, map.py);

	mlx_loop_hook(map.mlx, &keyhook, &map);
	mlx_loop(map.mlx);

	mlx_delete_image(map.mlx, map.bg);
	// mlx_delete_image(map.mlx, map.test);
	// mlx_delete_image(map.mlx, map.no_i);
	free(map.mapp);
	mlx_terminate(map.mlx);

	return (EXIT_SUCCESS);
}

void raycaster(t_map *map)
{
	int x;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	double perp_wall_dist;
	int line_height;
	int draw_start;
	int draw_end;
	int color;
	int y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_dir_x = map->pdx + map->plane_x * camera_x;
		ray_dir_y = map->pdy + map->plane_y * camera_x;

		map_x = (int)(map->px / TEXTURE_SIZE);
		map_y = (int)(map->py / TEXTURE_SIZE);

		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (map->px / TEXTURE_SIZE - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - map->px / TEXTURE_SIZE) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (map->py / TEXTURE_SIZE - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - map->py / TEXTURE_SIZE) * delta_dist_y;
		}

		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x >= 0 && map_x < map->mapx && map_y >= 0 && map_y < map->mapy && map->mapp[map_y * map->mapx + map_x] == 1)
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (map_x - map->px / TEXTURE_SIZE + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - map->py / TEXTURE_SIZE + (1 - step_y) / 2) / ray_dir_y;

		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		if (side == 1)
			color = 0x8888ff;
		else
			color = 0x1111ff;

		y = draw_start;
		while (y < draw_end)
		{
			mlx_put_pixel(map->p_layer, x, y, color);
			y++;
		}
		x++;
	}
}
