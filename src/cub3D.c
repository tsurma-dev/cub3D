/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/12 15:34:18 by tsurma           ###   ########.fr       */
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

	update_player_direction(&map);
	printf("Player direction vectors: pdx = %f, pdy = %f\n", map.pdx, map.pdy);

	map.bg = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map.p_layer = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// map.test = mlx_new_image(map.mlx, 2, 2);

	fill_background(&map);
	// fill_test(&map);
	// fill_wall(&map);
	reverse_texture(map.no_t);
	reverse_texture(map.so_t);
	reverse_texture(map.we_t);
	reverse_texture(map.ea_t);

	mlx_image_to_window(map.mlx, map.bg, 0, 0);
	mlx_image_to_window(map.mlx, map.p_layer, 0, 0);

	mlx_texture_t  *tex = mlx_load_png("./textures/mini.png");
	map.wall = mlx_texture_to_image(map.mlx, tex);
	mlx_delete_texture(tex);
	draw_map(&map);

	// draw_map(&map);
	// mlx_image_to_window(map.mlx, map.test, map.px, map.py);
    mlx_cursor_hook(map.mlx, mouse_hook, &map);

	mlx_loop_hook(map.mlx, &keyhook, &map);
	mlx_key_hook(map.mlx, &keyhook2, (void *)&map);
	mlx_loop(map.mlx);

	// mlx_delete_texture(map.no_t);
	// mlx_delete_texture(map.so_t);
	// mlx_delete_texture(map.we_t);
	// mlx_delete_texture(map.ea_t);
	// mlx_delete_image(map.mlx, map.bg);
	// mlx_delete_image(map.mlx, map.p_layer);

	// mlx_delete_image(map.mlx, map.test);
	// mlx_delete_image(map.mlx, map.no_i);
	free(map.mapp);
	mlx_terminate(map.mlx);

	return (EXIT_SUCCESS);
}

void	keyhook2(mlx_key_data_t keydata, void *ma)
{
	t_map	*map;

	map = (t_map *)ma;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		map->wall->enabled ^= 1;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}
