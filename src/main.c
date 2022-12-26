/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/26 15:46:01 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	t_lkd_lst	*tokens;
	char		*data;
	t_ctx		*ctx;

	line = NULL;
	ctx = ctx_init();
	while (True)
	{
		if (!get_line_from_terminal(&line, ctx) || !line)
			return (1);
		if (!strcmp(line, "exit\n"))
		{
			free(line);
			ctx_free(&ctx);
			return (0);
		}
		tokens = ft_tokenizer(line);
		print_lkd_list(&tokens);
		data = (char *)tokens->head->content;
		ft_printf("\ncommand is valid: %d\n", cmd_is_valid(data));
		ft_printf("\nis builtin: %d\n", is_builtin(data));
		lkd_lst_kill_list(&tokens, free_token);
		free_if_exists((void **)&line);
	}
	return (0);
}
