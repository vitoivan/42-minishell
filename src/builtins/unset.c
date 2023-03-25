/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/25 12:03:56 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_unset(t_ctx **ctx, char *line)
{
	char	*name;
	int		len;

	len = ft_strlen(line);
	if (len < 6)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		(*ctx)->status_code = 1;
		return ;
	}
	name = line + 6;
	if (!name)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		(*ctx)->status_code = 1;
	}
	skip_whitespace(&name, 0);
	if (*name == '\0' || !name)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		(*ctx)->status_code = 1;
	}
}

void	unset(t_ctx **ctx, char *line)
{
	char	*name;
	int		env_ind;

	validate_unset(ctx, line);
	if ((*ctx)->status_code != EXIT_SUCCESS)
		return ;
	name = line + 6;
	skip_whitespace(&name, 0);
	env_ind = validate_if_env_already_exists(ctx, name);
	if (env_ind >= 0)
		lkd_lst_pop_at(&(*ctx)->env, env_ind, free);
}
