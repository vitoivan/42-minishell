#include "./tests.h"
#include "tests.h"

void	assert(int result)
{
	if (!result)
		ft_printf(COLOR_BOLD RED "KO\n" RESET_COLOR REMOVE_BOLD);
	else
		ft_printf(COLOR_BOLD GREEN "OK\n" RESET_COLOR REMOVE_BOLD);
}

char	*get_test_title(char *message)
{
	char	*prefix;
	char	*first_part;
	char	*aux;

	first_part = ft_strjoin(COLOR_BOLD BLU "\t[ ", test_prefix);
	prefix = ft_strjoin(first_part, " ] " RESET_COLOR REMOVE_BOLD);
	free(first_part);
	aux = ft_strjoin(prefix, message);
	free(prefix);
	return (aux);
}

void	set_test_prefix(char *prefix)
{
	if (test_prefix)
		free(test_prefix);
	test_prefix = ft_strdup(prefix);
}
