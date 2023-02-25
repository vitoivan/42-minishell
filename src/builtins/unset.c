/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/25 14:31:02 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_unset(char *line)
{
	char	*name;

	name = line + 6;
	if (!name)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		errno = 1;
	}
	skip_whitespace(&name, 0);
	if (strlen(name) == 0)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		errno = 1;
	}
}

void	unset(t_ctx **ctx, char *line)
{
	char	*name;
	int		env_ind;

	validate_unset(line);
	if (errno != EXIT_SUCCESS)
	{
		cmd_export(ctx, "export $?=1");
		errno = 0;
		return ;
	}
	name = line + 6;
	skip_whitespace(&name, 0);
	env_ind = validate_if_env_already_exists(ctx, name);
	if (env_ind >= 0)
		lkd_lst_pop_at(&(*ctx)->env, env_ind, free);
}