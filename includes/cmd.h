#ifndef CMD_H
# define CMD_H

# include "./define.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

t_cmd		*cmd_new(char *cmd, char **args);
char		*get_cmd_binary_path(char *cmd);
char		**get_path(void);
BOOL		cmd_is_valid(char *cmd);

#endif