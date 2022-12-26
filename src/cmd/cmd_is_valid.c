/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/11 14:52:43 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_is_valid(char *cmd)
{
	char	*tmp;
	char	*command;
	char	*binary_path;
	int		is_valid;

	is_valid = False;
	if (!cmd)
		return (is_valid);
	tmp = cmd;
	skip_whitespace(&tmp, 0);
	while (*tmp && *tmp != ' ')
		tmp++;
	command = malloc(sizeof(char) * (tmp - cmd + 1));
	if (!command)
		return (is_valid);
	ft_strlcpy(command, cmd, tmp - cmd + 1);
	binary_path = get_cmd_binary_path(command);
	if (binary_path)
		is_valid = True;
	free_if_exists((void **)&binary_path);
	free_if_exists((void **)&command);
	return (is_valid);
}
