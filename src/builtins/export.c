/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/01/28 16:25:55 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int ft_isquote(char c)
{
	if (c == SINGLE_QUOTE)
		return (True);
	if (c == DOUBLE_QUOTE)
		return (True);
	return (False);
}

int builtin_export(char *name, char *value)
{
	char *value_to_be_setted;
	size_t str_len;
	

	value_to_be_setted = NULL;
	if (ft_isquote(value[0]))
	{
		str_len = ft_strlen(value) - 1;
		value_to_be_setted = calloc(str_len, sizeof(char));
		ft_strlcpy(value_to_be_setted, value + 1, str_len);
	} else 
		value_to_be_setted = ft_strdup(value);
	if (setenv(name, value_to_be_setted, 1) == -1)
	{
		free(value_to_be_setted);
		return (False);
	}
	free(value_to_be_setted);
	return (True);
}

