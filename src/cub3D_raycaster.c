/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:47:22 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/10 18:34:53 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	raycaster(t_map *map)
{
	t_ray	r;

	r.x = 0;
	while (r.x < SCREEN_WIDTH)
	{
		r.camera_x = 2 * r.x / (double)SCREEN_WIDTH - 1;
		r.ray_dir_x = map->pdx + map->plane_x * r.camera_x;
		r.ray_dir_y = map->pdy + map->plane_y * r.camera_x;
		r.map_x = (int)(map->px / TEXTURE_SIZE);
		r.map_y = (int)(map->py / TEXTURE_SIZE);
		r.delta_dist_x = fabs(1 / r.ray_dir_x);
		r.delta_dist_y = fabs(1 / r.ray_dir_y);
		set_step_dist(map, &r);
		r.hit = 0;
		find_coll(map, &r);
		set_draw_pos(&r);
		find_tex_hit(&r, map->px, map->py);
		r.y = r.draw_start;
		r.tex = select_texture(map, r.side, r.ray_dir_x, r.ray_dir_y);
		draw_column(map, &r);
		r.x++;
	}
}

void	find_tex_hit(t_ray *r, float px, float py)
{
	if (r->side == 0)
		r->wallx = py / TEXTURE_SIZE + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wallx = px / TEXTURE_SIZE + r->perp_wall_dist * r->ray_dir_x;
	r->wallx -= floor(r->wallx);
	r->texx = (int)(r->wallx * (double)TEXTURE_SIZE);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->texx = TEXTURE_SIZE - r->texx - 1;
	else if (r->side == 1 && r->ray_dir_y < 0)
		r->texx = TEXTURE_SIZE - r->texx - 1;
	r->step = 1.0 * TEXTURE_SIZE / r->line_height;
	r->tex_pos = (r->draw_start - SCREEN_HEIGHT / 2 + r->line_height / 2)
		* r->step;
}


void	set_draw_pos(t_ray *r)
{
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

void	set_step_dist(t_map *map, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (map->px / TEXTURE_SIZE - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1 - map->px / TEXTURE_SIZE)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (map->py / TEXTURE_SIZE - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1 - map->py / TEXTURE_SIZE)
			* r->delta_dist_y;
	}
}

void	draw_column(t_map *map, t_ray *r)
{
	while (r->y < r->draw_end)
	{
		r->texy = (int)r->tex_pos & (TEXTURE_SIZE - 1);
		r->tex_pos += r->step;
		r->color = tex_to_rgb(r->tex, r->texx, r->texy);
		mlx_put_pixel(map->p_layer, r->x, r->y, r->color);
		r->y++;
	}
}
