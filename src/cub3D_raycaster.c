/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:47:22 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/08 17:54:52 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
    unsigned int color;
    double wallx;
    int texx;
    int texy;
    double step;
    double tex_pos;
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
            side_dist_x = (map_x + 1 - map->px / TEXTURE_SIZE) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (map->py / TEXTURE_SIZE - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1 - map->py / TEXTURE_SIZE) * delta_dist_y;
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
		// while (y < draw_end)
		// {
		// 	color = tex_to_rgb(map, x % 64, (y - draw_start) % 64);
		// 	mlx_put_pixel(map->p_layer, x, y, color);
		// 	y++;
		// }

        if (side == 0)
            wallx = map->py + perp_wall_dist * ray_dir_y;
        else
            wallx = map->px + perp_wall_dist * ray_dir_x;
        wallx -= floor(wallx);
        texx = (int)(wallx * (double)TEXTURE_SIZE);
        if (side == 0 && ray_dir_x > 0)
            texx = TEXTURE_SIZE - texx - 1;
        else if (side == 1 && ray_dir_y < 0)
            texx = TEXTURE_SIZE - texx - 1;
        step = 1.0 * TEXTURE_SIZE / line_height;
        tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
        y = draw_start;
        while (y < draw_end)
        {
            texy = (int)tex_pos & (TEXTURE_SIZE - 1);
            tex_pos += step;
            color = tex_to_rgb(map, texx, texy);
            mlx_put_pixel(map->p_layer, x, y, color);
            y++;
        }
        x++;
    }
}


unsigned int	tex_to_rgb(t_map *map, int x, int y)
{
	int	abgr;
	int	rgba;
	int	*array;

	array = (int *)map->no_i->pixels;
	abgr = array[y * TEXTURE_SIZE + x];
	rgba = reverse_bytes(abgr);

	return (rgba);
}

unsigned int	reverse_bytes(int abgr)
{
	unsigned int rgba = 0;
	unsigned char byte;
	int i;

	i = 0;
	while (i < 32)
	{
		byte = (abgr >> i) & 0xff;
		rgba |= byte << (32 - 8 - i);
		i += 8;
	}
	return (rgba);
}

