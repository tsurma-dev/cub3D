/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olobresh <olobresh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:50:58 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/11 17:51:05 by olobresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	char_to_int(char c)
{
	if (c == '1')
		return (WALL);
	if (c == '0')
		return (FLOOR);
	if (c == 'N')
		return (N);
	if (c == 'S')
		return (S);
	if (c == 'E')
		return (E);
	if (c == 'W')
		return (W);
	if (c == ' ')
		return (NOTHING);
	return (-1);
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
	int		j;
	char	c;

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
	int		i;
	int		mapj;
	char	*line;

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
