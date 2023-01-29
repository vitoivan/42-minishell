#include "tests.h"

void	test_first(void)
{
	set_test_prefix("FIRST TEST");

	char *title = get_test_title("First test");
	ft_printf("%s ", title);
	free(title);
	assert(1);
}