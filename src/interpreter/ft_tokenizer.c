/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/10 14:08:48 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_token(char *start_token, char *end_token)
{
	char	*token;
	uint	index;

	index = 0;
	token = ft_calloc((end_token - start_token), sizeof(char));
	if (!token)
		exit(UNQUOTED_STRING_ERROR); // corrigir dps
	while (start_token < end_token)
	{
		token[index++] = *start_token;
		start_token++;
	}
	token[index] = '\0';
	return (token);
}

static void	parse_quote(char **start_token, char **end_token, char quote)
{
	(*start_token)++;
	(*end_token)++;
	while (**end_token != quote || **end_token)
		/*  Ajustar na proxima atualizacao do tokenizer */
		(*end_token)++;
	if (**end_token != quote)
		exit(MEMORY_ALLOC_ERROR);
}

t_linked	*ft_tokenizer(char *cmd_line)
{
	t_linked	*list;
	char		*end_token;

	end_token = cmd_line;
	list = linked_new_list();
	if (!list)
		exit(MEMORY_ALLOC_ERROR); //corrigir
	while (*cmd_line)
	{
		while (ft_isalpha(*end_token))
			end_token++;
		if (*end_token == SINGLE_QUOTE)
			parse_quote(&cmd_line, &end_token, SINGLE_QUOTE);
		else if (*end_token == DOUBLE_QUOTE)
			parse_quote(&cmd_line, &end_token, DOUBLE_QUOTE);
		linked_add_back(&list, linked_new_node(split_token(cmd_line,
						end_token)));
		cmd_line = ++end_token;
	}
	return (list);
}
