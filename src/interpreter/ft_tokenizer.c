/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/25 17:07:25 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/

#include "../../includes/minishell.h"

static Token	*mk_token(Lexer *lexer, TokenType type, byte variable)
{
	Token			*token;
	StringBuilder	*sb;

	token = ft_calloc(1, sizeof(Token));
	if (!token)
		return (NULL);
	token->type = type;
	if (variable)
	{
		sb = string_builder(lexer->start, (lexer->current_position
					- lexer->start));
		if (sb)
		{
			token->size = sb->size;
			token->start = sb->start;
			free(sb);
		}
		else
		{
			ft_printf("LexerError: Undefined variable\n");
			token->type = TOKEN_ERROR;
			token->error_msg = "Lexer Error: Undefined variable\n";
		}
	}
	else
	{
		token->size = (uint)(lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	return (token);
}


static Token *mk_wildcard_token(Lexer *lexer)
{
	DIR *dir;
	struct dirent *entry;
	char **wildcards;
	char *command;
	char *tmp;
	Token *token;
	byte i;

	tmp = (char *) lexer->current_position;
	i = 0;
	command = NULL;
	
	token = ft_calloc(1, sizeof(Token));
	if (!token) 
		return (NULL);
		
	
	wildcards = ft_wildcard_split_args(lexer);

	while (wildcards[i] != NULL) {
		if ((dir = opendir(".")) == NULL) 
			return NULL; // error ao abrir diretorio
		while ((entry = readdir(dir)) != NULL) 
		{
			if (ft_strmatch(entry->d_name, wildcards[i]))
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
		}
		free(wildcards[i]);
		rewinddir(dir);
		i++;
	}
	closedir(dir);
	free(wildcards);

	token->type = TOKEN_COMMAND;
	token->start = command;
	token->size = ft_strlen(command);

	return (token);
}

static Token *scan_command(Lexer *lexer) {
	byte quote;
	byte variable;
	
	quote    = 0;
	variable = 0;


	if ( is_operator(lexer) || is_at_end(lexer) )
		return NULL;
		
	while (!is_at_end(lexer) && !is_operator(lexer)) {
	
		if (ft_is_double_quote(*lexer->current_position)) 
			quote = !quote;
		if ( *lexer->current_position == '$')
			variable = 1;
		if ( *lexer->current_position == '*')
			return mk_wildcard_token(lexer);
		lexer->current_position++;
	}
	if (quote)
	{
		ft_printf("Parser Error, UNQUOTED STRING\n");
		exit(UNQUOTED_STRING_ERROR);
	}
	if (!is_at_end(lexer))
		lexer->current_position--;
	return (mk_token(lexer, TOKEN_COMMAND, variable));
}

static Token	*scan_operator(Lexer *lexer)
{
	while (!is_at_end(lexer) && is_operator(lexer))
		lexer->current_position++;
	// if (!strncmp(lexer->current_position - 1, "||", 2))
	// 	lexer->current_position++;
	if (is_at_end(lexer))
	{
		return (NULL); // return token with error
	}
	if (ft_strncmp(lexer->start, ";", 1) == 0)
		return (mk_token(lexer, TOKEN_HIGH_OPERATOR, 0));
	return (mk_token(lexer, TOKEN_OPERATOR, 0));
}

static Token	*lexer_next_token(ParserContext *context)
{
	Token	*new_current_token;

	skip_white_spaces(&context->lexer);
	new_current_token = scan_command(&context->lexer);
	if (!new_current_token)
		new_current_token = scan_operator(&context->lexer);
	if (!new_current_token)
		return (NULL);
	context->lexer.start = context->lexer.current_position;
	return (new_current_token);
}

void	del_token(Token *token)
{
	if (token != NULL)
	{
		free(token->start);
		free(token);
	}
}

void	advance_to_next_token(ParserContext *context)
{
	context->parser.previus_token = context->parser.current_token;
	context->parser.current_token = lexer_next_token(context);
}
