/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:36:18 by jv                #+#    #+#             */
/*   Updated: 2023/02/25 16:46:33 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


byte ft_strmatch(char *entry, char *pattern) 
{
	while(1) {
		char m = *pattern;
		char c = *entry;

		if (m == 0)
			return (c == 0);
		if (m == '*') {
			if (ft_strmatch(entry, pattern + 1))
				return (1);
			if (c == 0)
				return (0);
		} else {
			if (m == '?')
			{
				if (c == 0)
					return (0);
			} else if (m != c)
				return (0);
			pattern++;
		}
		entry++;
	}
}

char *ft_wildcard_get_pattern(Lexer *lexer) {
	char *start;
	char *end;

	start = lexer->current_position;
	end   = lexer->current_position;

	while (!ft_isspace(*(start - 1)))
		start--;
	while (!ft_isspace(*end) && *end)
		end++;

	/* update lexer position */
	lexer->current_position += (end - lexer->current_position);	
	return (ft_strndup(start, end - start));
}
 
char **ft_wildcard_split_args(Lexer *lexer) {
    char *start;
    char *end; 
    char *args;
    char **splited_args;

    start = lexer->current_position;

    while (start != lexer->start && !ft_isspace(*(start - 1)))
        start--;
    
    while (!is_at_end(lexer) && !is_operator(lexer))
        lexer->current_position++;
    
    end = lexer->current_position;

    args = ft_strndup(start, end - start);

    splited_args = ft_split(args, ' ');

    free(args);

    return (splited_args);
}

 uint ft_gt_last_sep_pos(char *position) {
	char *end;

	end = position;
	while (!(ft_isspace(*(position - 1))))
		position--;
	
	return (uint) (end - position);
}
/*
char *mk_wildcard_command(char *file_name, char *wildcard)
{
    static char *command = NULL;

    if (ft_strmatch(file_name, wildcard))
	{
		if (command) {
			char *s1 = command; 
			command = ft_strjoin(command, " ");
			free(s1);
			s1 = command;
			command = ft_strjoin(command, entry->d_name);
			free(s1);
		} else {
			char *s1 = ft_strndup(lexer->start, tmp - ft_gt_last_sep_pos(tmp) - lexer->start);
			char *s2 = ft_strdup(entry->d_name);
			command = ft_strjoin(s1, s2);
			free(s1); free(s2);
		}
	}

    return (command);
}
*/
