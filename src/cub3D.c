/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/05 18:07:13 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int main(void)
{
    t_map    map;

    int mapp[] = {
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
    map.px = 150;
    map.py = 150;
    map.pa = 0;
    map.pdx = cos(map.pa) * MOVE_SPEED;
    map.pdy = sin(map.pa) * MOVE_SPEED;
    map.plane_x = 0.66 * map.pdy;
    map.plane_y = -0.66 * map.pdx;

    window(&map);
    map.mapp = mapp;
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


void draw_map(t_map *map)
{
    int y = 0;
    int x = 0;

    while (y < map->mapy)
    {
        x = 0;
        while (x < map->mapx)
        {
            if (map->mapp[y * map->mapx + x] == 1)
            {
                mlx_image_to_window(map->mlx, map->no_i, x * TEXTURE_SIZE, y * TEXTURE_SIZE);
            }
            x++;
        }
        y++;
    }
}
void update_player_direction(t_map *map)
{
    map->pdx = cos(map->pa) * MOVE_SPEED;
    map->pdy = sin(map->pa) * MOVE_SPEED;
    map->plane_x = 0.66 * map->pdy;
    map->plane_y = -0.66 * map->pdx;
}

void keyhook(void *param)
{
    t_map *map = (t_map *)param;
    int moved = 0;

    if (mlx_is_key_down(map->mlx, MLX_KEY_W))
    {
        double move_speed = MOVE_SPEED_FORWARD;
        if (map->mapp[(int)((map->py + map->pdy * move_speed) / TEXTURE_SIZE) * map->mapx + (int)(map->px / TEXTURE_SIZE)] == 0)
            map->py += map->pdy * move_speed;
        if (map->mapp[(int)(map->py / TEXTURE_SIZE) * map->mapx + (int)((map->px + map->pdx * move_speed) / TEXTURE_SIZE)] == 0)
            map->px += map->pdx * move_speed;
        moved = 1;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_S))
    {
        double move_speed = MOVE_SPEED_BACKWARD;
        if (map->mapp[(int)((map->py - map->pdy * move_speed) / TEXTURE_SIZE) * map->mapx + (int)(map->px / TEXTURE_SIZE)] == 0)
            map->py -= map->pdy * move_speed;
        if (map->mapp[(int)(map->py / TEXTURE_SIZE) * map->mapx + (int)((map->px - map->pdx * move_speed) / TEXTURE_SIZE)] == 0)
            map->px -= map->pdx * move_speed;
        moved = 1;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_A))
    {
        map->pa += TURN_SPEED;
        if (map->pa > 2 * PI)
            map->pa -= 2 * PI;
        update_player_direction(map);
        moved = 1;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_D))
    {
        map->pa -= TURN_SPEED;
        if (map->pa < 0)
            map->pa += 2 * PI;
        update_player_direction(map);
        moved = 1;
    }

    if (moved)
    {
        // fill_background(map);
        ft_bzero(map->p_layer->pixels, (map->p_layer->height * map->p_layer->width) * 4);
        raycaster(map);
        // mlx_image_to_window(map->mlx, map->p_layer, 0, 0);
        // mlx_image_to_window(map->mlx, map->test, map->px, map->py);
    }

    if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(map->mlx);
    }
}

void fill_background(t_map *map)
{
    int y;
    int x;

    y = 0;
    while (y < SCREEN_HEIGHT / 2)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            mlx_put_pixel(map->bg, x, y, 0xa5e1f0);
            x++;
        }
        y++;
    }
    while (y < SCREEN_HEIGHT)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            mlx_put_pixel(map->bg, x, y, 0xf0e1a5);
            x++;
        }
        y++;
    }
}

void window(t_map *map)
{
    mlx_set_setting(MLX_MAXIMIZED, true);
    map->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    if (!map->mlx)
        exit(EXIT_FAILURE);
}

void fill_wall(t_map *map)
{
    int y;
    int x;

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

void fill_test(t_map *map)
{
    int y;
    int x;

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
void draw_line(t_map *map, float beginx, float beginy, float endx, float endy)
{
    int     pixels;
    double  deltax;
    double  deltay;

    fill_background(map);
    deltax = endx - beginx;
    deltay = endy - beginy;
    pixels = sqrt((deltax * deltax) + deltay * deltay);
    deltax /= pixels;
    deltay /= pixels;
    while (pixels && beginx > 0 && beginy > 0 && beginx < SCREEN_WIDTH && beginy < SCREEN_HEIGHT)
    {
        mlx_put_pixel(map->p_layer, beginx, beginy, 0x1111ff);
        beginx += deltax;
        beginy += deltay;
        --pixels;
    }
}
