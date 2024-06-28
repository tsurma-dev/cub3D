/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:06:43 by tsurma            #+#    #+#             */
/*   Updated: 2024/03/19 17:13:52 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	store(t_all_I_need *a);
static char	*store1(t_all_I_need *a);
static char	*returns(t_all_I_need *a, int i);

char	*get_next_line(int fd)
{
	static t_all_I_need	a;

	while (a.last && a.last[a.len])
		++a.len;
	a.buf = ft_calloc((a.len + BUFFER_SIZE + 1), sizeof(char));
	a.toread = read(fd, a.buf + a.len, BUFFER_SIZE);
	if (a.toread == -1)
		return (returns(&a, 0));
	store(&a);
	if (a.buf[a.len] == '\0' && a.toread == 0)
		return (returns(&a, 1));
	if (a.buf[a.len] == '\0' && a.toread == BUFFER_SIZE)
	{
		a.len = 0;
		free(a.last);
		a.last = a.buf;
		return (get_next_line(fd));
	}
	if ((!(a.buf[a.len]) || a.buf[a.len] == '\n') && a.buf[a.len + 1] == '\0')
		return (returns(&a, 2));
	free(a.last);
	a.last = malloc(sizeof(char) * (a.lenstore + a.toread + 1));
	if (!a.last)
		return (returns(&a, 0));
	return (store1(&a));
}

static void	store(t_all_I_need *a)
{
	a->buf[a->len + a->toread] = '\0';
	a->lenstore = a->len;
	a->c = -1;
	while (--a->len >= 0)
		a->buf[a->len] = a->last[a->len];
	a->len++;
	while (a->buf[a->len] && a->buf[a->len] != '\n')
		++a->len;
}

static char	*store1(t_all_I_need *a)
{
	while (a->buf[a->len + 1 + ++a->c])
		a->last[a->c] = a->buf[a->len + 1 + a->c];
	a->last[a->c] = '\0';
	a->buf[a->len + 1] = '\0';
	a->len = 0;
	return (a->buf);
}

static char	*returns(t_all_I_need *a, int i)
{
	if (i == 0)
	{
		a->len = 0;
		free(a->buf);
		if (a->last != NULL)
			free(a->last);
		a->last = NULL;
		return (a->last);
	}
	else if (i == 1)
	{
		a->len = 0;
		free(a->buf);
		a->buf = a->last;
		a->last = NULL;
		return (a->buf);
	}
	else
	{
		a->len = 0;
		free(a->last);
		a->last = NULL;
		return (a->buf);
	}
}
