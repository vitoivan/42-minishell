/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/01/28 16:30:28 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*line;
	AstNode		*root_cmd;
	AstNode		*tmp;
	t_ctx		*ctx;
	char 		*current_cmd;

	line = NULL;
	root_cmd = NULL;
	ctx = ctx_init();
	while (True)
	{
		if (!get_line_from_terminal(&line, ctx) || !line)
			return (1);
		root_cmd = ft_parser(line);
		if (line)
			free(line);
		tmp = root_cmd;
		while(tmp)
		{
			if (tmp->type == NODE_COMMAND)
			{
				current_cmd = tmp->token->start;
				if (!ft_strncmp(current_cmd, "exit", 4))
				{
					ctx_free(&ctx);
					ast_node_free(root_cmd);
					return (0);
				}
				else if (!ft_strncmp(current_cmd, "pwd", 3))
					pwd();
				else if (!ft_strncmp(current_cmd, "cd", 2))
				{
					char *cd_path = current_cmd + 3;
					errno = 0;
					cd(cd_path);
					ctx_update(&ctx);
				}
				else if (!ft_strncmp(current_cmd, "export", 6))
				{
					char *args = current_cmd + 7;
					char **splitted = ft_split(args, '=');
					char *name = splitted[0];
					char *value = splitted[1];
					skip_whitespace(&value, 0);
					builtin_export(name, value);
					int i = 0;
					while(splitted[i])
						free(splitted[i++]);
					free(splitted);
				}
			}
			tmp = tmp->as.binaryExpression.right;
		}
		ast_node_free(root_cmd);
	}
	return (0);
}
