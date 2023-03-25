/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_terminal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/25 15:14:56 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_line(char *prompt)
{
	char	*line;
	char	*tmp;

	line = readline(prompt);
	while (!line)
	{
		tmp = ft_strjoin("\n", prompt);
		line = readline(tmp);
		free(tmp);
	}
	return (line);
}

BOOL	get_line_from_terminal(char **line, t_ctx *ctx)
{
	char	*prompt;

	prompt = get_prompt(ctx);
	*line = get_line(prompt);
	add_history(*line);
	free(prompt);
	if (*line)
		return (True);
	free_if_exists((void **)line);
	return (False);
}
