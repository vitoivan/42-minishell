/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:36:18 by jv                #+#    #+#             */
/*   Updated: 2023/03/16 14:09:23 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_wildcard(char **entry, char **pattern, char *m, char *c)
{
	int	n;

	n = 0;
	while (*m == '*')
		*m = *(*pattern + ++n);
	if (ft_strmatch(*entry, *pattern + n))
		return (1);
	if (*c == 0)
		return (0);
	return (-1);
}

static int	handle_questionmark(char **pattern, char *m, char *c)
{
	if (*m == '?')
	{
		if (*c == 0)
			return (0);
	}
	else if (*m != *c)
		return (0);
	(*pattern)++;
	return (-1);
}

BYTE	ft_strmatch(char *entry, char *pattern)
{
	char	m;
	char	c;
	int		aux;

	while (1)
	{
		m = *pattern;
		c = *entry;
		if (m == 0)
			return (c == 0);
		if (m == '*')
		{
			aux = handle_wildcard(&entry, &pattern, &m, &c);
			if (aux != -1)
				return (aux);
		}
		else
		{
			aux = handle_questionmark(&pattern, &m, &c);
			if (aux != -1)
				return (aux);
		}
		entry++;
	}
}
