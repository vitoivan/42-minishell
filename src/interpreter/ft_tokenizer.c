/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/26 07:12:45 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_token(char *start_token, char *end_token)
{
	char	*token;
	uint	index;

	index = 0;
	token = ft_calloc((end_token - start_token) + 1, sizeof(char));
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
	while (**end_token != quote && **end_token != '\n' && **end_token)
		(*end_token)++;
	if (**end_token != quote)
		exit(MEMORY_ALLOC_ERROR);
}

static void	ft_add_to_ldk_lst(t_lkd_lst **list, char *cmd, char *end)
{
	char	*token;

	token = get_token(cmd, end);
	if (!token)
		return ;
	lkd_lst_add_back(list, lkd_lst_new_node(token));
}

/* 
	TODO: Receive one command and parses it to t_cmd struct,
		then append this struct to t_lkd_nlst
*/
t_lkd_lst	*ft_tokenizer(char *cmd_line)
{
	t_lkd_lst	*list;
	char		*end_token;

	list = lkd_lst_new_list();
	if (!list)
		exit(MEMORY_ALLOC_ERROR); //corrigir
	skip_whitespace(&cmd_line, 0);
	end_token = cmd_line;
	while (*cmd_line && *cmd_line != '\n')
	{
		while (ft_isalpha(*end_token))
			end_token++;
		if (*end_token == SINGLE_QUOTE)
			parse_quote(&cmd_line, &end_token, SINGLE_QUOTE);
		else if (*end_token == DOUBLE_QUOTE)
			parse_quote(&cmd_line, &end_token, DOUBLE_QUOTE);
		ft_add_to_ldk_lst(&list, cmd_line, end_token);
		skip_whitespace(&end_token, 1);
		cmd_line = end_token;
	}
	return (list);
}
