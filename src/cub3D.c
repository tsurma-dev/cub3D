/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 13:10:45 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	static t_map	map;

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
	load_images_tex(&map);
	update_player_direction(&map);
	printf("Player direction vectors: pdx = %f, pdy = %f\n", map.pdx, map.pdy);
	draw_map(&map);
	mlx_cursor_hook(map.mlx, mouse_hook, &map);
	mlx_loop_hook(map.mlx, &keyhook, &map);
	mlx_key_hook(map.mlx, &keyhook2, (void *)&map);
	mlx_loop(map.mlx);
	delete_tex_img(&map);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}

void	load_images_tex(t_map *map)
{
	mlx_texture_t	*tex;

	map->bg = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->p_layer = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->m_layer = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	fill_background(map);
	reverse_texture(map->no_t);
	reverse_texture(map->so_t);
	reverse_texture(map->we_t);
	reverse_texture(map->ea_t);
	mlx_image_to_window(map->mlx, map->bg, 0, 0);
	mlx_image_to_window(map->mlx, map->p_layer, 0, 0);
	mlx_image_to_window(map->mlx, map->m_layer, 0, 0);
	tex = mlx_load_png("./textures/mini.png");
	map->wall = mlx_texture_to_image(map->mlx, tex);
	mlx_delete_texture(tex);
}

void	delete_tex_img(t_map *map)
{
	mlx_delete_texture(map->no_t);
	mlx_delete_texture(map->so_t);
	mlx_delete_texture(map->we_t);
	mlx_delete_texture(map->ea_t);
	mlx_delete_image(map->mlx, map->bg);
	mlx_delete_image(map->mlx, map->p_layer);
	mlx_delete_image(map->mlx, map->m_layer);
	mlx_delete_image(map->mlx, map->wall);
	free(map->mapp);
}
