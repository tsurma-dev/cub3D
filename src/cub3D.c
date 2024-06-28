/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:28 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/28 16:42:42 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	static t_map	map;

	if (argc != 2)
		strerror(EINVAL);
	parser(argv[1], &map);
	printf("%d\n", map.colour_c);
	printf("%d\n", map.colour_f);
}






// char	**ft_pointjoin(char **dest, char *src)
// {
// 	char	**ret;
// 	int		i;
// 	int		j;

// 	if (!src)
// 		exit (0);
// 	i = 0;
// 	j = -1;
// 	if (dest != NULL)
// 	{
// 		while (dest[i] != NULL)
// 			++i;
// 	}
// 	ret = ft_calloc(sizeof(char *), i + 2);
// 	if (!ret)
// 		return (NULL);
// 	ret[i] = src;
// 	if (dest != NULL)
// 		while (--i >= 0)
// 			ret[i] = dest[i];
// 	free(dest);
// 	return (ret);
// }
