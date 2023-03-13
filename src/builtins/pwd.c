/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 20:00:23 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_pwd(t_ctx **ctx, char *line)
{
	int	i;

	i = 4;
	if ((size_t)i >= ft_strlen(line))
		return ;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		(*ctx)->status_code = 1;
}

void	pwd(t_ctx **ctx, char *line)
{
	char	*current_path;
	char	*fmt;

	validate_pwd(ctx, line);
	if ((*ctx)->status_code != EXIT_SUCCESS)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	current_path = NULL;
	current_path = getcwd(current_path, PATH_SIZE);
	fmt = ft_strjoin(current_path, "\n");
	ctx_populate_buffer(ctx, fmt);
	free(fmt);
	free(current_path);
}
