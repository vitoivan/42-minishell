/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_terminal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/11 16:52:07 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	get_line_from_terminal(char **line, t_ctx *ctx)
{
	char	*prompt;

	prompt = get_prompt(ctx);
	*line = readline(prompt);
	free(prompt);
	if (*line)
		return (True);
	free_if_exists((void **)line);
	return (False);
}
