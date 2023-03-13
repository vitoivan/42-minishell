/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_terminal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/13 10:07:47 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_line(char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (!line)
		line = readline(prompt);
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
