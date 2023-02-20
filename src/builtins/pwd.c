/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 15:09:13 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_pwd(char *line)
{
	int	i;

	i = 4;
	if ((size_t)i >= ft_strlen(line))
		return ;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		errno = 1;
}

void	pwd(t_ctx **ctx, char *line)
{
	char	*current_path;
	char	*fmt;

	validate_pwd(line);
	if (errno != EXIT_SUCCESS)
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
