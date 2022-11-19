/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_terminal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/11/19 16:30:40 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static BOOL	get_buffer(char **buffer)
{
	*buffer = (char *)malloc(sizeof(char) + 4096 + 1);
	if (!buffer)
		return (False);
	return (True);
}

static BOOL	free_and_return_error(char **buffer)
{
	free_if_exists((void **)buffer);
	return (False);
}

static void	set_empty_line_and_free_buffer(char **buffer, char **line)
{
	free_if_exists((void **)buffer);
	*line = ft_strdup("");
}

BOOL	get_line_from_terminal(char **line)
{
	char	buf;
	int		read_ret;
	char	*buffer;
	int		i;

	if (!get_buffer(&buffer))
		return (False);
	i = 0;
	ft_printf(COLOR_BOLD GREEN "minishell $> " RESET_COLOR REMOVE_BOLD);
	read_ret = read(STDIN_FILENO, &buf, 1);
	while (read_ret && read_ret != -1 && buf != '\n')
	{
		buffer[i++] = buf;
		buffer[i] = '\0';
		read_ret = read(STDIN_FILENO, &buf, 1);
	}
	if (read_ret == -1)
		return (free_and_return_error(&buffer));
	if (i > 0)
		*line = buffer;
	else
		set_empty_line_and_free_buffer(&buffer, line);
	return (True);
}
