#include "tests.h"

char	*test_prefix = NULL;

void	tests_main(void)
{
	test_first();
	free(test_prefix);
}

int	main(void)
{
	tests_main();

	return (0);
}