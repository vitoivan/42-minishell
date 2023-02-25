#include "./tests.h"

void test_ft_wildcard_split_args(void) {
  char line[] = "echo *.txt *.mp4";

  Lexer lexer = {
    .start = line,
    .current_position = line
  }; 
  char **splited_args = ft_wildcard_split_args(&lexer);

  int out1 = ft_strcmp(splited_args[0], "*.txt");
  int out2 = ft_strcmp(splited_args[1], "*.mp4");

  assert(out1 == 0);
  assert(out2 == 0);
  assert(splited_args[2] == NULL);
}
