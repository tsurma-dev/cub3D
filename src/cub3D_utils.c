/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:53:53 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 16:18:10 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**ft_pointjoin(char **dest, char *src)
{
	char	**ret;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	if (dest != NULL)
	{
		while (dest[i] != NULL)
			++i;
	}
	ret = ft_calloc(sizeof(char *), i + 2);
	if (!ret)
		return (NULL);
	ret[i] = src;
	while (i > 0)
	{
		i--;
		ret[i] = dest[i];
	}
	free(dest);
	return (ret);
}

int	path_extractor(char *line, t_map *map, int ind)
{
	size_t	i;

	if ((ind == 0 && map->no_t != NULL) || (ind == 1 && map->so_t != NULL)
		|| (ind == 2 && map->ea_t != NULL) || (ind == 3 && map->we_t != NULL))
		return (EXIT_FAILURE);
	line = ft_strnstr(line, "./", ft_strlen(line));
	if (!line)
		return (EXIT_FAILURE);
	i = -1;
	while (line[++i] && ft_isspace(line[i]) != 1)
		;
	line[i] = '\0';
	if (ind == 0)
		map->no_t = mlx_load_png(line);
	if (ind == 1)
		map->so_t = mlx_load_png(line);
	if (ind == 2)
		map->ea_t = mlx_load_png(line);
	if (ind == 3)
		map->we_t = mlx_load_png(line);
	return (EXIT_SUCCESS);
}

int	parse_color(t_map *map, char *line, size_t len)
{
	if (ft_strnstr(line, "C", len) != NULL)
	{
		if (rgb_extractor(line, &map->colour_c) == EXIT_FAILURE)
			return (RGB_OOR);
	}
	else if (ft_strnstr(line, "F", len) != NULL)
	{
		if (rgb_extractor(line, &map->colour_f) == EXIT_FAILURE)
			return (RGB_OOR);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_texture(t_map *map, char *line, size_t len)
{
	int	ind;

	ind = -1;
	if (ft_strnstr(line, "NO", len) != NULL)
		ind = 0;
	else if (ft_strnstr(line, "SO", len) != NULL)
		ind = 1;
	else if (ft_strnstr(line, "EA", len) != NULL)
		ind = 2;
	else if (ft_strnstr(line, "WE", len) != NULL)
		ind = 3;
	if (ind != -1)
	{
		if (path_extractor(line, map, ind) != EXIT_SUCCESS)
			return (4);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
