/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:25:38 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 14:25:17 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	borders(char **map)
{
	int	start;
	int	ret;
	int	x;
	int	y;

	start = ft_strchr_i(map[0], '1');
	map[0][start] = '3';
	map[0][start + 1] = '2';
	ret = crawler(map, start + 2, 0);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '2' || map[y][x] == '3')
				map[y][x] = '1';
	}
	return (ret);
}

int	crawler(char **map, int x, int y)
{
	static int	i;

	if (map[y][x] == '3')
	{
		i = 1;
	}
	map[y][x] = '2';
	if ((map[y][x + 1] == '1' || map[y][x + 1] == '3') && ft_is_edge(map, x + 1,
			y) == TRUE)
		crawler(map, x + 1, y);
	if (map[y + 1] && x <= (int)ft_strlen(map[y + 1]) && (map[y + 1][x] == '1'
		|| map[y + 1][x] == '3') && ft_is_edge(map, x, y + 1) == TRUE)
		crawler(map, x, y + 1);
	if (x > 0 && (map[y][x - 1] == '1' || map[y][x - 1] == '3')
		&& ft_is_edge(map, x - 1, y) == TRUE)
		crawler(map, x - 1, y);
	if (y > 0 && x <= (int)ft_strlen(map[y - 1]) && (map[y - 1][x] == '1'
		|| map[y - 1][x] == '3') && ft_is_edge(map, x, y - 1) == TRUE)
		crawler(map, x, y - 1);
	if (i == 1)
		return (0);
	return (-1);
}

int	ft_is_edge(char **map, int x, int y)
{
	if (x == 0 || y == 0)
		return (TRUE);
	if (map[y + 1] == NULL)
		return (TRUE);
	if (map[y][x + 1] == '\0' || map[y][x + 1] == '\n' || map[y][x + 1] == ' ')
		return (TRUE);
	if (map[y][x - 1] == ' ')
		return (TRUE);
	if (map[y + 1] && ((x >= ft_strrchr_i(map[y + 1], '1')
				&& (x >= ft_strrchr_i(map[y + 1], '2'))) || map[y
				+ 1][x] == ' '))
		return (TRUE);
	if (map[y + 1] && map[y + 1][x - 1] == ' ')
		return (TRUE);
	if (map[y + 1] && map[y + 1][x + 1] == ' ')
		return (TRUE);
	if (map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == '\0' || map[y - 1][x
		+ 1] == '\n')
		return (TRUE);
	if (map[y - 1][x - 1] == ' ')
		return (TRUE);
	return (FALSE);
}

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (i);
	return (0);
}

int	ft_strrchr_i(const char *s, int c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			r = i;
		i++;
	}
	if (s[i] == (char)c)
		r = i;
	return (r);
}
