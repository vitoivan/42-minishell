#include "../../includes/minishell.h"

BYTE	is_at_end(t_lexer *lexer)
{
	return (*lexer->current_position == '\0' ||
			*lexer->current_position == '\n');
}

BYTE	is_operator(t_lexer *lexer)
{
	char	c;

	c = *(lexer->current_position);
	if (c == '&' || c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

t_token_type	ft_get_token_type(t_lexer *lexer)
{
	char *token_content;
	t_token_type type;

	token_content = ft_strndup(lexer->start, lexer->current_position - lexer->start);
	type = TOKEN_ERROR;
	if (ft_strcmp(token_content, "||") == 0)
		type = TOKEN_OPERATOR_OR;
	if (ft_strcmp(token_content, "|") == 0)
		type = TOKEN_OPERATOR_PIPE;
	if (ft_strcmp(token_content, "<") == 0)
		type = TOKEN_OPERATOR_REDIRECT_INPUT;
	if (ft_strcmp(token_content, "<<") == 0)
		type = TOKEN_OPERATOR_HERE_DOC;
	if (ft_strcmp(token_content, ">") == 0)
		type = TOKEN_OPERATOR_REDIRECT;
	if (ft_strcmp(token_content, ">>") == 0)
		type = TOKEN_OPERATOR_REDIRECT_APPEND;
	if (ft_strcmp(token_content, ";") == 0)
		type = TOKEN_OPERATOR_SEMICOLON;
	free(token_content);
	return (type);
}

void	skip_white_spaces(t_lexer *lexer)
{
	while (ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	lexer->start = lexer->current_position;
}

void	lexer_init(t_lexer *lexer, char *source)
{
	lexer->start = source;
	lexer->current_position = source;
}

t_token	*get_current_token(t_parser_context *context)
{
	return (context->parser.current_token);
}

t_token	*get_previus_token(t_parser_context *context)
{
	return (context->parser.previus_token);
}

char	*ft_strndup(const char *str, UINT n)
{
	char *new = NULL;

	new = ft_calloc(sizeof(char), n + 1);

	ft_strlcpy(new, str, n + 1);

	return (new);
}