/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycaster2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:56:25 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/17 13:11:39 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	find_coll(t_map *map, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x >= 0 && r->map_x < map->mapx && r->map_y >= 0
			&& r->map_y < map->mapy && map->mapp[r->map_y * map->mapx
				+ r->map_x] == 1)
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
}

mlx_texture_t	*select_texture(t_map *map, int side, double rdx, double rdy)
{
	if (side == 1 && rdy < 0)
		return (map->no_t);
	else if (side == 1)
		return (map->so_t);
	if (rdx < 0)
		return (map->we_t);
	return (map->ea_t);
}

unsigned int	tex_to_rgb(mlx_texture_t *tex, int x, int y)
{
	int	rgba;
	int	*array;

	if (!tex)
		return (0);
	x = tex->width - x - 1;
	array = (int *)tex->pixels;
	rgba = array[y * (tex->width) + x];
	return (rgba);
}

void	reverse_texture(mlx_texture_t *tex)
{
	int	i;
	int	size;

	if (!tex)
		return ;
	size = tex->height * tex->width * 4;
	i = 0;
	while (i < size)
	{
		tex->pixels[i + 0] = tex->pixels[i] ^ tex->pixels[i + 3];
		tex->pixels[i + 3] = tex->pixels[i] ^ tex->pixels[i + 3];
		tex->pixels[i + 0] = tex->pixels[i] ^ tex->pixels[i + 3];
		tex->pixels[i + 1] = tex->pixels[i + 1] ^ tex->pixels[i + 2];
		tex->pixels[i + 2] = tex->pixels[i + 1] ^ tex->pixels[i + 2];
		tex->pixels[i + 1] = tex->pixels[i + 1] ^ tex->pixels[i + 2];
		i += 4;
	}
}
