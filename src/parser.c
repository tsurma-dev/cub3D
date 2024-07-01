/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:02 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/01 16:44:05 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parser(char *path, t_map *map)
{
	char	*line;
	char	*temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		strerror(ENONET);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		ft_noendl(temp);
		line = ft_trimspace(temp);
		if (!line)
			return (EINVAL);
		free(temp);
		if (*line == 'C')
			map->colour_c = rgb_extractor(&line[1]);
		else if (*line == 'F')
			map->colour_f = rgb_extractor(&line[1]);
		free(line);
		temp = get_next_line(fd);
	}
	free(temp);
	return (TRUE);
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

