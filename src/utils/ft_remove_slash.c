/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:14:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/27 21:22:53 by jv               ###   ########.fr       */
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
	unslashed_str = (char *) ft_calloc(ft_strlen(str) - slashes + 1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			unslashed_str[j++] = str[i];
		i++;
	}
	/* limpando aqui pra nao ter que criar uma var tmp lá */
	/* inclusive fazer isso no ft_strjoin é uma boa */
	free(str); 
	return (unslashed_str);
}