/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:50:01 by vivan-de          #+#    #+#             */
/*   Updated: 2023/04/01 11:18:17 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char c)
{
	if (c == '\0')
		return (0);
	if (ft_isalnum(c) == 0 && c != '_')
		return (0);
	return (1);
}

int	validate_identifiers(t_str_builder_internal *sb, char *s)
{
	while (s[sb->i])
	{
		if (!is_valid_identifier(s[sb->i]))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)(s + sb->i), 2);
			ft_putstr_fd("'\n", 2);
			free(sb->new_str);
			return (-1);
		}
		sb->i++;
	}
	return (0);
}
