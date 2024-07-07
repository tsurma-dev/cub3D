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

int parser(char *path, t_map *map)
{
    char    **file = NULL;
    char    *line;
    int     fd;
    int     i;

    check_ext(path);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (ENONET);
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("Read line: %s\n", line);
        file = ft_pointjoin(file, line);
        if (!file)
        {
            printf("Error: Could not join lines\n");
            close(fd);
            return (ENOMEM);
        }
        line = get_next_line(fd);
    }
    close(fd);
    i = -1;
    while (file[++i] && parse_line(map, file[i]) != 3)
    {
        printf("Parsing line %d: %s\n", i, file[i]);
    }
    if (!file[i])
        return (ENONET);
    printf("Map data found, parsing map\n");
    if (parse_map(map, &file[i]) != 0)
    {
        printf("Error parsing map\n");
        exit(EXIT_FAILURE);
    }
    printf("Parsed map successfully.\n");
    int player_x = -1, player_y = -1;
    if (!find_player_position(map, &player_x, &player_y))
    {
        printf("Error: No player start position found\n");
        exit(EXIT_FAILURE);
    }
    printf("Player position found at (%d, %d).\n", player_x, player_y);
    if (!check_valid_map(map, player_x, player_y))
    {
        printf("Error: Map validation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Map validation successful.\n");
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
/*
int valid_char(char c)
{
    return (c == ' ' || c == '0' || c == '1' || c == 'N' ||
            c == 'S' || c == 'E' || c == 'W');
}

int char_to_int(char c)
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
*/

int parse_map(t_map *map, char **lines)
{
    int i;
    int j;
    int mapj;
    char *line;
    char *end;
    char c;

    if (get_map_dimensions(map, lines) == -1)
    {
        fprintf(stderr, "Error: Could not get map dimensions\n");
        return (-1);
    }
    printf("Map dimensions: %d x %d\n", map->mapx, map->mapy);
    map->mapp = malloc(sizeof(int) * (map->mapx * map->mapy));
    if (!map->mapp)
        return (ENOMEM);
    i = -1;
    mapj = 0;
    while (lines[++i])
    {
        line = lines[i];
        while (ft_isspace((unsigned char) *line))
            line++;
        end = line + ft_strlen(line) - 1;
        while (end > line && ft_isspace((unsigned char) *end))
            end--;
        end[1] = '\0';

        j = -1;
        while (line[++j])
        {
            c = line[j];
            printf("Parsing character '%c' at line %d, position %d\n", c, i, j);
            if (c == '1')
                map->mapp[mapj++] = WALL;
            else if (c == '0')
                map->mapp[mapj++] = FLOOR;
            else if (c == 'N')
                map->mapp[mapj++] = N;
            else if (c == 'E')
                map->mapp[mapj++] = E;
            else if (c == 'W')
                map->mapp[mapj++] = W;
            else if (c == 'S')
                map->mapp[mapj++] = S;
            else if (c == ' ')
                map->mapp[mapj++] = NOTHING;
            else
            {
                printf("Error: Unexpected character '%c' in map\n", c);
                return (1);
            }
        }
        while (j < map->mapx)
        {
            if (mapj >= map->mapx * map->mapy)
            {
                printf("Error: Index out of bounds at mapj=%d\n", mapj);
                return (1);
            }
            map->mapp[mapj++] = NOTHING;
            j++;
        }
    }
    printf("Map parsed and loaded into memory.\n");
    return (0);
}


int	get_map_dimensions(t_map *map, char **lines)
{
	int x;
	int y;
    char *line;
    char *end;

	map->mapx = 0;
    map->mapy = 0;

    y = 0;
    while (lines[y])
    {
        line = lines[y];
        while (ft_isspace((unsigned char)*line))
            line++;
        end = line + ft_strlen(line) - 1;
        while (end > line && ft_isspace((unsigned char)*end))
            end--;
        end[1] = '\0';

        if (line[0] == '1' || line[0] == ' ')
        {
            x = ft_strlen(line);
            if (x > map->mapx)
                map->mapx = x;
            map->mapy++;
        }
        y++;
    }
    return (map->mapx > 0 && map->mapy > 0) ? 0 : -1;
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
    return ret;
}
