/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:36:18 by jv                #+#    #+#             */
/*   Updated: 2023/03/16 14:15:49 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_wildcard_split_args(t_lexer *lexer)
{
	char	*start;
	char	*end;
	char	*args;
	char	**splited_args;

	start = lexer->current_position;
	while (start != lexer->start && !ft_isspace(*(start - 1)))
		start--;
	while (!is_at_end(lexer) && !is_operator(lexer, 0))
		lexer->current_position++;
	end = lexer->current_position;
	args = ft_strndup(start, end - start);
	splited_args = ft_split(args, ' ');
	free(args);
	return (splited_args);
}

static UINT	ft_gt_last_sep_pos(char *position)
{
	char	*end;
	UINT	ret;

	end = position;
	while (!(ft_isspace(*(position - 1))))
		position--;
	ret = (UINT)(end - position);
	return (ret);
}

static void	ft_parser_wildcard_exp(char *file_name, char *mask, char **command)
{
	char	*s1;

	if (ft_strmatch(file_name, mask))
	{
		s1 = *command;
		*command = ft_strjoin(*command, " ");
		free(s1);
		s1 = *command;
		*command = ft_strjoin(*command, file_name);
		free(s1);
	}
}

static void	init_vars(t_lexer *lexer, UINT *size, char **command,
		char ***wildcards)
{
	*size = lexer->current_position
		- ft_gt_last_sep_pos(lexer->current_position) - lexer->start - 1;
	*command = ft_strndup(lexer->start, *size);
	*wildcards = ft_wildcard_split_args(lexer);
}

char	*ft_mk_wildcard_command(t_lexer *lexer)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**wildcards;
	char			*command;
	UINT			size;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	init_vars(lexer, &size, &command, &wildcards);
	while (*wildcards != NULL)
	{
		entry = readdir(dir);
		while (entry != NULL)
		{
			ft_parser_wildcard_exp(entry->d_name, *wildcards, &command);
			entry = readdir(dir);
		}
		free(*wildcards);
		rewinddir(dir);
		wildcards++;
	}
	return (command);
}
