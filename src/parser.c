/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:02 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/15 14:11:40 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	read_file(char *path, char ***file)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ENOENT);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Read line: %s\n", line);
		*file = ft_pointjoin(*file, line);
		if (!(*file))
		{
			free(line);
			close(fd);
			return (ENOMEM);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	parser(char *path, t_map *map)
{
	char	**file = NULL;
	int		i;
	int		player_x;
	int		player_y;

	check_ext(path);
	if (read_file(path, &file) != 0)
		parser_exit(NULL, map, ENOMEM, "Could not join lines");
	i = -1;
	while (file[++i] && parse_line(map, file[i]) != 3)
		printf("Parsing line %d: %s\n", i, file[i]);
	printf("Map data found, parsing map\n");
	if (parse_map(map, &file[i]) != 0)
		parser_exit(file, map, 1, "Could not parse map");
	printf("Parsed map successfully.\n");
	player_x = -1;
	player_y = -1;
	if (!find_player_position(map, &player_x, &player_y))
		parser_exit(file, map, EINVAL, "No player start position found");
	printf("Player position found at (%d, %d).\n", player_x, player_y);
	if (!check_valid_map(map, player_x, player_y))
		parser_exit(file, map, EINVAL, "Map validation failed");
	ft_free_matrix(file);
	printf("Map validation successful.\n");
	printf("c = %d\nf = %d\n", map->colour_c, map->colour_f);
	return (0);
}

void	parser_exit(char **file, t_map *map, int err_nr, const char *message)
{
	if (map->mapp != NULL)
		free(map->mapp);
	if (file != NULL)
		ft_free_matrix(file);
	if (!message)
		printf("Error\n%s\n", strerror(err_nr));
	else
		printf("Error\n%s\n", message);
	exit(err_nr);
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
	else if (ft_strnstr(line, "1", len) != NULL)
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
	while (line[++i] && ft_isspace(line[i]) != 1)
		;
	line[i] = '\0';
	return (mlx_load_png(line));
}
