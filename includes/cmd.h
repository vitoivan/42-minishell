#ifndef CMD_H
# define CMD_H

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

t_cmd		*cmd_new(char *cmd, char **args);
char		*get_binary_path(char *cmd);

#endif