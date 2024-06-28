/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:48:24 by tsurma            #+#    #+#             */
/*   Updated: 2024/04/03 15:49:37 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix == NULL)
		return (NULL);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (NULL);
}
