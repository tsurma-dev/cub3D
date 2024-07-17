/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:50:58 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/17 13:18:36 by tsurma           ###   ########.fr       */
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

int	ret_print(int i, char *mess)
{
	printf("%s\n", mess);
	return (i);
}

int	process_map_line(t_map *map, char *line, int y)
{
	int		j;
	char	c;
	int		line_length;
	int		boundary_error;

	j = -1;
	line_length = ft_strlen(line);
	boundary_error = 0;
	while (++j < line_length)
	{
		c = line[j];
		if (!valid_char(c))
		{
			printf("Error: Unexpected character '%c' at position %d\n", c, j);
			return (1);
		}
		map->mapp[y * map->mapx + j] = char_to_int(c);
		if ((y == 0 || y == map->mapy - 1 || j == 0 || j == line_length - 1)
			&& char_to_int(c) == FLOOR)
			boundary_error = 1;
	}
	if (boundary_error)
		return (ret_print(1, "Error\n '0' found at border.\n"));
	return (0);
}

int	parse_map(t_map *map, char **lines)
{
	if (get_map_dimensions(map, lines) == -1)
	{
		printf("Error\nCould not get map dimensions\n");
		return (-1);
	}
	if (borders(lines) == -1)
		return (ret_print(1, "Error\nMap not enclosed.\n"));
	map->mapp = malloc(sizeof(int) * (map->mapx * map->mapy));
	if (!map->mapp)
		return (ENOMEM);
	return (process_map_lines(map, lines));
}
