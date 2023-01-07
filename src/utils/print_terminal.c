/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/31 08:34:50 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path_fmt(t_ctx *ctx)
{
	char	**splitted;
	int		skip_n_home;
	char	*path_fmt;
	int		i;

	i = 0;
	splitted = ft_split(ctx->path, '/');
	if (!ft_strcmp(splitted[0], "home") && !ft_strcmp(splitted[1], ctx->user))
	{
		skip_n_home = ft_strlen(splitted[0]) + ft_strlen(splitted[1]) + 2;
		path_fmt = ft_strjoin("~", ctx->path + skip_n_home);
	}
	else
		path_fmt = ft_strdup(ctx->path);
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	return (path_fmt);
}

static const char	*get_printf_str(void)
{
	char	*s;

	s = COLOR_BOLD GREEN "%s" WHT ":" BLU "%s" WHT "$ " RESET_COLOR REMOVE_BOLD;
	return ((const char *)s);
}

static char	*get_user_and_host(t_ctx *ctx)
{
	char	*user_and_host;
	char	*tmp;

	tmp = ft_strjoin(ctx->user, "@");
	user_and_host = ft_strjoin(tmp, ctx->hostname);
	free(tmp);
	return (user_and_host);
}

void	print_terminal(t_ctx *ctx)
{
	char	*user_and_host;
	char	*path;

	user_and_host = get_user_and_host(ctx);
	path = get_path_fmt(ctx);
	ft_printf(get_printf_str(), user_and_host, path);
	free_if_exists((void **)&path);
	free_if_exists((void **)&user_and_host);
}
