/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/16 13:46:27 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_command(char **current_pos)
{
	char	*variable_name;
	char	*variable_value;
	char	*end;

	end = *current_pos;
	while (!ft_isspace(*end))
		end++;
	variable_name = ft_strndup(*current_pos, (end - *current_pos));
	*current_pos = end;
	variable_value = getenv(variable_name);
	free(variable_name);
	return (variable_value);
}
