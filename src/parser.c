/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:02 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/05 17:50:24 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parser(char *path, t_map *map)
{
	char	**file;
	char	*line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ENONET);
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file = ft_pointjoin(file, line);
		if (!file)
			return (ENOMEM);
	}
	i = -1;
	while (file[++i] && parse_line(map, file[i]) != 3)
		;
	if (!file[i])
		return (ENONET);
	parse_map(map, &file[i]);
	return (0);
}

int	parse_line(t_map *map, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "NO", len) != NULL)
		map->no_t = path_extractor(line);
	else if (ft_strnstr(line, "SO", len) != NULL)
		map->so_t = path_extractor(line);
	else if (ft_strnstr(line, "EA", len) != NULL)
		map->ea_t = path_extractor(line);
	else if (ft_strnstr(line, "WE", len) != NULL)
		map->we_t = path_extractor(line);
	else if (ft_strnstr(line, "C", len) != NULL)
		map->colour_c = (rgb_extractor(line));
	else if (ft_strnstr(line, "F", len) != NULL)
		map->colour_f = (rgb_extractor(line));
	else if (ft_strnstr(line, "1111", len) != NULL)
		return (3);
	else
		return (1);
	return (0);

}


mlx_texture_t	*path_extractor(char *line)
{
	size_t	i;

	line = ft_strnstr(line, "./", ft_strlen(line));
	if (!line)
		return (NULL);
	i = -1;
	while (line[++i] && ft_isspace(line[i]) != 1 )
		;
	line[i] = '\0';
	return (mlx_load_png(line));
}


// mlx_image_t	*load_image(char *line)
// {
// 	int				i;
// 	int				fd;
// 	mlx_texture_t	*tex;
// 	mlx_image_t		*img;

// 	i = 0;
// 	while (line[i] && line[i] == ' ')
// 		++i;
// 	if (!line[i] || (line[i] != '.' || line[i + 1] != '/'))
// 		return (NULL);
// 	tex = mlx_load_png(line[i + 1]);
// 	if (!tex)
// 		return (NULL);
// 	img = mlx_texture_to_image(mlx, tex);
// 	free(tex);

// }

// int	rgb_to_int(int r, int g, int b)
// {
// 	int	rgb;

// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 		return (-1);
// 	rgb = (r << (3 * 8)) + (g << (2 * 8)) + (b << (1 * 8));
// 	return (rgb);
// }

int	rgb_extractor(char *line)
{
	int	i;
	int	rgb;
	int	c;

	if (!line)
		return (-1);
	i = 0;
	rgb = 0;
	c = 3;
	while (line[i] && line[i] == ' ')
		++i;
	while (--c >= 0)
	{
		if (ft_isdigit(line[i]) == FALSE)
			return (UNEX_CHAR);
		rgb = (rgb << 8) + ft_atoi(&line[i]);
		if ((rgb & 0xff) > 255 || (rgb & 0xff) < 0)
			return (RGB_OOR);
		while (ft_isdigit(line[i]) == TRUE)
			++i;
		if (line[i] == ',')
			++i;
	}
	return (rgb);
}

int	parse_map(t_map *map, char **lines)
{
	int	i;
	int	j;
	int	*mapi;
	int	mapj;

	if (get_map_dimensions(map, lines) == -1)
		return (-1);
	mapi = malloc(sizeof(int) * (map->mapx * map->mapy));
	if (!mapi)
		return (ENOMEM);
	i = -1;
	mapj = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j] && lines[i][j] != '\n')
		{
			if (lines[i][j] == '1')
				mapi[++mapj] = WALL;
			else if (lines[i][j] == '0')
				mapi[++mapj] = FLOOR;
			else if (lines[i][j] == 'N')
				mapi[++mapj] = N;
			else if (lines[i][j] == 'E')
				mapi[++mapj] = E;
			else if (lines[i][j] == 'W')
				mapi[++mapj] = W;
			else if (lines[i][j] == 'S')
				mapi[++mapj] = S;
			else if (lines[i][j] == ' ')
				mapi[++mapj] = NOTHING;
			else
				return (1);
		}
		while (j < map->mapx - 1)
			mapi[++mapj] = NOTHING;
	}
	return (0);
}

int	get_map_dimensions(t_map *map, char **lines)
{
	int	x;
	int	y;

	y = -1;
	while (lines[++y] && lines[y][0] == '1' && lines[y][0] == ' ')
	{
		x = ft_strlen(lines[y]);
		if (x > map->mapx)
			map->mapx = x;
	}
	map->mapy = y;
	if (lines[y] != NULL)
		return (-1);
	return (0);
}

char	**ft_pointjoin(char **dest, char *src)
{
	char	**ret;
	int		i;
	int		j;

	if (!src)
		exit (0);
	i = 0;
	j = -1;
	if (dest != NULL)
	{
		while (dest[i] != NULL)
			++i;
	}
	ret = ft_calloc(sizeof(char *), i + 2);
	if (!ret)
		return (NULL);
	ret[i] = src;
	if (dest != NULL)
		while (--i >= 0)
			ret[i] = dest[i];
	free(dest);
	return (ret);
}
