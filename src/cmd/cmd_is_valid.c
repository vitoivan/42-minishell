/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/11 10:17:04 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	*cmd_is_valid(char *cmd)
{
	char	*tmp;
	char	*command;
	uint	size;

	if (!cmd)
		return (False);
	tmp = cmd;
	skip_whitespace(&tmp, 0);
	while (*tmp && *tmp != ' ')
		tmp++;
	command = malloc(sizeof(char) * (tmp - cmd + 1));
	if (!command)
		return (False);
	ft_strlcpy(command, tmp, tmp - cmd + 1);
}
