#include "../../includes/minishell.h"

byte	is_at_end(Lexer *lexer)
{
	return (*lexer->current_position == '\0' ||
			*lexer->current_position == '\n');
}

byte	is_operator(Lexer *lexer)
{
	char	c;

	c = *(lexer->current_position);
	if (c == '&' || c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

void	skip_white_spaces(Lexer *lexer)
{
	while (ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	lexer->start = lexer->current_position;
}

void	lexer_init(Lexer *lexer, char *source)
{
	lexer->start = source;
	lexer->current_position = source;
}

Token	*get_current_token(ParserContext *context)
{
	return (context->parser.current_token);
}

Token	*get_previus_token(ParserContext *context)
{
	return (context->parser.previus_token);
}

char	*ft_strndup(const char *str, uint n)
{
	char *new = NULL;

	new = ft_calloc(sizeof(char), n + 1);

	ft_strlcpy(new, str, n + 1);

	return (new);
}