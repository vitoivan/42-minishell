/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_terminal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/26 07:11:56 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	get_line_from_terminal(char **line)
{
	ft_printf(COLOR_BOLD GREEN "minishell $> " RESET_COLOR REMOVE_BOLD);
	*line = get_next_line(STDIN_FILENO, 4096, True);
	if (*line)
		return (True);
	skip_whitespace(line, 0);
	free_if_exists((void **)line);
	return (False);
}
