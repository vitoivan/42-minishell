#ifndef TESTS_H
# define TESTS_H

# include "../includes/minishell.h"

void		assert(int result);
char		*get_test_title(char *message);
void		test_first(void);
void		set_test_prefix(char *prefix);
void        test_ft_wildcard_split_args(void);

extern char	*test_prefix;

#endif