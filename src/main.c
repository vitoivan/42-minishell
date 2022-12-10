/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/10 14:00:18 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	t_linked	*tokens;

	line = NULL;
	while (True)
	{
		if (!get_line_from_terminal(&line) || !line)
			return (1);
		if (!strcmp(line, "exit\n"))
		{
			free(line);
			return (0);
		}
		tokens = ft_tokenizer(line);
		// ft_lst_print_str(tokens);
		linked_kill_list(&tokens, free_token);
		free_if_exists((void **)&line);
	}
	return (0);
}
