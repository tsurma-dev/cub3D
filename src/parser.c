/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:02 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 16:18:39 by tsurma           ###   ########.fr       */
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

void	parser_2(t_map *map, int *i, char **file)
{
	int	j;

	j = 0;
	while (file[++*i])
	{
		j = parse_line(map, file[*i]);
		if (j == 3)
			break ;
		if (j == EXIT_FAILURE)
			parser_exit(file, map, 1, "RGB out of range");
		else if (j == 2)
			parser_exit(file, map, 1, "Unexpected Character");
		else if (j == 4)
			parser_exit(file, map, 1, "Texture assignment Error");
	}
}

int	parser(char *path, t_map *map)
{
	char	**file;
	int		i;
	int		player_x;
	int		player_y;

	file = NULL;
	check_ext(path);
	if (read_file(path, &file) != 0)
		parser_exit(NULL, map, ENOMEM, "Could not join lines");
	i = -1;
	parser_2(map, &i, file);
	if (parse_map(map, &file[i]) != 0)
		parser_exit(file, map, 1, "Could not parse map");
	player_x = -1;
	player_y = -1;
	if (!find_player_position(map, &player_x, &player_y))
		parser_exit(file, map, EINVAL, "No player start position found");
	if (!check_valid_map(map, player_x, player_y))
		parser_exit(file, map, EINVAL, "Map validation failed");
	ft_free_matrix(file);
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
	int		result;

	len = ft_strlen(line);
	if (len == 0 || line[0] == '\n' || line[0] == '\0')
		return (EXIT_SUCCESS);
	result = parse_texture(map, line, len);
	if (result != EXIT_FAILURE)
		return (result);
	result = parse_color(map, line, len);
	if (result != EXIT_FAILURE)
		return (result);
	if (ft_strnstr(line, "1", len) != NULL)
		return (3);
	return (2);
}
