/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/22 13:44:06 by victor.simo      ###   ########.fr       */
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

void	pwd(t_ctx **ctx, char *line, t_token *token)
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
	free(current_path);
	ft_putstr_fd(fmt, token->fileout);
	free(fmt);
}
