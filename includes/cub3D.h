/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:26 by tsurma            #+#    #+#             */
/*   Updated: 2024/06/28 16:12:46 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"

typedef enum parserr
{
	NOLINE,
	RGB_OOR,
	UNEX_CHAR
}	t_parserr;

typedef enum BOOL
{
	FALSE,
	TRUE
}	t_BOOL;

typedef struct cub3D_map
{
	void		*mlx;
	mlx_image_t	*no_i;
	mlx_image_t	*so_i;
	mlx_image_t	*we_i;
	mlx_image_t	*ea_i;
	int			colour_f;
	int			colour_c;
}	t_map;

int	parser(char *path, t_map *map);
int	rgb_extractor(char *line);



#endif
