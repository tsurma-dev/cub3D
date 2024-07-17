/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 16:20:21 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	static t_map	map;

	if (argc != 2)
		return (ret_print(1, "Usage: ./cub3D <map_file.cub>\n"));
	initiate_cub3dmap(&map);
	if (parser(argv[1], &map) != 0)
		return (ret_print(1, "Error\nFailed to parse map file.\n"));
	window(&map);
	if (load_images_tex(&map) == EXIT_FAILURE)
	{
		delete_tex_img(&map);
		mlx_terminate(map.mlx);
		return (ret_print(1, "\nError\nCould not load all images."));
	}
	update_player_direction(&map);
	draw_map(&map);
	mlx_cursor_hook(map.mlx, mouse_hook, &map);
	mlx_loop_hook(map.mlx, &keyhook, &map);
	mlx_key_hook(map.mlx, &keyhook2, (void *)&map);
	mlx_loop(map.mlx);
	delete_tex_img(&map);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}

int	load_images_tex(t_map *map)
{
	mlx_texture_t	*tex;

	if (!map->no_t || !map->so_t || !map->ea_t || !map->we_t)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

void	delete_tex_img(t_map *map)
{
	if (map->no_t != NULL)
		mlx_delete_texture(map->no_t);
	if (map->so_t != NULL)
		mlx_delete_texture(map->so_t);
	if (map->we_t != NULL)
		mlx_delete_texture(map->we_t);
	if (map->ea_t != NULL)
		mlx_delete_texture(map->ea_t);
	if (map->bg != NULL)
		mlx_delete_image(map->mlx, map->bg);
	if (map->p_layer != NULL)
		mlx_delete_image(map->mlx, map->p_layer);
	if (map->m_layer != NULL)
		mlx_delete_image(map->mlx, map->m_layer);
	if (map->wall != NULL)
		mlx_delete_image(map->mlx, map->wall);
	if (map->mapp != NULL)
		free(map->mapp);
}
