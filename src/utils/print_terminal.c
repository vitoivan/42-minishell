/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/25 15:08:50 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path_fmt(t_ctx *ctx)
{
	char	**splitted;
	int		skip_n_home;
	char	*path_fmt;
	char	*tmp;

	splitted = ft_split(ctx->path, '/');
	if (!ft_strcmp(splitted[0], "home") && !ft_strcmp(splitted[1], ctx->user))
	{
		skip_n_home = ft_strlen(splitted[0]) + ft_strlen(splitted[1]) + 2;
		path_fmt = ft_strjoin("~", ctx->path + skip_n_home);
	}
	else
		path_fmt = ft_strdup(ctx->path);
	clear_splitted(&splitted);
	tmp = ft_strjoin(COLOR_BOLD BLU, path_fmt);
	free(path_fmt);
	path_fmt = ft_strjoin(tmp, RESET_COLOR REMOVE_BOLD);
	free(tmp);
	return (path_fmt);
}

static char	*get_dolar_ginal(void)
{
	char	*dolar_signal;
	char	*dolar_signal_tmp;

	dolar_signal = ft_strdup("$ ");
	dolar_signal_tmp = ft_strjoin(COLOR_BOLD WHT, dolar_signal);
	free(dolar_signal);
	dolar_signal = ft_strjoin(dolar_signal_tmp, RESET_COLOR REMOVE_BOLD "\0");
	free(dolar_signal_tmp);
	return (dolar_signal);
}

static char	*get_user_and_host(t_ctx *ctx)
{
	char	*user_and_host;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(ctx->user, "@");
	user_and_host = ft_strjoin(tmp, ctx->hostname);
	free(tmp);
	tmp = ft_strjoin(COLOR_BOLD GREEN, user_and_host);
	tmp2 = ft_strjoin(tmp, RESET_COLOR REMOVE_BOLD);
	free(tmp);
	free(user_and_host);
	return (tmp2);
}

char	*get_prompt(t_ctx *ctx)
{
	char	*user_and_host;
	char	*path;
	char	*dolar;
	char	*tmp1;
	char	*tmp2;

	user_and_host = get_user_and_host(ctx);
	path = get_path_fmt(ctx);
	dolar = get_dolar_ginal();
	tmp1 = ft_strjoin(user_and_host, path);
	tmp2 = ft_strjoin(tmp1, dolar);
	free(user_and_host);
	free(path);
	free(dolar);
	free(tmp1);
	return (tmp2);
}
