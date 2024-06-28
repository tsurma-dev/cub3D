/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:16:35 by tsurma            #+#    #+#             */
/*   Updated: 2024/02/12 22:35:15 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		splitindex;
	int		wordlen;

	splitindex = 0;
	if (!s)
		return (NULL);
	split = malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			wordlen = 0;
			while (*s && *s != c && ++wordlen)
				++s;
			split[splitindex++] = ft_substr(s - wordlen, 0, wordlen);
		}
		else
			++s;
	}
	split[splitindex] = 0;
	return (split);
}

static int	wordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	i = -1;
	wordcount = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			++wordcount;
			while (s[i] && s[i] != c)
				++i;
		}
		if (!s[i])
			break ;
	}
	return (wordcount);
}

/*Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.*/
