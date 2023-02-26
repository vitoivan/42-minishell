/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:36:18 by jv                #+#    #+#             */
/*   Updated: 2023/02/25 22:08:45 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


static byte ft_strmatch(char *entry, char *pattern) 
{

	while(1) {
		char m = *pattern;
		char c = *entry;

		if (m == 0)
			return (c == 0);
		if (m == '*') {
            int n = 0;
            while (m == '*') 
                m = *(pattern + ++n);

			if (ft_strmatch(entry, pattern + n))
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
 
static char **ft_wildcard_split_args(Lexer *lexer) {
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

static uint ft_gt_last_sep_pos(char *position) {
	char *end;

	end = position;
	while (!(ft_isspace(*(position - 1))))
		position--;
	
	return (uint) (end - position);
}

static void ft_parser_wildcard_exp(char *file_name, char *mask, char **command)
{
    char *s1;
    
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

char *ft_mk_wildcard_command(Lexer *lexer)
{
    DIR *dir;
    struct dirent *entry;
    char **wildcards;
    char *command;
    uint size;

    if ((dir = opendir(".")) == NULL) 
		return NULL; // error ao abrir diretorio
    
    size = lexer->current_position - ft_gt_last_sep_pos(lexer->current_position) - lexer->start - 1;
    command = ft_strndup(lexer->start, size);
    wildcards = ft_wildcard_split_args(lexer);
    
   	while (*wildcards != NULL) {
		while ((entry = readdir(dir)) != NULL) 
            ft_parser_wildcard_exp(entry->d_name, *wildcards, &command);    
		free(*wildcards);
		rewinddir(dir);
		wildcards++;
	}
    return (command);
}

