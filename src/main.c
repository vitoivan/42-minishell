/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/01/10 18:53:08 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	AstNode		*command_tree;

	line = NULL;
	command_tree = NULL;
	while (True)
	{
		if (!get_line_from_terminal(&line) || !line)
			return (1);
		if (!ft_strcmp(line, "exit\n"))
		{
			free(line);
			ast_node_free(command_tree);
			return (0);
		}
		command_tree = ft_parser(line);

		free_if_exists((void **)&line);
		ast_node_free(command_tree);
	}
	return (0);
}
