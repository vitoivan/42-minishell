/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/11/19 16:24:17 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	line = NULL;
	while (True)
	{
		if (!get_line_from_terminal(&line) || !line)
			return (1);
		if (!strcmp(line, "exit"))
		{
			free(line);
			return (1);
		}
		ft_printf("line: %s\n", line);
		free_if_exists((void **)&line);
	}
	return (0);
}
