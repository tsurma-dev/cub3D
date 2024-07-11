/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:02 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/10 15:49:16 by tsurma           ###   ########.fr       */
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
	{
		printf("Parsing line %d: %s\n", i, file[i]);
	}
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
	while (line[++i] && ft_isspace(line[i]) != 1)
		;
	line[i] = '\0';
	return (mlx_load_png(line));
}

int	process_rgb_component(char *line, int *i)
{
	int value;

	if (ft_isdigit(line[*i]) == FALSE)
		return (UNEX_CHAR);
	value = ft_atoi(&line[*i]);
	if (value > 255 || value < 0)
		return (RGB_OOR);
	while (ft_isdigit(line[*i]) == TRUE)
		++(*i);
	if (line[*i] == ',')
		++(*i);
	return (value);
}

int	rgb_extractor(char *line)
{
	int	i;
	int	rgb;
	int	component;
	int	c;

	if (!line)
		return (-1);
	i = 0;
	rgb = 0;
	c = 3;
	while (line[i] && line[i] == ' ')
		++i;
	if (line[i] == 'C' || line[i] == 'F')
		i++;
	while (line[i] && line[i] == ' ')
		++i;
	while (--c >= 0)
	{
		component = process_rgb_component(line, &i);
		if (component < 0)
			return (component);
		rgb = (rgb << 8) + component;
	}
	rgb = (rgb << 8) + 0xff;
	return (rgb);
}


int	valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W');
}

int	char_to_int(char c)
{
	if (c == '1')
		return WALL;
	if (c == '0')
		return FLOOR;
	if (c == 'N')
		return N;
	if (c == 'S')
		return S;
	if (c == 'E')
		return E;
	if (c == 'W')
		return W;
	if (c == ' ')
		return NOTHING;
	return -1;
}
void	trim_whitespace(char **line)
{
	char	*end;

	while (ft_isspace((unsigned char)**line))
		(*line)++;
	end = *line + ft_strlen(*line) - 1;
	while (end > *line && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';
}

int	process_map_line(t_map *map, char *line, int *mapj)
{
	int	j;
	char c;

	j = 0;
	while (line[j])
	{
		c = line[j];
		if (!valid_char(c))
		{
			printf("Error: Unexpected character '%c' in map\n", c);
			return (1);
		}
		map->mapp[(*mapj)++] = char_to_int(c);
		j++;
	}
	while (j < map->mapx)
	{
		if (*mapj >= map->mapx * map->mapy)
		{
			printf("Error: Index out of bounds at mapj=%d\n", *mapj);
			return (1);
		}
		map->mapp[(*mapj)++] = NOTHING;
		j++;
	}
	return (0);
}


int	parse_map(t_map *map, char **lines)
{
	int	i;
	int	mapj;
	char *line;

	if (get_map_dimensions(map, lines) == -1)
	{
		printf("Error: Could not get map dimensions\n");
		return (-1);
	}
	map->mapp = malloc(sizeof(int) * (map->mapx * map->mapy));
	if (!map->mapp)
		return (ENOMEM);
	i = 0;
	mapj = 0;
	while (lines[i])
	{
		line = lines[i];
		trim_whitespace(&line);
		if (process_map_line(map, line, &mapj) != 0)
			return (1);
		i++;
	}
	return (0);
}



int	get_map_dimensions(t_map *map, char **lines)
{
	int		x;
	int		y;
	char	*line;

	map->mapx = 0;
	map->mapy = 0;
	y = 0;
	while (lines[y])
	{
		line = lines[y];
		trim_whitespace(&line);
		if (line[0] == '1' || line[0] == ' ')
		{
			x = ft_strlen(line);
			if (x > map->mapx)
				map->mapx = x;
			map->mapy++;
		}
		y++;
	}
	if (map->mapx > 0 && map->mapy > 0)
		return (0);
	return (-1);
}

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
