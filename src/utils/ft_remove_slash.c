/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:14:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/30 08:17:31 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_remove_slash(char *str)
{
	UINT	slashes;
	UINT	i;
	UINT	j;
	char	*unslashed_str;

	slashes = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			slashes++;
		i++;
	}
	unslashed_str = (char *) ft_calloc(ft_strlen(str) - slashes + 1,
			sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			unslashed_str[j++] = str[i];
		i++;
	}
	free(str);
	return (unslashed_str);
}
